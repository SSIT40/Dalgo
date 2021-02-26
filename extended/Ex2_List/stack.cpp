#include "stack.h"

#include <iostream>
using namespace std;

// instanciate template TYPE 
template class Stack<double>;


template <typename TYPE>
Stack<TYPE>::Stack()
{
	m_elements = nullptr;
	setup(10);
}

template <typename TYPE>
Stack<TYPE>::Stack(int maxSize)
{
	m_elements = nullptr;
	setup(maxSize);
}

template <typename TYPE>
Stack<TYPE>::Stack(const Stack<TYPE>& fromStack)
{
	m_elements = nullptr;
	clone(fromStack);
}

template <typename TYPE>
Stack<TYPE>::~Stack()
{
	if (m_elements != 0)
		delete[] m_elements;
}

template <typename TYPE>
bool Stack<TYPE>::top(TYPE& element) const
{
	if (m_topIndex >= 0)
	{
		element = m_elements[m_topIndex];
		return true;
	}
	else
		return false;
}

template <typename TYPE>
bool Stack<TYPE>::pop(TYPE& element)
{
	if (top(element) == true)
	{
		m_topIndex--;
		return true;
	}
	else
		return false;

}

template <typename TYPE>
bool Stack<TYPE>::getElement(TYPE& element, int index) const
{
	if (index<0 || index>m_topIndex)
		return false;
	else
	{
		element = m_elements[index];
		return true;
	}
}

template <typename TYPE>
bool Stack<TYPE>::push(TYPE element)
{
	if (m_topIndex < (m_maxSize - 1))
	{
		m_topIndex++;
		m_elements[m_topIndex] = element;
		return true;
	}
	else
		return false;
}

template <typename TYPE>
bool Stack<TYPE>::empty() const
{

	if (size() == 0)
		return true;
	else
		return false;
}

template <typename TYPE>
int Stack<TYPE>::size() const
{
	return m_topIndex + 1;
}

template <typename TYPE>
int Stack<TYPE>::maxSize() const
{
	return m_maxSize;
}

template <typename TYPE>
bool Stack<TYPE>::resize(int maxSize)
{
	int iOriginalElementCount = m_topIndex + 1;
	unsigned int uiCopyElementCount = 0;

	// How many elements should we copy? 
	if (iOriginalElementCount < maxSize)
		// The new array is bigger then the old array, copy all old elements  
		uiCopyElementCount = iOriginalElementCount;
	else
		// The new array is smaller then the old array, copy upto new size  
		uiCopyElementCount = maxSize;

	// temporary array, using new due to unknown size at compiler time
	double* tempArray = new double[maxSize];
	for (unsigned int uiIndex = 0; uiIndex < uiCopyElementCount; uiIndex++)
		tempArray[uiIndex] = m_elements[uiIndex];

	// clean up old memory and allocate new memory ( ie setting the pointer to point to a new memory, up to maxSize, which may be smaller then uiELementCount)
	setup(maxSize);

	// insert back the original elements
	for (unsigned int uiIndex = 0; uiIndex < uiCopyElementCount; uiIndex++)
		m_elements[uiIndex] = tempArray[uiIndex];

	// We need to fix this one due to the setup method resetting the topindex to -1
	m_topIndex = uiCopyElementCount - 1;

	// free temporary memory
	delete[] tempArray;

	// signal success
	return true;

}

template <typename TYPE>
void Stack<TYPE>::clear()
{
	m_topIndex = -1;
}

template <typename TYPE>
void Stack<TYPE>::display() const
{
	if (size() == 0)
		cout << "The stack container is empty." << endl;
	else
	{
		cout << "The content in the stack container is:" << endl;
		for (int iIndex = 0; iIndex <= m_topIndex; iIndex++)
		{
			cout << "elements [" << iIndex << "]=" << m_elements[iIndex] << " " << endl;
		}
		cout << endl;
	}
}

// Operators
template <typename TYPE>
Stack<TYPE>& Stack<TYPE>::operator=(const Stack<TYPE>& rhsStack)
{
	if (this != &rhsStack)
		clone(rhsStack);

	return *this;
}

template <typename TYPE>
bool Stack<TYPE>::operator==(const Stack<TYPE>& rhsStack) const
{
	// if amount of elements are different then they can be similar
	if (size() != rhsStack.size())
		return false;

	bool bCheckResult = true; //assume positiv logic, ie the stacks are alike
	unsigned int uiSize = size();

	double dTempStorage = 0.0;
	for (unsigned int uiIndex = 0; uiIndex < uiSize; uiIndex++)
	{
		bCheckResult = rhsStack.getElement(dTempStorage, uiIndex);
		if (m_elements[uiIndex] != dTempStorage)
		{
			// As soon as one element is different the whole stack is different
			bCheckResult = false;
			break;
		}
	}
	return bCheckResult;
}

// Helpers
template <typename TYPE>
void Stack<TYPE>::setup(int maxSize)
{
	m_topIndex = -1;
	m_maxSize = maxSize;

	if (m_elements != 0)
		delete[] m_elements;

	m_elements = new double[m_maxSize];
}

template <typename TYPE>
void Stack<TYPE>::clone(const Stack& fromStack)
{
	int iMaxSize = fromStack.maxSize();
	int iSize = fromStack.size();

	setup(iMaxSize);

	double dTempStorage = 0.0;
	for (int uiIndex = 0; uiIndex < iSize; uiIndex++)
	{
		fromStack.getElement(dTempStorage, uiIndex);
		push(dTempStorage);
	}
}


template <typename TYPE>
bool Stack<TYPE>::replaceElement(TYPE searchElement, TYPE newElement, int& index)
{
	Stack<double> tempStack;
	double test;
	bool result = false;

	for (int i = 0; i < m_maxSize; i++)
	{
		test = m_elements[i];
		tempStack.push(test);


		if (test = searchElement)
		{
			// ändra värdet
			tempStack.push(newElement);
			index = i;
			result = true;
		}
		else
		{
			tempStack.push(test);
		}

	}

	for (int i = 0; i < m_maxSize; i++)
	{
		m_elements[i] = tempStack[i];		// Vet int vad jag skall göra här för att fylla stacken med rätt data
	}

	return result;
}