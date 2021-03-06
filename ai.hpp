#include "./cpp_reversi.cpp"

#ifndef CR_2026DE3B_BB6E_4AA6_A4FA_70F2A82B45B4
#define CR_2026DE3B_BB6E_4AA6_A4FA_70F2A82B45B4
namespace Reversi
{
    class AI
    {
    public:
        //パラメータ
        float magnifcation;   //後手重視の倍率。 とりあえず0.1~0.2くらいがちょうどいい？
        int preloading_times; //先読みの回数

        float (*evaluation_function)(Board board, Piece color);  //評価関数
        AI(float (*efunc)(Board board, Piece color), int pt = 2) // コンストラクタ
        {
            evaluation_function = efunc; //評価関数ポインタを代入。
            magnifcation = 1.0;
            preloading_times = 2;
        }
        float evaluate_position(Board board, Position position, Piece color);    //1マスを評価する。
        float evaluate_board(Board board, Piece color, int count = 2);           //ボード全体を評価する (intは何手先まで読むか)
        Position predict_best_position(Board board, Piece color, int count = 0); //最適な位置を探索(計算)する (intは何手先まで読むか)

    private:
        static Piece
        getEnemyColor(Piece color); // 相手側の色を返す。
    };
} // namespace Reversi
#endif