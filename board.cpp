#include "board.hpp"

#ifndef CR_8bd0d938_8918_4e2e_8ee7_64419c741770
#define CR_8bd0d938_8918_4e2e_8ee7_64419c741770

namespace Reversi
{
    bool Board::checkPlaceable(Position position, Piece piece_color)
    {
    }
    std::vector<Position> Board::searchPlaceableDirections(Position, Piece piece_color)
    {
        //ベクトルを初期化
        std::vector<Position> placeable_directions;
        // 8方向を探索する。
        for (int i = 0; i < 8; i++)
        {
            Position direction = eight_directions[i];
            for (int d = 0; d < 8; d++)
            {
            }
        }
    }

    void Place(Position position, Piece piece_color)
    {
    }

    Piece Board::getPiece(Position position)
    {
    }

    void Board::setPiece(Position position, Piece piece_color)
    {
    }
} // namespace Reversi

#endif