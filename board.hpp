#include "position.hpp"
#include "stone.hpp"

#ifndef CR_89a4880f_edc4_4925_b2dd_349f85b6de33
#define CR_89a4880f_edc4_4925_b2dd_349f85b6de33

namespace Reversi
{
    class Board
    {
    private:
        Stone board_map[8][8];

    public:
        Board();
        ~Board();
    };

    Board::Board()
    {
        // 盤面を初期化
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                board_map[y][x] = Stone::none;
            }
        }
        // 最初の４つの石を配置
        board_map[3][3] = Stone::white;
        board_map[4][4] = Stone::white;
        board_map[4][3] = Stone::black;
        board_map[3][4] = Stone::black;
        }

    Board::~Board()
    {
    }

} // namespace Reversi
#endif