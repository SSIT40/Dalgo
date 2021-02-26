#if !defined LIST_H
#define LIST_H

template <typename TYPE>
class Node
{
public:
	TYPE data;
	Node* pNext;
};


//klassdeklaration
template <typename TYPE>
class List
{
public:
	List();
	~List();

	void insertFirst(const TYPE& rDataIn);
	void insertLast(const TYPE& rDataIn);
	void insertAt(const TYPE& rDataIn, int iPosition); // before insert

	bool deleteFirst();
	bool deleteLast();
	bool deleteAt(int iPosition);

	// Cursos based, mutate Active node pointer
	const Node<TYPE>* getFirstElement();
	const Node<TYPE>* getLastElement();
	const Node<TYPE>* getNextElement();

	void display() const;

	bool replaceElement(TYPE rElement, TYPE rnewElement, int& iPosition);

protected:
	void setup();

private:
	int m_iNumberOfElements;
	Node<TYPE>* m_pBegin;
	Node<TYPE>* m_pEnd;
	Node<TYPE>* m_pActive;
};

#endif