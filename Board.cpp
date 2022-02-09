#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

typedef std::tuple<int, int> point;

std::string point_to_tuple(int p1, int p2)
{
    std::string response;
    response += "(";
    response += std::to_string(p1);
    response += ", ";
    response += std::to_string(p2);
    response += ")";
    return response;
};

std::vector<std::string> side_dirs(std::string direction){
    std::vector<std::string> dirs;
    if(direction.size() == 2){
        for (int i = 0; i < direction.size(); i++) {
            std::string new_element (1, direction[i]);
            dirs.push_back(new_element);
        }
        return dirs;
    }
    return dirs;
};

class Board
{
public:
    // define the needed vars
    int dim;
    std::vector<point> points;
    // create a constructor, basically an __init__ like in python
    Board(int dim, std::vector<point> points){
        this->dim = dim;
        this->points = points;
    }
    void print_points(){
        for (auto &tuple : points){
            point_to_tuple(std::get<0>(tuple), std::get<1>(tuple));
        }
        std::cout << std::endl;
    }
    
    void print_board(){
        std::string board_rows = "";
        for(int col = 0; col < dim; col++){
            std::string row_string = "";
            for(int row = 0; row < dim; row++){
                // create a point based on the for loops
                point point (col, row);
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

    point neighbor(point old_point, std::string direction){
        int col = std::get<0>(old_point);
        int row = std::get<1>(old_point);
        if(direction.find('U') != std::string::npos){
            col--;
        } else if(direction.find('D') != std::string::npos){
            col++;
        }

        if (direction.find('R') != std::string::npos){
            row++;
        } else if (direction.find('L') != std::string::npos){
            row--;
        }

        if(row < -1 || row == dim || col < -1 || col == dim){
            row = -1;
            col = -1;
        }
        point new_point (col, row);
        return new_point;
    }

    bool follow(std::string gravity = "DR"){
        if(points.size() == 0){
            return false;
        }
        // Get the first element from the list
        point poi = points[0];
        // 
        point unfound_point (-1, -1);
        // 
        point gravpoint (this->neighbor(poi, gravity));
        if(gravpoint != unfound_point){
            points.erase(points.begin());
            points.push_back(poi);
            return true;
        }

        /*
            START HERE WITH SIDE DIRS
        */

        points.push_back(poi);
        points.erase(points.begin());  
        std::cout << points.size() << gravity << std::endl;
    }
};

int main()
{
    int dim;
    dim = 5;

    std::vector<point> points;
    int i = 0;
    for (int col = 0; col < dim; col++)
    {
        for (int row = 0; row < dim; row++)
        {
            i++;
            int quest = col * dim + row;
            if (quest < (dim * dim / 2))
            {
                std::cout << i << " continuing at" << point_to_tuple(col, row) << std::endl;
                continue;
            }
            std::cout << i << " pushing back at " << point_to_tuple(col, row) << std::endl;
            points.push_back(point(col, row));
        }
    }
    Board board(dim, points);
    board.print_points();
    board.print_board();
    std::string gravity = "UR";
    std::vector<std::string> side_irs = side_dirs(gravity);
    std::cout << side_irs.at(0) << " " << side_irs.at(1) << std:: endl;
    return 0;
}