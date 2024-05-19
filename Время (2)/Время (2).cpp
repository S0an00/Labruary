
#include <iostream>
using namespace std;
class Time
{   
public:
    int hour;
    int minytes;
    int sec;
    /*()
    {
        if (this->sec >= 60)
        {
            this->time+=(this->sec % 60);
        }
        if (this->time >= 60)
        {
            this->hour += this->time / 60;
            this->time %= 60;
        }
        if (this->hour >= 24)
        {
            this->hour %= 24;
        }
    }*/
   
    Time& operator+(Time& obj)
    {
        Time temp;
        temp.hour=this->hour + obj.hour;
        temp.sec = this->sec + obj.sec;
        temp.minytes = this->minytes + obj.minytes;
        return temp;
    }
    Time& operator-(Time& obj)
    {
        Time temp;
        temp.hour = this->hour - obj.hour;
        temp.sec = this->sec - obj.sec;
        temp.minytes = this->minytes - obj.minytes;
        return temp;
    }
    Time& operator-=(Time& obj)
    {
        this->hour = this->hour - obj.hour;
        this->sec = this->sec - obj.sec;
        this->minytes = this->minytes - obj.minytes;
        return *this;
    }
    Time& operator+=(Time& obj)
    {
        this->hour = this->hour + obj.hour;
        this->sec = this->sec + obj.sec;
        this->minytes = this->minytes + obj.minytes;
        return *this;
    }
    friend ostream& operator<<(ostream& st,const Time& obj)
    {
        st << obj.hour<<" "<< obj.minytes<<" "<< obj.sec;
        return st;
    }
    friend istream& operator>>(istream& st, Time& obj)
    {
        st >> obj.hour;
        st >> obj.minytes;
        st >> obj.sec;
        return st;
    }
    bool operator>(Time& st)
    {
        int temp,temp2;
        temp = hour * 3600+minytes*60+sec;
        temp2 = st.hour * 3600 + st.minytes * 60 + st.sec;

        return temp > temp2;
    }
    bool operator<(Time& st)
    {
        int temp, temp2;
        temp = hour * 3600 + minytes * 60 + sec;
        temp2 = st.hour * 3600 + st.minytes * 60 + st.sec;

        return temp < temp2;
    }
    bool operator!=(Time& st)
    {
        int temp, temp2;
        temp = hour * 3600 + minytes * 60 + sec;
        temp2 = st.hour * 3600 + st.minytes * 60 + st.sec;

        return temp != temp2;
    }
    bool operator==(Time& st)
    {
        int temp, temp2;
        temp = hour * 3600 + minytes * 60 + sec;
        temp2 = st.hour * 3600 + st.minytes * 60 + st.sec;

        return temp == temp2;
    }
    void PerevodVremeny(Time& st) {
        if (st.hour > 12)
            cout << st.hour%12 << " " << st.minytes << " " << st.sec << " PM" << endl;
        else
            cout << st.hour << " " << st.minytes << " " << st.sec << " AM" << endl;
    }
    void Hour12 (Time& st) {
        if (st.hour < 12)
            cout << st.hour << " " << st.minytes << " " << st.sec <<" AM" << endl;
        else 
            cout << st.hour << " " << st.minytes << " " << st.sec <<" PM"<< endl;
    }
};
int main()
{
    Time moscow, newyourk,free;
    
    moscow = {13,2,6 };
    newyourk = { 12,0,0};
    moscow.PerevodVremeny(moscow);
}
