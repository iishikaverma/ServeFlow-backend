#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;

class FileManager
{
public:
    static nlohmann::json readJson(const string& filePath);

    static void writeJson(
        const string& filePath,
        const nlohmann::json& data
    );
};

#endif