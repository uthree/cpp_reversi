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
    Board board; // 初期化
    AI ai = AI(&evaluate);
    cout << ai.evaluate_board(board, black, 64) << endl;
    cout << "RESULT" << endl;
    cout << board.toString() << endl;
}

void clear_screen()
{
    std::cout << "\e[2J" << std::endl;
}