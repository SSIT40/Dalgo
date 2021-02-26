#include <iostream>

using namespace std;

#include "stack.h"
#include "List.h"


int main()
{
	List<int> numbers;

	numbers.insertFirst(10);
	numbers.insertLast(20);
	numbers.insertLast(30);

	numbers.display();
	//	pos
	//	1	2	3	4
	//	20	11	

	numbers.insertAt(11, 2);		//(data in, position)
	//	pos
	//	1	2	3	4
	//	10	11	20	
	numbers.display();

	numbers.deleteAt(2);
	numbers.display();


	const Node<int>* pTheNode = nullptr;

	pTheNode = numbers.getFirstElement();

	if (pTheNode != nullptr)
	{
		cout << "The content is " << endl;
		cout << "[ ";
		while (pTheNode != nullptr)
		{
			cout << pTheNode->data << " ";
			pTheNode = numbers.getNextElement();
		}
		cout << " ]" << endl;
	}
	else
	{
		cout << "numbers list is empty";
	}

	////////////////
	
	numbers.insertAt(4, 2);
	numbers.insertAt(7, 2);
	numbers.insertAt(5, 2);

	numbers.display();

	int elementToSearch = 5;
	int newElement = 7;
	int resultPosition = -1;
	bool found = false;
	found = numbers.replaceElement(elementToSearch, newElement, resultPosition);
	if (found == true)
	{  
		cout << "Element: " << elementToSearch << " was replaced with: " << newElement << " successfully!" << endl;
		numbers.display();
	}



	////////////////////////////////////////

	////			Stack				////

	////////////////////////////////////////



	const unsigned int uiStackSize = 4;

	Stack<double> aStack(uiStackSize);

	for (unsigned int uiIndex = 0; uiIndex < uiStackSize; uiIndex++)
	{
		aStack.push(uiIndex + 10);
	}

	double valueToSearch = 12;
	double newElement = 10;
	int resultIndex = -1;
	bool found = false;
	found = aStack.replaceElement(valueToSearch, newElement, resultIndex);
	if (found == true)
	{
		/* do something clever */
		cout << "The first found element is at index : " << resultIndex << endl;
	}

	return 0;
}