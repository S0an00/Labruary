
#include <iostream>
using namespace std;
class RGB_Chanel
{
private:
    bool red;
    bool blue;
    bool green;
public:
    bool operator==(RGB_Chanel& obj)
    {
        if (this->red == obj.red && this->blue == obj.blue && this->green == obj.green)
            return true;
        else
            return false;
    }
    bool operator!=(RGB_Chanel& obj)
    {
        if (this->red != obj.red || this->blue != obj.blue || this->green != obj.green)
            return true;
        else
            return false;
    }
    friend istream& operator>>(istream& st,RGB_Chanel& obj)
    {
        st >> obj.red;
        st >> obj.blue;
        st >> obj.green;
        return st;
    }
    friend ostream& operator<<(ostream& st, RGB_Chanel& obj)
    {
        if (obj.red == 1 && obj.blue == 1 && obj.green == 1)
        {
            st << "Ваша лента белого цвета" << endl;
            return st;
        }
        else if (obj.red == 1 && obj.blue == 1 && obj.green == 0)
        {
            st << "Ваша лента фиолетового цвета" << endl;
            return st;
        }
        else if (obj.red == 1 && obj.blue == 0 && obj.green == 1)
        {
            st << "Ваша лента желтого цвета" << endl;
            return st;
        }
        else if (obj.red == 0 && obj.blue == 1 && obj.green == 1)
        {
            st << "Ваша лента голубого цвета" << endl;
            return st;
        }
        else if (obj.red == 1 && obj.blue == 0 && obj.green == 0)
        {
            st << "Ваша лента красного цвета" << endl;
            return st;
        }
        else if (obj.red == 0 && obj.blue == 1 && obj.green == 0)
        {
            st << "Ваша лента синего цвета" << endl;
            return st;
        }
        else if (obj.red == 0 && obj.blue == 0 && obj.green == 1)
        {
            st << "Ваша лента зеленого цвета" << endl;
            return st;
        }
    }
};
int main()
{
    setlocale(LC_ALL, "RU");
    RGB_Chanel ll;
    cin >> ll;
    cout << ll;
}
