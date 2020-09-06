#ifndef CR_f055808d_4939_44b6_97d2_ff5c20b9b6dc
#define CR_f055808d_4939_44b6_97d2_ff5c20b9b6dc
namespace Reversi
{
    class Position
    {
    public:
        int x;
        int y;
        //計算
        Position operator+(Position other);
        Position operator-(Position other);
        Position operator*(int other);
        Position operator/(int other);

        Position(int x, int y); // コンストラクタ。
    };

    Position::Position(int x_, int y_)
    {
        x = x_;
        y = y_;
    }

} // namespace Reversi

#endif