
#include <iostream>
#include <vector>
using namespace std;
class Matrix
{
public:
	int array[3][3] ;
	Matrix& operator=(const Matrix& other)
	{
		if (this != &other) {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					array[i][j] = other.array[i][j];
				}
			}
			
		}
		return *this;
	}
	Matrix& operator+=(Matrix& other)
	{
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->array[i][j]=this->array[i][j]+other.array[i][j];
			}
		}
		return  *this;
	}
	Matrix operator+(Matrix& other)
	{
		Matrix temp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp.array[i][j] = this->array[i][j] + other.array[i][j];
				cout << temp.array[i][j] << " ";
			}
		}
		return  temp;
	}
	Matrix operator-(Matrix& other)
	{
		Matrix temp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp.array[i][j] = this->array[i][j] - other.array[i][j];
			}
		}
		return  temp;
	}
	Matrix& operator-=(Matrix& other)
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->array[i][j] = this->array[i][j] - other.array[i][j];
			}
		}
		return  *this;
	}
	Matrix operator*(Matrix& other)
	{
		Matrix temp;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp.array[i][j] = this->array[i][j] * other.array[i][j];
			}
		}
		return  temp;
	}
	Matrix& operator*=(Matrix& other)
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->array[i][j] = this->array[i][j] * other.array[i][j];
			}
		}
		return  *this;
	}
	friend istream& operator>>(istream& enter,Matrix& obj )
	{

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				enter>>obj.array[i][j];
			}
		}
		return  enter;
	}
	friend ostream& operator<<(ostream& enter, const Matrix& temp)
	{
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				enter <<temp.array[i][j]<<" ";

			}
			cout << endl;
		}
		return enter;
	}
};

int main()
{
	Matrix mat1, mat2, mat3;
	mat1 = {3,5,7,8,3,4,5,2,6};
	mat2={ 4,1,2,1,5,3,2,1,4 };
	
	
}