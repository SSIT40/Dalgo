#if !defined STACK_H
#define STACK_H

template <typename TYPE>
class Stack
{
public:
	Stack(); // default constructor
	Stack(int maxSize); //
	Stack(const Stack<TYPE>& fromStack);
	virtual ~Stack();

	bool top(TYPE& element) const; // get the element
	bool pop(TYPE& element); // removes the element
	bool getElement(TYPE& element, int index) const;

	bool push(TYPE element);

	bool empty() const;

	int size() const;
	int maxSize() const;
	bool resize(int maxSize);

	void clear();

	void display() const;
		
	Stack<TYPE>& operator=(const Stack<TYPE>& rhsStack);	
	bool operator==(const Stack<TYPE>& rhsStack) const;

	bool replaceElement(TYPE searchElement, TYPE newElement, int& index);

	// Provet		///
	int countSameElements(const TYPE& searchValue) const;


protected:
	void setup(int maxSize); // if elements != 0 will nuke it
	void clone(const Stack& fromStack); 

private:
	int m_maxSize;
	TYPE* m_elements;
	int m_topIndex;

};

#endif
