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
    }

    Board::~Board()
    {
    }

} // namespace Reversi
#endif