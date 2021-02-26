#include <iostream>
using namespace std;

#include "stack.h"

int main()
{
	Stack<int> sensorValues;
	sensorValues.push(1);
	sensorValues.push(2);
	sensorValues.push(3);
	sensorValues.push(3);
	sensorValues.push(3);
	sensorValues.push(2);
	sensorValues.push(1);
	sensorValues.push(3);

	sensorValues.display();

	int count = sensorValues.countSameElements(3);
	cout << "number of elements containing 3 is: " << count << endl;

	system("pause");

	return 0 ;
}