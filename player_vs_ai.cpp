// 超簡易型AIでのテスト。

#include "cpp_reversi.cpp"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace Reversi;
float evaluate_func1(Board board, Piece color)
{
    //序盤なら乱数を返す
    if (board.countPiece(none) > 55)
        return (float)rand();

    Piece enemy_color;
    if (color == black)
        enemy_color = white;
    if (color == white)
        enemy_color = black;

    float f = 0;
    f += board.countPiece(color);
    f += board.countPlaceablePositions(color) * 0.8;
    f += board.countCorner(color) * 10;
    f += board.countPlaceableCorner(color) * 8;
    f -= board.countPiece(enemy_color);
    f -= board.countCorner(enemy_color) * 10;
    f -= board.countPlaceableCorner(enemy_color) * 8;
    return f;
}

using namespace Reversi;
using namespace std;
int main()
{
    srand(time(NULL)); //乱数の初期化
    Board board;                 // 初期化
    AI ai = AI(&evaluate_func1); // AI初期化
    ai.magnifcation = 0.8;
    ai.preloading_times = 30;

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
            Position pos = ai.predict_best_position(board, white);
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
