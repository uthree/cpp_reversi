// 超簡易型AIでのテスト。

#include "cpp_reversi.cpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>

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
    const float score_a = 1.0;
    const float score_b = -0.04;
    const float score_c = 0.01;
    const float score_d = -0.4;
    const float score_e = 0.02;
    const float score_f = 0.01;

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
                        r -= score_a * 0.5;
                    else
                        r -= score_a * 1.0;
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
                        r -= score_b * 0.2;
                    else
                        r -= score_b * 1.0;
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
                        r -= score_c * 0.2;
                    else
                        r -= score_c * 1.0;
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
                        r -= score_d * 0.2;
                    else
                        r -= score_d * 1.0;
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
                        r -= score_e * 0.0;
                    else
                        r -= score_e * 1.0;
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
                        r -= score_f * 0.0;
                    else
                        r -= score_f * 1.0;
                }
            }
        }
    }
    return r / 40;
}

using namespace Reversi; // 評価関数を定義
float evaluate(Board board, Piece color)
{
    float score = 0;
    float count_score = (float)board.countPiece(color) / 64;                   //石の制圧率
    float cell_score = evaluate_cell_types(board, color);                      //　マス目ごとのスコア
    float placeable_score = board.searchPlaceablePositions(color).size() / 64; // 設置できるマスの数(選択肢の数)
    return cell_score * 20 + count_score + placeable_score * 2;
}

float evaluate2(Board board, Piece color)
{
    float sc = (float)board.countPiece(color) + board.searchPlaceablePositions(color).size();
    if (board.checkPlaceable(Position(0, 0), color) || board.checkPlaceable(Position(0, 7), color) || board.checkPlaceable(Position(7, 0), color) || board.checkPlaceable(Position(7, 7), color))
    {
        sc += 100.0;
    }
    if (board.getPiece(Position(0, 0)) == color || board.getPiece(Position(7, 7)) == color || board.getPiece(Position(0, 7)) == color || board.getPiece(Position(7, 0)) == color)
    {
        sc += 500.0;
    }
}

using namespace Reversi;
using namespace std;
int main()
{
    Board board;            // 初期化
    AI ai = AI(&evaluate2); // AI初期化
    ai.magnifcation = 2.0;

    while (board.checkPlaceableAnywhere()) //どちらかが設置不可能になるまで繰り返す。
    {

        // 評価値
        cout << "EV: " << round(ai.evaluate_board(board, white) * 100) / 100 << endl;
        cout << board.toString(black) << endl;
        if (board.checkPlaceableAnywhere(black))
        {
        label_input:
            string s;
            cin >> s;
            int x, y;
            try
            {
                x = s[0] - 97;
                y = stoi(s.substr(1, 1)) - 1;
                //不正な値だったら戻る
                if (x > 7 || x < 0 || y > 7 || y < 0)
                {
                    cout << "盤面の外にアクセスしようとしないでください。" << endl;
                    goto label_input;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                cout << "不正な値です。入力し直してください。" << endl;
                goto label_input;
            };
            if (!board.checkPlaceable(Position(x, y), black))
            {
                cout << "そこには置けません。" << endl;
                goto label_input;
            }
            board.place(Position(x, y), black);
        }
        cout << board.toString(white) << endl;
        if (board.checkPlaceableAnywhere(white))
        {
            Position pos = ai.predict_best_position(board, white, 3);
            cout << "AI_ANS: " << pos.x << pos.y << endl;
            board.place(pos, white);
        }
        else
        {
            cout << "?" << endl;
        }
    }
    //勝利判定
    int count_black = board.countPiece(black);
    int count_white = board.countPiece(white);

    cout << board.toString(black) << endl;

    cout << "黒: " << count_black << endl;
    cout << "白: " << count_white << endl;
    if (count_black > count_white)
    {
        cout << "黒(プレイヤー)の勝利です。" << endl;
    }
    else if (count_black < count_white)
    {
        cout << "白(コンピュータ)の勝利です。" << endl;
    }
    else
    {
        cout << "引き分けです。" << endl;
    }
}

void clear_screen()
{
    std::cout << "\e[2J" << std::endl;
}