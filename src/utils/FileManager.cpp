#include "../../include/utils/FileManager.h"

#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

json FileManager::readJson(const string& filePath)
{
    ifstream file(filePath);

    if (!file.is_open())
    {
        cout << "Unable to open file: " << filePath << endl;
        return json::array();
    }

    json data;
    file >> data;

    file.close();

    return data;
}

void FileManager::writeJson(
    const string& filePath,
    const json& data
)
{
    ofstream file(filePath);

    if (!file.is_open())
    {
        cout << "Unable to open file: " << filePath << endl;
        return;
    }

    file << data.dump(4);

    file.close();
}