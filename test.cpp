#include "cpp_reversi.cpp"
#include <iostream>
#include <unistd.h>

using namespace Reversi; // 評価関数を定義
float evaluate(Board board, Piece color)
{
    return (float)board.countPiece(color);
}

using namespace Reversi;
using namespace std;
int main()
{
    Board board;           // 初期化
    AI ai = AI(&evaluate); // AI初期化

    while (board.checkPlaceableAnywhere()) //どちらかが設置不可能になるまで繰り返す。
    {
        cout << board.toString(black) << endl;
        board.place(ai.predict_best_position(board, black), black);
        cout << board.toString(white) << endl;
        board.place(ai.predict_best_position(board, white), white);
    }
}

void clear_screen()
{
    std::cout << "\e[2J" << std::endl;
}