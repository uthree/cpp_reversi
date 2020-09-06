#include <vector>

#include "position.hpp"
#include "piece.hpp"

#ifndef CR_89a4880f_edc4_4925_b2dd_349f85b6de33
#define CR_89a4880f_edc4_4925_b2dd_349f85b6de33

namespace Reversi
{
    class Board
    {
    private:
        Piece board_map[8][8];
        const Position eight_directions[8] = {
            {0, 1},
            {1, 1},
            {1, 0},
            {1, -1},
            {-1, 1},
            {0, -1},
            {-1, 0},
            {-1, -1},
        };

    public:
        Board();
        ~Board();
        bool Board::checkPlaceable(Position position, Piece piece_color);                    //特定の座標に石を置けるかチェックする。
        std::vector<Position> Board::searchPlaceableDirections(Position, Piece piece_color); //石を置ける方向をvectorで返す。
        Piece Board::getPieceFromPosition(Position position);
        void Place(Position position, Piece piece_color); // 設置処理
    };

    Board::Board()
    {
        // 盤面を初期化
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                board_map[y][x] = Piece::none;
            }
        }
        // 最初の４つの石を配置
        board_map[3][3] = Piece::white;
        board_map[4][4] = Piece::white;
        board_map[4][3] = Piece::black;
        board_map[3][4] = Piece::black;
    }

    Board::~Board()
    {
    }

} // namespace Reversi
#endif