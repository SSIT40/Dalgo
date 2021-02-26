
#include <iostream>
using namespace std;

#include "List.h"

// instanciate template TYPE 
template class CList<int>;
template class CList<float>;
template class CList<double>;


template <typename TYPE>
CList<TYPE>::CList()
{
	setup();
}

template <typename TYPE>
CList<TYPE>::CList(TYPE elementArray[], unsigned int uiElementCount)
{
	setup();

	for (unsigned int uiIndex = 0; uiIndex < uiElementCount; uiIndex++)
		insertLast(elementArray[uiIndex]);
}

template <typename TYPE>
void CList<TYPE>::setup()
{
	m_pBegin = nullptr;
	m_pEnd = nullptr;
	m_pActive = nullptr;
	m_iNumberOfElements = 0;
}


template <typename TYPE>
CList<TYPE>::~CList()
{
	cleanup();
}

template <typename TYPE>
void CList<TYPE>::insertFirst(const TYPE& rDataIn)
{
	CNode<TYPE> *pNewNode = new CNode<TYPE>;
	pNewNode->data = rDataIn;
	pNewNode->pNext = nullptr;

	// Insert BEFORE
	pNewNode->pNext = m_pBegin;
	m_pBegin = pNewNode;

	m_iNumberOfElements++;
	if (m_iNumberOfElements == 1)
		m_pEnd = pNewNode;
}


template <typename TYPE>
void CList<TYPE>::insertLast(const TYPE& rDataIn)
{
	CNode<TYPE> *pNewNode = new CNode<TYPE>;
	pNewNode->data = rDataIn;
	pNewNode->pNext = nullptr;

	m_iNumberOfElements++;

	// Insert AFTER, due to this being the first one!
	if (m_iNumberOfElements == 1)
		m_pBegin = pNewNode;
	else
		m_pEnd->pNext = pNewNode;
	
	m_pEnd = pNewNode;
}


template <typename TYPE>
void CList<TYPE>::insertAt(const TYPE& rDataIn, int iPosition)
{
	// +1 for insert after the last one
	if (iPosition<1 || iPosition>m_iNumberOfElements+1)
		return;

	if (iPosition == 1) 
	{
		insertFirst(rDataIn);
		return;
	}

	if (iPosition == m_iNumberOfElements+1) 
	{
		insertLast(rDataIn);
		return;
	}

	CNode<TYPE> *pNode = m_pBegin;
	
	// The position -1 puts it in before that position
	for (int iCounter = 1; iCounter < iPosition - 1; iCounter++)
		pNode = pNode->pNext;

	CNode<TYPE> *pNodeNext = nullptr;
	// account for not nullptr next node
	if (pNode != nullptr)
		pNodeNext = pNode->pNext;

	// This is insert BEFORE
	CNode<TYPE> *pNewNode = new CNode <TYPE>;
	pNewNode->data = rDataIn;
	pNewNode->pNext = pNodeNext;

	if (pNode != nullptr)
		pNode->pNext = pNewNode;
	
	m_iNumberOfElements++;
}

template <typename TYPE>
bool CList<TYPE>::deleteFirst()
{
	if (m_iNumberOfElements == 0)
		return false;

	CNode<TYPE> *pDeleteNode = m_pBegin;

	if (m_pActive == pDeleteNode)
		m_pActive = pDeleteNode->pNext;

	m_pBegin = pDeleteNode->pNext;
	m_iNumberOfElements--;
	
	if (m_iNumberOfElements == 0)
		m_pEnd = nullptr;

	delete pDeleteNode;
	return true;
}

template <typename TYPE>
bool CList<TYPE>::deleteLast()
{
	return deleteAt(m_iNumberOfElements);
}

template <typename TYPE>
bool CList<TYPE>::deleteAt(int iPosition)
{
	if (iPosition<1 || iPosition>m_iNumberOfElements)
		return false;

	if (iPosition == 1)
		return deleteFirst();

	CNode<TYPE> *pPreDeleteNode = m_pBegin;
	// step forward to the one before the node to delete
	for (int iCounter = 1; iCounter < iPosition - 1; iCounter++)
		pPreDeleteNode = pPreDeleteNode->pNext;

	CNode<TYPE> *pDeleteNode = pPreDeleteNode->pNext;
	pPreDeleteNode->pNext = pDeleteNode->pNext;

	if (m_pActive == pDeleteNode)
		m_pActive = pDeleteNode->pNext;

	delete pDeleteNode;

	if (iPosition == m_iNumberOfElements)
		m_pEnd = pPreDeleteNode;

	m_iNumberOfElements--;
	return true;
}

