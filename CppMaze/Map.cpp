
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

#include "Map.h"

using namespace std;


Map::Map(string map_file_name)
{
    if (loadMap(map_file_name) != 0)
    {
        cerr << "Error in loading map" << endl;
    }
}



int Map::loadMap(string map_file_name)
{
    // Open file with maze map and read it
    string map_data_string = "";
    ifstream map_file(map_file_name);
    if (map_file.is_open())
    {
        char temp;
        map_file >> map_width;
        map_file >> temp;
        map_file >> map_height;
        map_file >> temp;
        map_file >> map_data_string;
    }
    else
    {
        cerr << "Could not open map file" << endl;
        return 1;
    }

    if (map_data_string.empty())
    {
        cerr << "Input from file missing" << endl;
        return 2;
    }

    // Remove all ','
    for (size_t i = 0; i < map_data_string.length(); ++i)
    {
        if (map_data_string[i] != ',')
        {
            map_data.push_back(map_data_string[i]);
        }
    }

    map_file.close();
    return 0;
}
