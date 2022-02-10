#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include "Board.h"

typedef std::tuple<int, int> point;

std::string point_to_tuple(point p)
{
    int p1 = std::get<0>(p);
    int p2 = std::get<1>(p);
    std::string response;
    response += "(";
    response += std::to_string(p1);
    response += ", ";
    response += std::to_string(p2);
    response += ")";
    return response;
};

std::vector<std::string> side_dirs(std::string direction)
{
    std::vector<std::string> dirs;
    // if the direction is one of the corners, length == 2, so return both main dirs
    if (direction.size() == 2)
    {
        for (int i = 0; i < direction.size(); i++)
        {
            std::string new_element(1, direction[i]);
            dirs.push_back(new_element);
        }
        return dirs;
    }
    // we received a main dir, so give back the according corner dirs
    if (direction == "L" || direction == "R")
    {
        dirs.push_back("U" + direction);
        dirs.push_back("D" + direction);
    }
    else
    {
        dirs.push_back(direction + "L");
        dirs.push_back(direction + "R");
    }
    return dirs;
}

Board::Board(int dim, std::vector<point> points)
{
    this->dim = dim;
    this->points = points;
}

bool Board::poi_in_points(point quest_point)
{
    for (point point_in_points : points)
    {
        if (point_in_points == quest_point)
        {
            return true;
        }
    }
    return false;
}

void Board::print_points()
{
    for (point p : points)
    {
        point_to_tuple(p);
    }
    std::cout << std::endl;
}

void Board::print_board()
{
    std::string board_rows = "";
    for (int col = 0; col < dim; col++)
    {
        std::string row_string = "";
        for (int row = 0; row < dim; row++)
        {
            // create a point based on the for loops
            point point(col, row);
            // check if point in points
            bool found_point = std::find(points.begin(), points.end(), point) != points.end();
            row_string += found_point ? "X" : "-";
            row_string += " ";
        }
        // Append row to the board string
        board_rows += row_string;
        board_rows += "\n";
    }
    // print board
    std::cout << board_rows;
}

point Board::neighbor(point old_point, std::string direction)
{
    int col = std::get<0>(old_point);
    int row = std::get<1>(old_point);
    if (direction.find('U') != std::string::npos)
    {
        col--;
    }
    else if (direction.find('D') != std::string::npos)
    {
        col++;
    }

    if (direction.find('R') != std::string::npos)
    {
        row++;
    }
    else if (direction.find('L') != std::string::npos)
    {
        row--;
    }

    point unfound_point(-1, -1); // init an impossible point
    // check if any points exceeds dimension
    if (row == -1 || row == dim || col == -1 || col == dim)
    {
        return unfound_point;
    }
    // check if neighbor is already in points
    point quest_point(col, row);
    if (this->poi_in_points(quest_point))
    {
        return unfound_point;
    }
    return quest_point;
}

bool Board::follow_gravity(std::string gravity = "DR")
{
    for (int i = 0; i < points.size(); i++)
    {
        // get the first point in points
        point poi = points[i];
        point unfound_point(-1, -1);
        // calculate the gravpoint
        point gravpoint(this->neighbor(poi, gravity));
        // if there is a gravpoint, push it to the list
        if (gravpoint == unfound_point)
        {
            continue;
        }
        points.erase(points.begin() + i);
        points.push_back(gravpoint);
        return true; // the follow worked
    }
    return false;
}

bool Board::follow_side(std::string gravity = "DR")
{
    std::vector<std::string> side_directions(side_dirs(gravity));
    point unfound_point(-1, -1);
    for (int i = 0; i < points.size(); i++)
    {
        // get the first point in points
        point poi = points[i];
        // calculate both sides
        std::vector<point> side_points;
        for (std::string dir : side_directions)
        {
            point side_point(this->neighbor(poi, dir));
            if (side_point == unfound_point)
            {
                continue;
            }
            side_points.push_back(side_point);
        }
        // len(side_points) == 0 => there weren't any side points for this poi
        if (side_points.size() == 0)
        {
            continue;
        }
        else if (side_points.size() == 1)
        {
            points.erase(points.begin() + i);
            points.push_back(side_points[0]);
            return true;
        }
        int index = rand() % 2; // get a random number between 0 and 1
        points.erase(points.begin() + i);
        points.push_back(side_points[index]);
        return true;
    }
    return false;
}

bool Board::follow(std::string gravity = "DR")
{
    if (points.size() == 0)
    {
        return false;
    }
    bool follow_grav = this->follow_gravity(gravity);
    if (follow_grav)
    {
        return true;
    }
    // no points can follow to gravity
    // check if a point can fall to the side
    return this->follow_side(gravity);
}
