#pragma once

#include <string>
#include <vector>

#include "../DataStructures/Graph.h"

struct UserRecord
{
    std::string username;
    std::string passwordHash;
    int score;
};

class FileManager
{
public :

    static bool loadGraph(const std::string& path, Graph& graph);

   
    static std::string hashPassword(const std::string& password);

    static std::vector<UserRecord> loadUsers(const std::string& path);

    static bool saveUsers(const std::string& path, const std::vector<UserRecord>& users);
};