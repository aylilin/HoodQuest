#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <string>

Menu::Menu(Graph& graph, int goalVertex)
    : graph(graph), goalVertex(goalVertex)
{
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

    std::cout << "مسیر پیشنهادی (Dijkstra): ";

    for(size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];

        if(i != path.size() - 1)
            std::cout << " -> ";
    }

    std::cout << std::endl;

    std::cout << "خانه بعدی پیشنهادی: "
               << engine.getSuggestedNextMove()
               << std::endl;
}

void Menu::printState(GameEngine& engine) const
{
    GameState state = engine.getState();

    std::cout << "---------------------------------" << std::endl;
    std::cout << "نوبت: " << state.getMoveCount() + 1 << std::endl;
    std::cout << "موقعیت شما: " << state.getPlayer().getPosition() << std::endl;
    std::cout << "موقعیت گرگ: " << state.getWolf().getPosition() << std::endl;
    std::cout << "امتیاز: " << state.getPlayer().getScore() << std::endl;

    printSuggestion(engine);
}

void Menu::run()
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

    std::cout << "به HoodQuest خوش آمدید!" << std::endl;

    std::cout
        << "موقعیت شما: " << playerStart
        << " | موقعیت گرگ: " << wolfStart
        << " | خانه مادربزرگ: " << goalVertex
        << std::endl;

    while(!engine.isGameOver())
    {
        printState(engine);

        std::cout
            << "دستور را وارد کنید (شماره خانه مقصد، یا u برای Undo): ";

        std::string input;

        std::cin >> input;

        if(input == "u" || input == "U")
        {
            if(engine.undo())
            {
                std::cout << "حرکت قبلی لغو شد (۲ امتیاز جریمه شد)." << std::endl;
            }
            else
            {
                std::cout << "در حال حاضر امکان Undo وجود ندارد." << std::endl;
            }

            continue;
        }

        int destination;

        try
        {
            destination = std::stoi(input);
        }
        catch(...)
        {
            std::cout << "ورودی نامعتبر است." << std::endl;

            continue;
        }

        TurnResult result = engine.playTurn(destination);

        if(result == TurnResult::InvalidMove)
        {
            std::cout << "حرکت نامعتبر است؛ خانه انتخابی مجاور شما نیست." << std::endl;
        }
        else if(result == TurnResult::Continue)
        {
            std::cout << "امتیاز فعلی: " << engine.getState().getPlayer().getScore() << std::endl;
        }
        else if(result == TurnResult::PlayerWon)
        {
            std::cout << "تبریک! شنل قرمزی به خانه مادربزرگ رسید." << std::endl;
            std::cout << "امتیاز نهایی: " << engine.getState().getPlayer().getScore() << std::endl;
        }
        else if(result == TurnResult::PlayerLost)
        {
            std::cout << "گرگ شنل قرمزی را گرفت؛ باختید." << std::endl;
            std::cout << "امتیاز نهایی: " << engine.getState().getPlayer().getScore() << std::endl;
        }
    }
}