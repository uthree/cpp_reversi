#ifndef CR_f055808d_4939_44b6_97d2_ff5c20b9b6dc
#define CR_f055808d_4939_44b6_97d2_ff5c20b9b6dc
namespace Reversi
{
    class Position
    {
    public:
        int x;
        int y;
        Position operator+();
        Position operator-();
    };

} // namespace Reversi

#endif