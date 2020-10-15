// 超簡易型AIでのテスト。

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

// マス単位での評価関数
float evaluate_cell_types(Board board, Piece color)
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
                Position p = ScoreMap::a[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_a;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_a;
                }
            }

            // SCORE TYPE B
            for (int i = 0; i < 4; i++)
            {
                Position p = ScoreMap::b[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_b;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_b;
                }
            }

            // SCORE TYPE C
            for (int i = 0; i < 4; i++)
            {
                Position p = ScoreMap::c[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_c;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_c;
                }
            }

            // SCORE TYPE D
            for (int i = 0; i < 4; i++)
            {
                Position p = ScoreMap::d[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_d;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_d;
                }
            }

            // SCORE TYPE E
            for (int i = 0; i < 4; i++)
            {
                Position p = ScoreMap::e[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_e;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_e;
                }
            }
            // SCORE TYPE F
            for (int i = 0; i < 4; i++)
            {
                Position p = ScoreMap::f[i];
                if (p.x == x && p.y == y)
                {
                    Piece c = board.getPiece(Position(x, y));
                    if (c == color)
                        r += score_f;
                    else if (c == none)
                        r += 0.0;
                    else
                        r -= score_f;
                }
            }
        }
    }
    return r / 40.0;
}

using namespace Reversi; // 評価関数を定義
float evaluate(Board board, Piece color)
{
    float score = 0;
    float count_score = (float)board.countPiece(color) / 64;
    float cell_score = evaluate_cell_types(board, color);
    return cell_score * 4 + count_score;
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