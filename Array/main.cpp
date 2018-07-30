#include <iostream>
#include "Array.h"
using namespace std;

int main()
{
    Array<int>* arr = new Array<int>();
	for(int i = 0 ; i < 10 ; i ++)
    {
        arr->Addlast(i);
		Showarray(arr);
    }
    for(int i = 0 ; i < 8 ; i ++)
	{
        arr->Removefirst();
        Showarray(arr);
	}
	return 0;
}

template <class T>
void Showarray(Array<T>* arr)
{
	for(int i = 0 ; i < arr->Getsize() ; i ++)
	{
		cout << arr->Getdata(i) << ",";
	}
	cout << "capacity:" << arr->Getcapacity() <<endl;
}
