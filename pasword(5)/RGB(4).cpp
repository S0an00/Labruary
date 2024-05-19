
#include <iostream>
using namespace std;
class Password {
public:
	char pass[16];
	bool  operator!=(Password& st)
	{
		for (int i = 0; i < 16; i++)
		{
			if (pass[i] != st.pass[i])
			{
				return true;
			}
		}
		return false;
	}
	bool  operator==(Password& st)
	{
		for (int i = 0; i < 16; i++)
		{
			if (pass[i] != st.pass[i])
			{
				return false;
			}
		}
		return true;
	}
	void LvlPass() {
		int temp=0;
		int st=0;
		for (int i = 0; i < 16; i++)
		{
			if (pass[i] == NULL)
				break;
			if (pass[i] > 32 && pass[i] < 48)
				st++;
			temp++;
		}
		
		if (st>=3 && temp > 12)
			cout << "Надежный пароль" << endl;
		else if ((st>=1 && temp > 8) || (st==0 && temp > 8))
			cout << "Средний пароль" << endl;
		else if ((st==0 && temp <= 8)||(st<=3&&temp<=8))
			cout << "Слабый пароль" << endl;

	}

};
int main()
{
	setlocale(LC_ALL, "RU");
	Password adam, soan;
	adam = { '3','d','g','!','2','2','!','!','f','d','s','f','f'};
	soan = { '3','d','g','4','f','s'};
	adam.LvlPass();
}
