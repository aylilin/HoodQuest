#include "FileManager.h"

#include <fstream>
#include <sstream>

bool FileManager::loadGraph(const std::string& path, Graph& graph)
{
    std::ifstream file(path);

    if(!file.is_open())
        return false;

    int vertexCount;

    if(!(file >> vertexCount))
        return false;

    for(int i = 0; i < vertexCount; i++)
    {
        int id;

        if(!(file >> id))
            return false;

        graph.addVertex(id);
    }

    int edgeCount;

    if(!(file >> edgeCount))
        return false;

    for(int i = 0; i < edgeCount; i++)
    {
        int from;
        int to;
        int weight;

        if(!(file >> from >> to >> weight))
            return false;

        graph.addEdge(from, to, weight);
    }

    return true;
}

std::string FileManager::hashPassword(const std::string& password)
{
   
    unsigned long hash = 5381;

    for(char c : password)
    {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
    }

    std::ostringstream oss;

    oss << std::hex << hash;

    return oss.str();
}

std::vector<UserRecord> FileManager::loadUsers(const std::string& path)
{
    std::vector<UserRecord> users;

    std::ifstream file(path);

    if(!file.is_open())
        return users;

    std::string username;
    std::string passwordHash;
    int score;

    while(file >> username >> passwordHash >> score)
    {
        UserRecord record;

        record.username = username;
        record.passwordHash = passwordHash;
        record.score = score;

        users.push_back(record);
    }

    return users;
}

bool FileManager::saveUsers(const std::string& path, const std::vector<UserRecord>& users)
{
    std::ofstream file(path);

    if(!file.is_open())
        return false;

    for(const UserRecord& user : users)
    {
        file << user.username << " " << user.passwordHash << " " << user.score << std::endl;
    }

    return true;
}