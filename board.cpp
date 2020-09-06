#include "board.hpp"

#ifndef CR_8bd0d938_8918_4e2e_8ee7_64419c741770
#define CR_8bd0d938_8918_4e2e_8ee7_64419c741770

namespace Reversi
{
    bool Board::checkPlaceable(Position pos, Piece color)
    {
        //TODO: 最適化
        auto direction = searchPlaceableDirections(pos, color);
        if (direction.size() > 0)
            return true;
        return false;
    }
    std::vector<Position> Board::searchPlaceableDirections(Position pos, Piece color)
    {
        //ベクトルを初期化
        std::vector<Position> placeable_directions;

        //　相手の色を確認しておく。
        Piece enemy_color;
        if (color == black)
            enemy_color = white;
        if (color == white)
            enemy_color = black;

        // そもそも既に石が置いてある場合
        if (getPiece(pos) != none)
        {
            return placeable_directions;
        }
        // 8方向を探索する。
        for (int i = 0; i < 8; i++)
        {
            Position direction = eight_directions[i]; //今調べてる方向
            bool flag = false;                        //フラグ

            //端まで行くか置きたい色と同じ色が検出されるか何もないところに当たるまで
            for (int d = 1; d < 8; d++)
            {
                Position checkpos = direction * d + pos;

                // 端の場合はループを抜ける
                if (checkpos.x > 7 || checkpos.x < 0)
                    break;
                if (checkpos.y > 7 || checkpos.y < 0)
                    break;
                //何もないのでループを抜ける
                if (getPiece(checkpos) == none)
                    break;
                //相手の色ならフラグを有効にする。
                if (getPiece(checkpos) == enemy_color)
                {
                    flag = true;
                }
                //フラグが立っていて、かつ自分の色がきたら設置可能な方向とする。
                if (getPiece(checkpos) == color && flag)
                {
                    placeable_directions.push_back(direction); //戻り値に追加。
                    break;
                }
            }
        }
        // 値を返す
        return placeable_directions;
    }

    void Board::Place(Position pos, Piece color) //設置処理。 checkPlaceableがtrueになっていることが前提。
    {
        std::vector<Position> placeable_directions = searchPlaceableDirections(pos, color);
        int size = placeable_directions.size();
        setPiece(pos, color);
        for (int i = 0; i < size; i++)
        {
            Position direction = placeable_directions[i];
            for (int d = 1; d < 8; d++)
            {
                Position checkpos = direction * d + pos;
                Piece checkcol = getPiece(pos);

                // 端の場合はループを抜ける
                if (checkpos.x > 7 || checkpos.x < 0)
                    break;
                if (checkpos.y > 7 || checkpos.y < 0)
                    break;

                if (checkcol == color) //自分の色だったらループ抜ける
                    break;
                if (checkcol == none) // 何もなかったらループ抜ける
                    break;
                //結果的に相手の色の場合のみ以下の処理が実行されるので、ひっくり返す(自分の色にする。)。
                setPiece(checkpos, color);
            }
        }
    }

    Piece Board::getPiece(Position position)
    {
        return board_map[position.y][position.x];
    }

    void Board::setPiece(Position position, Piece piece)
    {
        board_map[position.y][position.x] = piece;
    }
} // namespace Reversi

#endif