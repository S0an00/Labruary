
#include <iostream>
using namespace std;
class Coordinates {
public:
    int x;
    int y;
    bool operator==(Coordinates& st){
        if (st.x == x && st.y == y)
            return true;
        else
            return false;
    }
    bool operator!=(Coordinates& st) {
        if (st.x == x && st.y == y)
            return false;
        else
            return true;
    }
    friend istream& operator>>(istream& st, Coordinates& then) {
        st >> then.x;
        st >> then.y;
        return st;
    }
    friend ostream& operator<<(ostream& st, Coordinates& then) {
        st << "x = " << then.x << endl;
        st << "y = " << then.y << endl;
        return st;
    }
    void poisk()
    {
        if (x > 0 && y > 0)
            cout << "Точка находится в первой четверти" << endl;
        else if (x < 0 && y>0)
            cout << "Точка находится во второй четверти" << endl;
        else if (x < 0 && y < 0)
            cout << "Точка находится в третьей четверти" << endl;
        else if (x > 0 && y < 0)
            cout << "Точка находится в четвертой четверти" << endl;
        else if (x == 0 && y == 0)
            cout << "Точка находится в центре" << endl;
    }
    void proverkaonLine(int A,int B,int C)
    {
        if ((A * x + B * y + C) == 0)
            cout << "Точка лежит на линии" << endl;
        else
            cout << "Точка не лежит на линии" << endl;
    }
};
int main()
{
    setlocale(LC_ALL, "RU");
    Coordinates qwe, asd;
    qwe = { 7,0 };
    asd = { 7,2 };
    qwe.proverkaonLine(3, 5, 0);
    cin >> qwe;
}