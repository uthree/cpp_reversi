#include "position.hpp"

#ifndef CR_b39d2c13_9d40_4250_832f_e102d43f9f6b
#define CR_b39d2c13_9d40_4250_832f_e102d43f9f6b
namespace Reversi
{
    //ベクトルの加算減算に近いもの
    Position Position::operator+(Position other)
    {
        return Position(x + other.x, x + other.x);
    }
    Position Position::operator-(Position other)
    {
        return Position(x - other.x, x - other.x);
    }
    // ベクトルのスカラー倍みたいなもの。
    Position Position::operator*(int other)
    {
        return Position(x * other, y * other);
    }
    Position Position::operator/(int other)
    {
        return Position(x / other, y / other);
    }

} // namespace Reversi

#endif