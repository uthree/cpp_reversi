#include "cpp_reversi.cpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <random>
#include <stdint.h>

using namespace Reversi;
float evaluate_func1(Board board, Piece color)
{
    float sc = (float)board.countPiece(color) + board.searchPlaceablePositions(color).size();
    if (board.getPiece(Position(0, 0)) == color)
    {
        sc += 20.0;
    }
    if (board.getPiece(Position(7, 0)) == color)
    {
        sc += 20.0;
    }
    if (board.getPiece(Position(7, 7)) == color)
    {
        sc += 20.0;
    }
    if (board.getPiece(Position(0, 7)) == color)
    {
        sc += 20.0;
    }
    return sc;
}

using namespace Reversi;
float evaluate_func2(Board board, Piece color) //いかなる場合においてもゼロを返す雑な関数
{
    return 0;
}

using namespace Reversi;
using namespace std;
int main()
{
    Board board;
    AI bot_b(&evaluate_func1);
    bot_b.preloading_times = 3;
    bot_b.magnifcation = 0.5;
    AI bot_w(&evaluate_func2);
    bot_w.preloading_times = 4;
    bot_w.magnifcation = 0.5;

    while (board.checkPlaceableAnywhere())
    {
        cout << board.toString(black) << endl;
        if (board.checkPlaceableAnywhere(black))
        {
            board.place(bot_b.predict_best_position(board, black), black);
        }
        cout << board.toString(white) << endl;
        if (board.checkPlaceableAnywhere(white))
        {
            board.place(bot_w.predict_best_position(board, white), white);
        }
    }
    cout << board.toString() << endl;
    cout << "b" << board.countPiece(black) << ": w" << board.countPiece(white) << endl;
    return 0;
}
