#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

typedef std::tuple<int, int> point;
std::string point_to_tuple(point p);
std::vector<std::string> side_dirs(std::string direction);


class Board
{
public:
    // define the needed vars
    int dim;
    std::vector<point> points;
    // create a constructor, basically an __init__ like in python
    Board(int dim, std::vector<point> points);

    void print_points();

    void print_board();

    point neighbor(point old_point, std::string direction);

    bool git poi_in_points(point quest_point);

    bool follow_gravity(std::string gravity);

    bool follow_side(std::string gravity);

    bool follow(std::string gravity);
};
#endif