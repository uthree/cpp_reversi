#include <vector>
#include <string>

#include "position.cpp"
#include "piece.hpp"

#ifndef CR_89a4880f_edc4_4925_b2dd_349f85b6de33
#define CR_89a4880f_edc4_4925_b2dd_349f85b6de33

namespace Reversi
{
    class Board
    {
    private:
        Piece board_map[8][8];
        Position eight_directions[8] = {
            Position(1, 1),
            Position(0, 1),
            Position(1, 0),
            Position(1, -1),
            Position(-1, 1),
            Position(-1, -1),
            Position(-1, 0),
            Position(0, -1),

        };

    public:
        Board();
        ~Board();

        //メソッド
        bool checkPlaceable(Position position, Piece piece_color);                    //　特定の座標に石を置けるかチェックする。
        std::vector<Position> searchPlaceableDirections(Position, Piece piece_color); //　石を置ける方向をvectorで返す。
        void place(Position position, Piece piece_color);                             // 設置処理
        std::string toString();                                                       //　文字列化(簡易)
        bool checkPlaceableAnywhere(Piece color);                                     //どこかに置くことができるか調べる(falseだったらどこにもおけない。)
        int countPiece(Piece color);                                                  // 石の数を数える。
        std::vector<Position> searchPlaceablePositions(Piece color);                  // 設置可能な位置を列挙

        //単純なアクセサ群
        Piece getPiece(Position position);                   //　座標からどうなってるか調べる。
        void setPiece(Position Position, Piece Piece_color); //　任意の座標に任意の石を配置する。または石を除去する.
    };

    Board::Board()
    {
        // 盤面を初期化
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                board_map[y][x] = none;
            }
        }
        // 最初の４つの石を配置
        board_map[3][3] = white;
        board_map[4][4] = white;
        board_map[4][3] = black;
        board_map[3][4] = black;
    }

    Board::~Board()
    {
    }

} // namespace Reversi
#endif