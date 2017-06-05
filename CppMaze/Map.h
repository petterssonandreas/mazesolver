#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <cstdint>

class Map
{
public:
    Map() = default;
    ~Map() = default;
    Map(std::string map_file_name);

    std::vector<uint8_t> map_data;
    size_t map_width = 0;
    size_t map_height = 0;

    int loadMap(std::string map_file_name);

private:

};



#endif
