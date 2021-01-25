#include "ai.hpp"

#include <iostream>

#include "cpp_reversi.cpp"

#ifndef CR_2026DE2B_BB6E_4AA6_A4FA_70F2A82B45B4
#define CR_2026DE2B_BB6E_4AA6_A4FA_70F2A82B45B4
namespace Reversi
{
    float AI::evaluate_board(Board board, Piece color, int count)
    {
        count--;
        float r = 0.0;
        Piece enemy_color = getEnemyColor(color); //相手の色を取得

        // std::cout << board.toString(color) << std::endl;
        //自分側
        if (count > 0 && board.checkPlaceableAnywhere(color))
        {
            //自分の最善手を探索。
            float now_value = __FLT_MIN_10_EXP__;                                                 // 最大値になるようにする。
            std::vector<Position> my_placeable_positions = board.searchPlaceablePositions(color); // 自分が置ける場所全てを列挙
            Position best_position = my_placeable_positions.at(0);                                // 最善の位置

            for (int i = 0; i < my_placeable_positions.size(); i++)
            {
                Board b = Board(board);
                b.place(my_placeable_positions.at(i), color); // とりあえず設置してみる。
                float v = evaluation_function(b, color);      // 評価
                if (now_value <= v)
                { //最大値にしたいのでこう
                    now_value = v;
                    best_position = my_placeable_positions.at(i);
                    //std::cout << "MAX FND" << v << std::endl;
                }
                r += v;
            }
            board.place(best_position, color); //設置を確定
            r += now_value;                    //加算する
        }
        else if (board.checkPlaceableAnywhere(color))
        {
            return evaluation_function(board, color);
        }

        // std::cout << board.toString(getEnemyColor(color)) << std::endl;
        //相手側
        if (count > 0 && board.checkPlaceableAnywhere(enemy_color))
        {
            //相手側の最善手を探索
            std::vector<Position> enemy_placeable_positions = board.searchPlaceablePositions(enemy_color); //相手が置ける場所全てを列挙
            Position best_position = enemy_placeable_positions.at(0);
            float now_value = __FLT_MAX_10_EXP__; // 最小値になってほしい

            for (int i = 0; i < enemy_placeable_positions.size(); i++)
            {
                Board b = Board(board);
                b.place(enemy_placeable_positions.at(i), enemy_color); //とりあえず設置してみる。
                float v = 0.0 - evaluation_function(b, enemy_color);   //評価する(負数)
                if (now_value >= v)
                { // 最小値にしたいのでこうする
                    now_value = v;
                    best_position = enemy_placeable_positions.at(i);
                    //  "MIN FND" << v << std::endl;
                }
                r += v;
            }
            board.place(best_position, enemy_color); // 設置を確定。
            r -= now_value;                          //減算する。
        }
        else if (board.checkPlaceableAnywhere())
        {
            return evaluation_function(board, enemy_color);
        }

        if (count > 0)
        {
            r += evaluate_board(board, color, count) * magnifcation;
        }
        return r;
    }

    Position AI::predict_best_position(Board board, Piece color, int count)
    {
        if (count == 0)
            count = preloading_times;
        std::vector<Position> placeable_positions = board.searchPlaceablePositions(color);
        if (placeable_positions.size() == 0)
            return Position(-1, -1);
        Position best_position = placeable_positions.at(0);
        float best_score = -65535; //最大値になるようにする
        for (int i = 0; i < placeable_positions.size(); i++)
        {
            Board b = Board(board); //boardをコピー
            Position p = placeable_positions.at(i);
            b.place(p, color);
            float s = evaluate_board(b, color, count);
            if (best_score <= s)
            {
                best_score = s;
                best_position = p;
            }
        }
        return best_position;
    }

    Piece AI::getEnemyColor(Piece color)
    {
        if (color == black)
            return white;
        if (color == white)
            return black;
        return none;
    }

} // namespace Reversi
#endif