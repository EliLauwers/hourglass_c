#include "Board.h"
int main()
{
    int dim;
    dim = 5;
    std::vector<point> points;
    // Create some points
    for (int col = 0; col < dim; col++)
    {
        for (int row = 0; row < dim; row++)
        {
            int quest = col * dim + row;
            if (quest < (dim * dim / 2))
            {
                continue;
            }
            points.push_back(point(col, row));
        }
    }
    Board board(dim, points);
    for (int i = 0; i < 5; i++)
    {
        board.print_board();
        std::cout << std::endl;
        bool followed = board.follow("UL");
    }
    return 0;
}