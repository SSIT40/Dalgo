#if !defined LIST_H
#define LIST_H

template <typename TYPE>
class CNode
{
public:
	TYPE data;
	CNode *pNext;
};


// Klassdeklaration
template <typename TYPE>
class CList
{
public:
	CList(); 
	CList(TYPE elementArray[], unsigned int uiElementCount); 
	virtual ~CList(); 

	void insertFirst(const TYPE& rDataIn); 
	void insertLast(const TYPE& rDataIn); 
	void insertAt(const TYPE& rDataIn, int iPosition); // before insert

	bool deleteFirst(); 
	bool deleteLast(); 
	bool deleteAt(int iPosition); 

	bool getElementAt(TYPE& rElement, int iPosition) const;
	bool replaceElement(TYPE rElement, TYPE rNewElement, int& iPosition);
	
	// Non-const accessors DO mutate Active node pointer
	const CNode<TYPE>* getFirstElement();
	const CNode<TYPE>* getLastElement();
	const CNode<TYPE>* getElementAt(int iPosition);
	const CNode<TYPE>* getNextElement(); 
	
	int length() const; 
	void display() const; 

	// PROV
	bool intersect(const CList<TYPE>& inList);
	
protected:
	void setup();
	void cleanup();

	// helpers
	CNode<TYPE>* getFirstActiveElement();
	CNode<TYPE>* getNextActiveElement();

	
private:
	int m_iNumberOfElements; 
	CNode<TYPE>* m_pBegin; 
	CNode<TYPE>* m_pEnd; 
	CNode<TYPE>* m_pActive; // positionspointer for getNext()
};

#endif