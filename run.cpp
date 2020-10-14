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

    printf("正常終了");
    return 0;
}