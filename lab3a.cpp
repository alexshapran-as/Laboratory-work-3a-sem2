#include <iostream>
#include <string.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

class Vector 
{
	int *p;
	int size;

public:
	Vector(int *p, int size)
	{
		this->size = size; 
		this->p = new int[size];
		for (unsigned int i = 0; i < size; ++i ) 
			{ 
				this->p[i] = p[i];
			}
	}
	
	void print()
	{
		for (unsigned int i = 0; i < size; ++i) cout << p[i] << " ";
	}
	
	Vector() { p = 0; size = 0; }

	Vector & operator =(Vector& v1) 
	{
		size = v1.size;
		p = new int[size];
		for (unsigned int i = 0; i < size; ++i) p[i] = v1.p[i];
		return *this;
	}


	~Vector()
	{
		if ( size > 0 ) delete [] p;

	}

	friend Vector & operator^( Vector &v1, int* array);
	
};

int convTo(int bin_number,int dec_number)
		{
   			if (dec_number < bin_number) return dec_number;
   			else return convTo(bin_number,dec_number/bin_number)*10+dec_number%bin_number;   
		}

Vector & operator^( Vector &v1, int* array )
	{
		int* m = new int[v1.size];
		int** c = new int*[v1.size];
		int a = 0;
		int b = 0;
		int k = 0;

		for (unsigned int i = 0; i < v1.size; ++i) 
			{
				
				a = convTo(2,v1.p[i]); 
				b = convTo(2,array[i]);
				if ( a > b )
				{
					while ( a > 0 )
					{
						k++;
						a = a/10;
					}
				}
				else if ( b > a )
				{
					while ( b > 0 )
					{
						k++;
						b = b/10;
					}
				}
				else 
				{
					while ( a > 0 )
					{
						k++;
						a = a/10;
					}
				}
					a = convTo(2,v1.p[i]); 
					b = convTo(2,array[i]);
					c[i] = new int[k+1];
					m[i] = 0;
				for ( unsigned int j = k; j > 0; --j )
				{ 
					if ( (a%10+b%10) > 1 ) c[i][j] = 0;
					else if ( (a%10+b%10) == 1 ) c[i][j] = 1;
					else c[i][j] = 0;
					m[i] = m[i]+c[i][j]*pow(2,k-j);
					a = a / 10;
					b = b / 10;
				}
				
			}

		Vector *pV = new Vector( m, v1.size); 
		delete[] m;
		for (unsigned int i = 0; i < v1.size; ++i) delete c[i]; 
			delete []c;
		return *pV;
	}

int main(void)
{
	int size = 0;
	cout << endl << "Print the size of array-Vector: ";
	cin >> size;

	int *array = new int[size];
	cout << endl << "Print the elements of array(int*): ";
	for (unsigned int i = 0; i < size; ++i ) 
		{ 
			cout << endl << "Element " << i+1 << " = "; cin >> array[i]; 
		}
	cout << endl << "array(int*): ";
	for (unsigned int i = 0; i < size; ++i ) { cout << array[i] << " ";}
	cout << endl;

	int *array_v = new int[size];
	cout << endl << "Print the elements of array-Vector: "; 
	for (unsigned int i = 0; i < size; ++i ) 
		{ 
			cout << endl << "Element " << i+1 << " = "; cin >> array_v[i];
		}
	cout << endl << "array-Vector: ";
	Vector v1(array_v, size);
	v1.print();

	cout << endl << endl << "XOR: ";
	Vector v2;
	for (unsigned int i = 0; i < size; ++i ) v2 = v1 ^ array;
	v2.print();

	delete [] array;
	return 0;
}