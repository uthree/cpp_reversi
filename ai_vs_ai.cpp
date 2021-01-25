#include <iostream>
#include "cpp_reversi.cpp"

using namespace Reversi;
using namespace std;

float evaluate_board_1(Board board, Piece color)
{
    float f = 0;
    f += board.countPiece(color);
    f += board.countPlaceablePositions(color) * 0.9;
    f += board.countCorner(color) * 400;
    f += board.countPlaceableCorner(color) * 20;
    return f;
}

float evaluate_board_2(Board board, Piece color)
{
    return 0;
}

int main(int argc, char const *argv[])
{
    Board board = Board(); //盤面の初期化
    AI ai_1 = AI(evaluate_board_1);
    ai_1.preloading_times = 30;
    ai_1.magnifcation = 0.5;
    AI ai_2 = AI(evaluate_board_2);
    ai_1.preloading_times = 1;
    ai_1.magnifcation = 0.8;

    AI first_player = ai_1;
    AI second_player = ai_2;

    while (board.checkPlaceableAnywhere())
    {
        cout << board.toString() << endl;
        if (board.checkPlaceableAnywhere(black))
        {
            Position p = first_player.predict_best_position(board, black);
            board.place(p, black);
        }
        cout << board.toString() << endl;
        if (board.checkPlaceableAnywhere(white))
        {
            Position p = first_player.predict_best_position(board, white);
            board.place(p, white);
        }
    }
    cout << board.toString() << endl;
    cout << board.countPiece(black) << " : " << board.countPiece(white) << endl;

    return 0;
}
