
#include <iostream>
using namespace std;
class Vklad
{
public:
    int SumSber=0;
    int Srok=365;
    float Stavka=12;// 12%  годовых
    void OperationSber(Vklad& st) {//расчет дохода
        cout << "Ваш годовой доход: " << st.SumSber * (st.Stavka / 100)<<endl;
    }
    void SnatieMon(Vklad& obj) {//снятие
        cout << "Введите сумму , которую хотите cнять : ";
        int sum = 0;
        cin >> sum;
        obj.SumSber -= sum;
        cout << "Ваш счет составляет : " << obj.SumSber << endl;

    }
    void Popolnenye(Vklad& obj) {//полнение
        cout << "Введите сумму , которую хотите внести : ";
        int sum;
        cin >> sum;
        obj.SumSber += sum;
        cout << "Ваш счет составляет : " << obj.SumSber << endl;
    }
    friend ostream& operator<<(ostream& st, Vklad& obj) {
        cout << "Сумма ваших сбережений: " << obj.SumSber << endl;
        cout << "Срок вклада: " << obj.Srok << endl;
        cout << "Ставка (годовая): " << obj.Stavka << endl;
        return st;
    }
    Vklad& operator+(Vklad& obj)
    {
        Vklad temp;
        temp.SumSber = this->SumSber + obj.SumSber;
        return temp;
    }
    Vklad& operator-(Vklad& obj)
    {
        Vklad temp;
        temp.SumSber = this->SumSber - obj.SumSber;
        return temp;
    }
};
int main()
{
    setlocale(LC_ALL, "RU");
    Vklad DF;
    DF.SumSber = 100000;
    DF.OperationSber(DF);
}