template <typename TYPE>
void CList<TYPE>::display() const
{
	const CNode<TYPE>* pNode = m_pBegin;
	
	if (pNode == nullptr)
		cout << "The list container is empty." << endl;
	else
	{
		cout << "The content in the list container is:" << endl;
		cout << "[ "; 

		while (pNode != nullptr)
		{
			cout << pNode->data << "  ";
			pNode = pNode->pNext;
		}

		cout << " ]";
		cout << endl;
	}
	
}

template <typename TYPE>
void CList<TYPE>::cleanup(void)
{
	while (deleteFirst()==true) 
		;
	setup();
}

template <typename TYPE>
const CNode<TYPE>* CList<TYPE>::getNextElement()
{
	if (m_pActive == nullptr)
		m_pActive = m_pBegin;
	else
		m_pActive = m_pActive->pNext;
	return m_pActive;
}


template <typename TYPE>
const CNode<TYPE>* CList<TYPE>::getFirstElement()
{
	if (m_iNumberOfElements > 0)
		m_pActive = m_pBegin;
	else
		m_pActive = nullptr;

	return m_pActive;
}

template <typename TYPE>
const CNode<TYPE>* CList<TYPE>::getLastElement() 
{
	
	if (m_iNumberOfElements > 0)
		m_pActive = m_pEnd;
	else
		m_pActive = nullptr;

	return m_pActive;
}

template <typename TYPE>
CNode<TYPE>* CList<TYPE>::getNextActiveElement()
{
	if (m_pActive == nullptr)
		m_pActive = m_pBegin;
	else
		m_pActive = m_pActive->pNext;
	return m_pActive;
}


template <typename TYPE>
CNode<TYPE>* CList<TYPE>::getFirstActiveElement()
{
	if (m_iNumberOfElements > 0)
		m_pActive = m_pBegin;
	else
		m_pActive = nullptr;

	return m_pActive;
}

template <typename TYPE>
bool CList<TYPE>::replaceElement(TYPE rElement, TYPE rnNewElement, int& iPosition)
{
	bool bFoundElement = false;
	CNode<TYPE>* pTheNode = nullptr;

	pTheNode = getFirstActiveElement();
	int position = 0;
	while (pTheNode != nullptr)
	{
		position++;
		if (pTheNode->data == rElement)
		{
			if (bFoundElement == false)
				iPosition = position;
			bFoundElement = true;
			pTheNode->data = rnNewElement;
		}

		pTheNode = getNextActiveElement();
	}

	return bFoundElement;
}

template <typename TYPE>
const CNode<TYPE>* CList<TYPE>::getElementAt(int iPosition) 
{
	// No change if not in range
	if (iPosition<1 || iPosition>m_iNumberOfElements)
		return 0;

	CNode<TYPE>* pTheNode = m_pBegin;
	for (int iCounter = 1; iCounter < iPosition; iCounter++)
		pTheNode = pTheNode->pNext;

	m_pActive = pTheNode;
	
	return m_pActive;
}

template <typename TYPE>
bool CList<TYPE>::getElementAt(TYPE& rElement, int iPosition) const
{
	if (iPosition<1 || iPosition>m_iNumberOfElements)
		return false;

	CNode<TYPE>* pTheNode = m_pBegin;
	for (int iCounter = 1; iCounter < iPosition; iCounter++)
		pTheNode = pTheNode->pNext;

	if (pTheNode != nullptr)
	{
		rElement = pTheNode->data;
		return true;
	}
	else
		return false;
}


template <typename TYPE>
int CList<TYPE>::length() const
{
	return m_iNumberOfElements;
}


////////////////////////////////////////////////////////////////////////
// PROV
template <typename TYPE>
bool CList<TYPE>::intersect(const CList<TYPE>& inList)
{
	bool bFoundElement = false;
	CNode<TYPE>* pTheNode = nullptr;	
	CNode<TYPE>* pInNode = nullptr;

	pTheNode = getFirstActiveElement();
	pInNode = inList.m_pBegin;

	int position = 1;
	bool test = true;

	while (pTheNode != nullptr && position <= m_iNumberOfElements)
	{
		while (pInNode != nullptr)
		{
			if (pTheNode->data == pInNode->data)
			{
				test = true;
			}			
			pInNode = pInNode ->pNext;
		}


		pTheNode = pTheNode->pNext;
		
		if (test != true)
		{
			deleteAt(position);
			bFoundElement = true;			
		}
		else
		{
			position++;			
			test = false;
		}	
		pInNode = inList.m_pBegin;		
	}

	return bFoundElement;
}
