#include <vector>
#include <string>

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

        std::string piece_none_str;
        std::string piece_black_str;
        std::string piece_white_str;
        std::string piece_placeable_str;
        std::string cursor_str;

    public:
        Board();
        ~Board();
        Board(const Board &other);

        //メソッド
        bool checkPlaceable(Position position, Piece piece_color); //　特定の座標に石を置けるかチェックする。
        bool checkPlaceable(int x, int y, Piece piece_color);      //オーバーロード

        std::vector<Position> searchPlaceableDirections(Position position, Piece piece_color); //　石を置ける方向をvectorで返す。
        std::vector<Position> searchPlaceableDirections(int x, int y, Piece piece_color);      //オーバーロード

        void place(Position position, Piece piece_color); // 設置処理
        void place(int x, int y, Piece piece_color);      //オーバーロード

        std::string toString();                                   //文字列化 (ガイドなし)
        std::string toString(Piece guide_color);                  //　文字列化(ガイド付き)
        std::string toString(Piece guide_color, Position cursor); // 文字列化(カーソル, ガイド付き)

        bool checkPlaceableAnywhere(Piece color); //どこかに置くことができるか調べる(falseだったらどこにもおけない。)、色指定
        bool checkPlaceableAnywhere();            //どこかに置くことができるか調べる(色は問わない。)
        int countPiece(Piece color);              // 石の数を数える。

        int countPlaceablePositions(Piece color); // 石を置ける場所の数を数える
        int countPlaceableCorner(Piece color);    //角を置ける場所の数を数える。
        int countCorner(Piece color);             //角の数を数える。

        std::vector<Position> searchPlaceablePositions(Piece color); // 設置可能な位置を列挙

        //単純なアクセサ群
        Piece getPiece(Position position); //　座標からどうなってるか調べる。
        Piece getPiece(int x, int y);      //オーバーロード

        void setPiece(Position Position, Piece piece_color); //　任意の座標に任意の石を配置する。または石を除去する.
        void setPiece(int x, int y, Piece piece_color);      // オーバーロード

        //オペレータ
        //Board operator=(Board *other);
    };

    Board::Board() //コンストラクタ
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

        piece_black_str = "\e[0m\e[42m\e[30m●\e[0m";
        piece_white_str = "\e[0m\e[42m\e[37m●\e[0m";
        piece_none_str = "\e[0m\e[44m\e[32m■\e[0m";
        piece_placeable_str = "\e[0m\e[44m\e[32m□\e[0m";
        cursor_str = "\e[0m\e[42m\e[33m@\e[0m";
    }

    Board::Board(const Board &other)
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

        piece_black_str = "\e[0m\e[42m\e[30mb\e[0m";
        piece_white_str = "\e[0m\e[42m\e[37mw\e[0m";
        piece_none_str = "\e[0m\e[42m \e[0m";
        piece_placeable_str = "\e[0m\e[42m\e[33m.\e[0m";

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                this->board_map[y][x] = other.board_map[y][x];
                //std::cout << other.board_map[y][x] << std::endl;
            }
        }
    }

    Board::~Board()
    {
    }

} // namespace Reversi
#endif