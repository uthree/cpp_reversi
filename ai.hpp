#include "./cpp_reversi.cpp"

#ifndef CR_2026DE3B_BB6E_4AA6_A4FA_70F2A82B45B4
#define CR_2026DE3B_BB6E_4AA6_A4FA_70F2A82B45B4
namespace Reversi
{
    class AI
    {
    public:
        float (*evaluation_function)(Board board, Piece color); //評価関数
        AI(float (*efunc)(Board board, Piece color))            // コンストラクタ
        {
            evaluation_function = efunc; //評価関数ポインタを代入。
        }
        float evaluate_position(Board board, Position position, Piece color); //1マスを評価する。
        float evaluate_board(Board board, Piece color, int count);            //ボード全体を評価する

    private:
        static Piece getEnemyColor(Piece color); // 相手側の色を返す。
    };
} // namespace Reversi
#endif