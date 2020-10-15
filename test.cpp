#include "cpp_reversi.cpp"
#include <iostream>
#include <unistd.h>

using namespace Reversi;
namespace ScoreMap
{
    const Position a[] = {
        Position(0, 0),
        Position(0, 7),
        Position(7, 7),
        Position(7, 0),
    };
    const Position b[] = {
        Position(0, 1),
        Position(1, 0),
        Position(7, 1),
        Position(7, 0),
        Position(7, 6),
        Position(6, 7),
        Position(0, 7),
        Position(1, 7),
    };
    const Position c[] = {
        Position(0, 2),
        Position(2, 0),
        Position(5, 0),
        Position(0, 5),
        Position(5, 2),
        Position(5, 7),
        Position(2, 2),
        Position(2, 7),
    };
    const Position d[] = {
        Position(1, 1),
        Position(1, 6),
        Position(6, 1),
        Position(6, 6),
    };
    const Position e[] = {
        Position(2, 1),
        Position(1, 2),
        Position(6, 1),
        Position(1, 6),
        Position(6, 5),
        Position(5, 6),
        Position(1, 5),
        Position(5, 1),
    };
    const Position f[] = {
        Position(2, 2),
        Position(5, 2),
        Position(2, 5),
        Position(5, 5),
    };
} // namespace ScoreMap

using namespace Reversi; // 評価関数を定義
float evaluate(Board board, Piece color)
{
    float count = (float)board.countPiece(color) / 64;
}

float evaluate_cell_types(Board, Piece color)
{
    const float score_a = 1;
    const float score_b = 0.1;
    const float score_c = 0.2;
    const float score_d = -1;
    const float score_e = 0.2;
    const float score_f = 0.1;

    float r = 0.0;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            // SCORE TYPE A
            for (int i = 0; i < 4; i++)
            {
                if (ScoreMap::a[i] == Position(x, y))
                {
                    r += score_a;
                }
            }
        }
    }
    return r / 40;
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