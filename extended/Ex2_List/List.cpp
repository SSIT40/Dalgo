#include <iostream>


using namespace std;

#include"List.h"

template class List<int>;

template <typename TYPE>
List<TYPE>::List()
{
	setup();
}

template <typename TYPE>
List<TYPE>::~List()
{

}

template <typename TYPE>
void List<TYPE>::setup()
{
	m_iNumberOfElements = 0;
	m_pBegin=nullptr;
	m_pEnd=nullptr;
	m_pActive=nullptr;

}

template <typename TYPE>
void List<TYPE>::insertFirst(const TYPE& rDataIn)
{
	Node<TYPE>* pNewNode = new Node<TYPE>;
	pNewNode->data = rDataIn;
	pNewNode->pNext = nullptr;

	//insert before
	pNewNode->pNext = m_pBegin;
	m_pBegin = pNewNode;

	m_iNumberOfElements++;

	if (m_iNumberOfElements == 1)
		m_pEnd = pNewNode;

}


template <typename TYPE>
void List<TYPE>::insertLast(const TYPE& rDataIn)
{
	Node<TYPE>* pNewNode = new Node<TYPE>;
	pNewNode->data = rDataIn;
	pNewNode->pNext = nullptr;

	m_iNumberOfElements++;

	//insert after
	if (m_iNumberOfElements == 1)
		m_pBegin = pNewNode;
	else
		m_pEnd->pNext = pNewNode;

	m_pEnd = pNewNode;


	

}

template <typename TYPE>
void List<TYPE>::insertAt(const TYPE& rDataIn, int iPosition)
{
	if ((iPosition < 1) || (iPosition > m_iNumberOfElements + 1))
	{
		return;
	}

	if (iPosition == 1)
	{ 
		insertFirst(rDataIn);
		return;
	}

	if (iPosition == m_iNumberOfElements + 1)
	{
		insertLast(rDataIn);
		return;
	}

	Node<TYPE>* pNode = m_pBegin;
	for (int iCounter = 1; iCounter < iPosition - 1; iCounter++)
	{
		pNode = pNode->pNext;
	}

	Node<TYPE>* pNodeNext = nullptr;

	if (pNode != nullptr)
	{
		pNodeNext = pNode->pNext;
	}

	//	insert before
	Node<TYPE>* pNewNode = new Node<TYPE>;
	pNewNode->data = rDataIn;							///////////////////////// kan behövas i hemmuppg !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pNewNode->pNext = pNodeNext;

	if (pNode != nullptr)
	{
		pNode->pNext = pNewNode;
	}

	m_iNumberOfElements++;
}


template <typename TYPE>
void List<TYPE>::display() const
{
	const Node<TYPE>* pNode = m_pBegin;

	if (pNode == nullptr)
	{
		cout << "The list container is empty." << endl;
	}
	else
	{
		cout << "The content in the list container is: " << endl;
		cout << "[ ";
		while (pNode != nullptr)
		{
			cout << pNode->data << " - ";
			pNode = pNode->pNext;
		}
		cout << " ]" << endl;
	}
	return;
}


template <typename TYPE>
bool List<TYPE>::deleteFirst()
{
	if (m_iNumberOfElements == 0)
	{
		return false;
	}

	//assert()	någå som kan köras i debug mode
	Node<TYPE>* pDeleteNode = m_pBegin;
	if (m_pActive == pDeleteNode)
	{
		m_pActive = pDeleteNode->pNext;
	}

	m_pBegin = pDeleteNode->pNext;
	m_iNumberOfElements--;

	if (m_iNumberOfElements)
	{
		m_pEnd = nullptr;
	}

	delete pDeleteNode;
	return true;

}

template <typename TYPE>
bool List<TYPE>::deleteLast()
{
	return deleteAt(m_iNumberOfElements);
}

template <typename TYPE>
bool List<TYPE>::deleteAt(int iPosition)
{
	if ((iPosition < 1) || iPosition > m_iNumberOfElements)
	{
		return false;
	}

	if (iPosition == 1)
	{
		return deleteFirst();
	}

	Node<TYPE>* pPreDeleteNode = m_pBegin;

	for (int iCounter = 1; iCounter < iPosition - 1; iCounter++)
	{
		pPreDeleteNode = pPreDeleteNode->pNext;
	}

	Node<TYPE>* pDeleteNode = pPreDeleteNode->pNext;
	pPreDeleteNode->pNext = pDeleteNode->pNext;

	if (m_pActive == pDeleteNode)
	{
		m_pActive = pDeleteNode->pNext;
	}

	delete pDeleteNode;
	if (iPosition == m_iNumberOfElements)
	{
		m_pEnd = pPreDeleteNode;
	}

	m_iNumberOfElements--;

	return true;

}

template <typename TYPE>
const Node<TYPE>* List<TYPE>::getFirstElement()
{
	if (m_iNumberOfElements > 0)
	{
		m_pActive = m_pBegin;
	}
	else
	{
		m_pActive == nullptr;
	}

	return m_pActive;
}

template <typename TYPE>
const Node<TYPE>* List<TYPE>::getLastElement()
{
	if (m_iNumberOfElements > 0)
	{
		m_pActive = m_pEnd;
	}
	else
	{
		m_pActive == nullptr;
	}

	return m_pActive;
}

template <typename TYPE>
const Node<TYPE>* List<TYPE>::getNextElement()
{
	if (m_pActive == nullptr)
	{
		m_pActive = m_pBegin;
	}
	else
	{
		m_pActive = m_pActive->pNext;
	}

	return m_pActive;
}


////////////////////////////////////////////
////////		Hemuppg			////////////
////////////////////////////////////////////



/// rElement	== de gamla värde som man söker efter
/// rnewElement == nya värde som ersetter
/// iPosition	== var detta sker

template <typename TYPE>
bool List<TYPE>::replaceElement(TYPE rElement, TYPE rnewElement, int& iPosition)
{
	m_pActive = m_pBegin;	

	if (m_iNumberOfElements > 0)		// söker rElement
	{
		
		while (m_pActive != nullptr)
		{
			if (m_pActive->data == rElement)
			{
				////			HÄR SKA DEN BYTA INNEHÅLL		///
				m_pActive->data = rnewElement;



				return true;
			}
			else
			{
				m_pActive = m_pActive->pNext;
			}
		}

		// här kan de vara att det måste göras en logik för om while !true 
		return false;
	}
	else
	{
		m_pActive == nullptr;

		return false;
	}
	

	/*

	if (m_iNumberOfElements > 0)		// söker rElement
	{
		m_pActive = m_pBegin;

		if (m_pActive == nullptr)
		{
			m_pActive = m_pBegin;
		}
		else
		{
			m_pActive = m_pActive->pNext;
		}

		return m_pActive;
	}
	else
	{
		m_pActive == nullptr;

		return false;
	}

	



	if (iPosition == 1)		//		replace first		////////////////
	{
		if (m_iNumberOfElements > 0)
		{
			m_pActive = m_pBegin;
		}
		else
		{
			m_pActive == nullptr;
		}

		rElement = m_pBegin;
		if (m_pActive == pDeleteNode)
		{
			m_pActive = pDeleteNode->pNext;
		}

		m_pBegin = pDeleteNode->pNext;
		m_iNumberOfElements--;

		return //m_pActive;
	}


	*/
	
}