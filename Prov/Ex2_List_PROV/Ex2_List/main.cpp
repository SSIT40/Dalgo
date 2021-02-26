#include <iostream>
using namespace std;

#include "List.h"


int main()
{
	CList<int> theList;
	theList.insertLast(1);
	theList.insertLast(2);
	theList.insertLast(3);
	theList.insertLast(3);
	theList.insertLast(3);
	theList.insertLast(2);
	theList.insertLast(1);


	CList<int> inlist;
	inlist.insertLast(1);
	inlist.insertLast(2);
	inlist.insertLast(30);
	inlist.insertLast(30);
	inlist.insertLast(33);
	inlist.insertLast(3);
	inlist.insertLast(4);


	if (inlist.intersect(theList) == true)
	{
		cout << "something changed:" << endl;
		theList.display();
	}
	else
		cout << "No change" << endl;

	inlist.display();
	system("pause");
	return 0;
}