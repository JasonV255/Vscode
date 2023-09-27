
#include <stdio.h>
#include <iostream>
using namespace std;

int a, m, n, i;
/*
void draw
{

}
void logic
{

}
*/
int main()
{
	cout << "Insert a non-negative integer: ";
	cin >> a;
	
	//Check if prime
	for (i = 2; i <= a/2; i++)
	{
		
		if (a % i != 0)
		{
			cout << "This is a prime number."; break;
		}
		else {

		}
	}
			

	cout << "\n";
	return 0;


}

