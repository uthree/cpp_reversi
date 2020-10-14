#include "cpp_reversi.cpp"
#include <iostream>

using namespace Reversi;
using namespace std;
int main()
{
    Board b = Board();
    cout << "test" << endl;
    cout << b.toString() << endl;
    b.place(Position(3, 5), white);
    cout << b.toString() << endl;
    b.place(Position(2, 3), black);
    cout << b.toString() << endl;
    cout << b.countPiece(black) << endl;
    cout << b.searchPlaceablePositions(white).size() << endl;
    auto v = b.searchPlaceablePositions(white);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].x << " " << v[i].y << endl;
    }

    printf("正常終了");
    return 0;
}