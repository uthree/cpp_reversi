#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "cpp_reversi.cpp"

using namespace Reversi;
using namespace std;

float evaluate_board_1(Board board, Piece color) // 多少マシな評価関数
{
    float f = 0;
    f += board.countPiece(color);
    f += board.countPlaceablePositions(color) * 0.9;
    f += board.countCorner(color) * 400;
    f += board.countPlaceableCorner(color) * 20;
    return f;
}

float evaluate_board_2(Board board, Piece color) //ランダムな値を返すでたらめな評価関数
{
    float r = (float)rand();
    //std::cout << r << std::endl;
    return r;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL)); //乱数の初期化
    // 100回対戦させて、勝利回数を見る。
    int black_wins = 0; 
    int white_wins = 0;
    int draw = 0;
    for (size_t i = 0; i < 100; i++) //500回検証する。
    {
            Board board = Board(); //盤面の初期化
        AI ai_1 = AI(evaluate_board_1);
        ai_1.preloading_times = 10;
        ai_1.magnifcation = 0.2;
        AI ai_2 = AI(evaluate_board_2);
        ai_1.preloading_times = 1;
        ai_1.magnifcation = 0.8;

        AI first_player = ai_1;
        AI second_player = ai_2;

        while (board.checkPlaceableAnywhere())
        {
            //cout << board.toString() << endl;
            if (board.checkPlaceableAnywhere(black))
            {
                Position p = first_player.predict_best_position(board, black);
                //std::cout << first_player.evaluate_board(board, black, 2);
                board.place(p, black);
            }
            //cout << board.toString() << endl;
            if (board.checkPlaceableAnywhere(white))
            {
                Position p = second_player.predict_best_position(board, white);
                board.place(p, white);
            }
        }
        //cout << board.toString() << endl;
        //cout << board.countPiece(black) << " : " << board.countPiece(white) << endl;

        // 勝敗判定。
        int count_b = board.countPiece(black);
        int count_w = board.countPiece(white);

        if(count_b > count_w) {
            black_wins ++;
        }
        if (count_b < count_w) {
            white_wins ++;
        }
        if (count_b == count_w) {
            draw ++;
        }
    }
    cout << "Wins" << endl;
    cout << "B =    " << black_wins << endl;
    cout << "W =    " << white_wins << endl;
    cout << "Draw = " << draw << endl;
    return 0;
}
