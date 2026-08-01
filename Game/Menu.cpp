#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cctype>

Menu::Menu(
    Graph& graph,
    int goalVertex,
    const std::map<int,std::string>& labels,
    const std::string& usersFilePath)
    : graph(graph),
      goalVertex(goalVertex),
      labels(labels),
      usersFilePath(usersFilePath)
{
}

std::string Menu::label(int vertexId) const
{
    auto it = labels.find(vertexId);

    if(it != labels.end())
        return it->second;

    return std::to_string(vertexId);
}

int Menu::pickRandomStart(const std::vector<int>& ids, int exclude) const
{
    std::vector<int> candidates;

    for(int id : ids)
    {
        if(id != exclude)
            candidates.push_back(id);
    }

    if(candidates.empty())
        return exclude;

    return candidates[rand() % candidates.size()];
}

void Menu::printSuggestion(GameEngine& engine) const
{
    std::vector<int> path = engine.getSuggestedPath();

    std::cout << "Suggested path (Dijkstra): ";

    for(size_t i = 0; i < path.size(); i++)
    {
        std::cout << label(path[i]);

        if(i != path.size() - 1)
            std::cout << " -> ";
    }

    std::cout << std::endl;

    std::cout << "Suggested next move: "
               << label(engine.getSuggestedNextMove())
               << std::endl;
}

void Menu::printState(GameEngine& engine) const
{
    GameState state = engine.getState();

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Turn: " << state.getMoveCount() + 1 << std::endl;
    std::cout << "Your position: " << label(state.getPlayer().getPosition()) << std::endl;
    std::cout << "Wolf position: " << label(state.getWolf().getPosition()) << std::endl;
    std::cout << "Score this round: " << state.getPlayer().getScore() << std::endl;

    printSuggestion(engine);
}

bool Menu::registerUser()
{
    std::string username;

    std::cout << "Enter a new username: ";

    std::cin >> username;

    if(!std::cin)
        return false;

    if(userTable.Contains(username))
    {
        std::cout << "This username is already taken." << std::endl;

        return false;
    }

    std::string password;

    std::cout << "Enter a password: ";

    std::cin >> password;

    if(!std::cin)
        return false;

    UserRecord record;

    record.username = username;
    record.passwordHash = FileManager::hashPassword(password);
    record.score = 0;

    userTable.Insert(username, record);

    userList.push_back(record);

    scoreManager.setScore(username, 0);

    FileManager::saveUsers(usersFilePath, userList);

    std::cout << "Account created successfully." << std::endl;

    return true;
}

bool Menu::loginUser(std::string& loggedInUser)
{
    std::string username;

    std::cout << "Username: ";

    std::cin >> username;

    if(!std::cin)
        return false;

    if(!userTable.Contains(username))
    {
        std::cout << "No such user exists." << std::endl;

        return false;
    }

    std::string password;

    std::cout << "Password: ";

    std::cin >> password;

    if(!std::cin)
        return false;

    UserRecord record = userTable.Get(username);

    if(record.passwordHash != FileManager::hashPassword(password))
    {
        std::cout << "Incorrect password." << std::endl;

        return false;
    }

    std::cout << "Login successful. Welcome, " << username << "!" << std::endl;

    std::cout << "Your total score: " << record.score << std::endl;

    showTopPlayer();

    loggedInUser = username;

    return true;
}

void Menu::showTopPlayer() const
{
    std::vector<std::pair<std::string,int>> top = scoreManager.getTopPlayers(1);

    if(top.empty())
        return;

    std::cout
        << "Current top player: " << top[0].first
        << " with score " << top[0].second
        << std::endl;
}

void Menu::updateUserScore(const std::string& username, int delta)
{
    UserRecord record = userTable.Get(username);

    record.score += delta;

    userTable.Insert(username, record);

    for(UserRecord& u : userList)
    {
        if(u.username == username)
        {
            u.score = record.score;

            break;
        }
    }

    scoreManager.addToScore(username, delta);

    FileManager::saveUsers(usersFilePath, userList);
}

void Menu::playGame(const std::string& username)
{
    std::vector<int> ids = graph.getVertexIds();

    int playerStart = pickRandomStart(ids, goalVertex);

    int wolfStart = pickRandomStart(ids, goalVertex);

    while(wolfStart == playerStart)
    {
        wolfStart = pickRandomStart(ids, goalVertex);
    }

    Player player(1, playerStart);

    Wolf wolf(1, wolfStart);

    GameEngine engine(graph, goalVertex, player, wolf);

    std::cout
        << "Your position: " << label(playerStart)
        << " | Wolf position: " << label(wolfStart)
        << " | Grandma's house: " << label(goalVertex)
        << std::endl;

    while(!engine.isGameOver())
    {
        printState(engine);

        std::cout
            << "Enter your move (destination letter, or u for Undo): ";

        std::string input;

        std::cin >> input;

        if(!std::cin)
        {
            std::cout << "Input ended; stopping the game." << std::endl;
            break;
        }

        if(input == "u" || input == "U")
        {
            if(engine.undo())
            {
                std::cout << "Last move undone (2-point penalty applied)." << std::endl;
            }
            else
            {
                std::cout << "Undo is not available right now." << std::endl;
            }

            continue;
        }

        int destination = -1;

        bool isNumeric = !input.empty() &&
            std::all_of(input.begin(), input.end(), ::isdigit);

        if(isNumeric)
        {
            destination = std::stoi(input);
        }
        else
        {
            std::string upperInput = input;

            std::transform(upperInput.begin(), upperInput.end(), upperInput.begin(), ::toupper);

            bool found = false;

            for(const auto& entry : labels)
            {
                if(entry.second == upperInput)
                {
                    destination = entry.first;
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                std::cout << "Invalid input." << std::endl;
                continue;
            }
        }

        TurnResult result = engine.playTurn(destination);

        if(result == TurnResult::InvalidMove)
        {
            std::cout << "Invalid move; that vertex is not adjacent to you." << std::endl;
        }
        else if(result == TurnResult::Continue)
        {
            std::cout << "Score this round: " << engine.getState().getPlayer().getScore() << std::endl;
        }
        else if(result == TurnResult::PlayerWon)
        {
            std::cout << "Congratulations! Red Riding Hood reached grandma's house." << std::endl;
        }
        else if(result == TurnResult::PlayerLost)
        {
            std::cout << "The wolf caught Red Riding Hood; you lost." << std::endl;
        }
    }

    int roundScore = engine.getState().getPlayer().getScore();

    updateUserScore(username, roundScore);

    std::cout << "Score this round: " << roundScore << std::endl;
    std::cout << "Your total score is now: " << scoreManager.getScore(username) << std::endl;
}

void Menu::run()
{
    userList = FileManager::loadUsers(usersFilePath);

    for(const UserRecord& record : userList)
    {
        userTable.Insert(record.username, record);

        scoreManager.setScore(record.username, record.score);
    }

    bool exitRequested = false;

    while(!exitRequested)
    {
        std::cout << "===================================" << std::endl;
        std::cout << "Welcome to HoodQuest!" << std::endl;
        std::cout << "1. Create a new account" << std::endl;
        std::cout << "2. Log in to an existing account" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choice: ";

        std::string choice;

        std::cin >> choice;

        if(!std::cin)
        {
            exitRequested = true;
            break;
        }

        if(choice == "1")
        {
            registerUser();
        }
        else if(choice == "2")
        {
            std::string username;

            if(loginUser(username))
            {
                playGame(username);
            }
        }
        else if(choice == "3")
        {
            exitRequested = true;
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }
    }

    std::cout << "Goodbye!" << std::endl;
}
