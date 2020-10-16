#include <iostream>

#include "board.hpp"
#include "cpp_reversi.cpp"

#ifndef CR_8bd0d938_8918_4e2e_8ee7_64419c741770
#define CR_8bd0d938_8918_4e2e_8ee7_64419c741770

namespace Reversi
{
    bool Board::checkPlaceable(Position pos, Piece color)
    {
        //TODO: 最適化
        auto direction = searchPlaceableDirections(pos, color);
        if (direction.size() > 0 && this->getPiece(pos) == none)
            return true;
        return false;
    }
    bool Board::checkPlaceableAnywhere(Piece color)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (checkPlaceable(Position(x, y), color))
                    return true;
            }
        }
        return false;
    }
    bool Board::checkPlaceableAnywhere()
    {
        return (checkPlaceableAnywhere(white) || checkPlaceableAnywhere(black));
    }
    int Board::countPiece(Piece color)
    {
        int r = 0;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (this->getPiece(Position(x, y)) == color)
                    r++;
            }
        }
        return r;
    }
    std::vector<Position> Board::searchPlaceablePositions(Piece color) // なんか知らんが二倍の値が出てくる。
    {
        std::vector<Position> r;
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (this->checkPlaceable(Position(x, y), color))
                    r.push_back(Position(x, y));
            }
        }
        return r;
    }
    std::vector<Position> Board::searchPlaceableDirections(Position pos, Piece color)
    {
        //ベクトルを初期化
        std::vector<Position> placeable_directions;
        bool flag = false;
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

            //端まで行くか置きたい色と同じ色が検出されるか何もないところに当たるまで
            flag = false;
            for (int d = 1; d < 8; d++)
            {
                Position checkpos = direction * d + pos;

                // 端の場合はループを抜ける
                if (checkpos.x > 7 || checkpos.x < 0)
                    break;
                if (checkpos.y > 7 || checkpos.y < 0)
                    break;
                //何もない
                if (getPiece(checkpos) == none)
                {
                    break;
                }

                // 相手の色見つけた
                if (getPiece(checkpos) == enemy_color)
                {
                    flag = true;
                }
                if (getPiece(checkpos) == color && flag == false) //自分と同じ色でfagがfalse
                {
                    break; //ひっくり返せないので無視する。
                }
                //2回目のループ、かつ自分の色がきたら設置可能な方向とする。
                if (getPiece(checkpos) == color && d >= 2 && flag == true)
                {
                    placeable_directions.push_back(direction); //戻り値に追加。
                    //std::cout << direction.x << " " << direction.y << std::endl;
                    break;
                }
            }
        }
        // 値を返す
        return placeable_directions;
    }

    void Board::place(Position pos, Piece color) //設置処理。 checkPlaceableがtrueになっていることが前提。
    {
        std::vector<Position> placeable_directions = searchPlaceableDirections(pos, color);
        int size = placeable_directions.size();
        setPiece(pos, color);
        for (int i = 0; i < size; i++)
        {
            Position direction = placeable_directions[i];
            for (int d = 1; d < 8; d++)
            {

                Position checkpos = pos + direction * d;

                Piece checkcol = getPiece(checkpos);

                // 端の場合はループを抜ける
                if (checkpos.x > 7 || checkpos.x < 0)
                    break;
                if (checkpos.y > 7 || checkpos.y < 0)
                    break;

                if (checkcol == color && d >= 1) //自分の色だったらループ抜ける
                    break;

                if (checkcol == none) // 何もなかったらループ抜ける
                    break;

                //結果的に相手の色の場合のみ以下の処理が実行されるので、ひっくり返す(自分の色にする。)。
                setPiece(checkpos, color);
            }
        }
    }

    std::string Board::toString() // 盤面を文字列に変換
    {
        std::string r = " abcdefgh\n";
        Piece p;
        for (int y = 0; y < 8; y++)
        {
            r += std::to_string(y + 1);
            for (int x = 0; x < 8; x++)
            {
                p = getPiece(Position(x, y));
                switch (p)
                {
                case black:
                    r.append(piece_black_str);
                    break;
                case white:
                    r.append(piece_white_str);
                    break;
                case none:
                    r.append(piece_none_str);
                    break;

                default:
                    r.append("NULL");
                    break;
                }
            }
            r.push_back('\n');
        }
        return r;
    }

    std::string Board::toString(Piece guide) // 盤面を文字列に変換(ガイド付き)
    {
        std::string r = " abcdefgh\n";
        Piece p;
        for (int y = 0; y < 8; y++)
        {
            r += std::to_string(y + 1);
            for (int x = 0; x < 8; x++)
            {
                p = getPiece(Position(x, y));
                switch (p)
                {
                case black:
                    r.append(piece_black_str);
                    break;
                case white:
                    r.append(piece_white_str);
                    break;
                case none:
                    if (this->checkPlaceable(Position(x, y), guide))
                    {
                        r.append(piece_placeable_str);
                    }
                    else
                    {
                        r.append(piece_none_str);
                    }
                    break;
                default:
                    r.append("NULL");
                    break;
                }
            }
            r.push_back('\n');
        }
        return r;
    }

    std::string Board::toString(Piece guide, Position cursor)
    {
        std::string r = " abcdefgh\n";
        Piece p;
        for (int y = 0; y < 8; y++)
        {
            r += std::to_string(y + 1);
            for (int x = 0; x < 8; x++)
            {
                p = getPiece(Position(x, y));
                switch (p)
                {
                case black:
                    r.append(piece_black_str);
                    break;
                case white:
                    r.append(piece_white_str);
                    break;
                case none:
                    if (this->checkPlaceable(Position(x, y), guide))
                    {
                        r.append(piece_placeable_str);
                    }
                    else if (x == cursor.x && y == cursor.y)
                    {
                        r.append(cursor_str);
                    }
                    else
                    {
                        r.append(piece_none_str);
                    }
                    break;
                default:
                    r.append("NULL");
                    break;
                }
            }
            r.push_back('\n');
        }
        return r;
    }

    Piece Board::getPiece(Position position)
    {
        //std::cout << "getPiece" << position.x << position.y << std::endl;
        //範囲外へのアクセスを防ぐ
        if (position.x > 7 || position.x < 0 || position.y > 7 || position.y < 0)
            return outside;
        return board_map[position.y][position.x];
    }

    void Board::setPiece(Position position, Piece piece)
    {
        //std::cout << "setPiece" << position.x << position.y << std::endl;
        //範囲外へのアクセスを防ぐ
        if (!(position.x > 7 || position.x < 0 || position.y > 7 || position.y < 0))
            board_map[position.y][position.x] = piece;
    }
} // namespace Reversi

#endif