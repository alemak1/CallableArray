

#ifndef LINKED_NODE_H
#define LINKED_NODE_H

template<class T>
class LinkedNode{
private:
	T dataItem;
protected:
	/**Consider using shared pointers 
	**/
	LinkedNode<T>* nextPtr;
	LinkedNode<T>* prevPtr;
public:
	LinkedNode(): nextPtr(nullptr),prevPtr(nullptr){};
	LinkedNode(const T& myDataItem): nextPtr(nullptr),prevPtr(nullptr),dataItem(myDataItem){};
	LinkedNode(const T& myDataItem, LinkedNode<T>* myNextPtr = nullptr, LinkedNode<T>* myPrevPtr = nullptr): nextPtr(nullptr),prevPtr(nullptr),dataItem(myDataItem){};
	
	T getItem() const{
		return dataItem;
	}

	void setItem(const T& myDataItem){
		dataItem = myDataItem;
	}

	virtual setPrev(LinkedNode<T>* myPrevPtr){
		prevPtr = myPrevPtr;
	}

	virtual setNext(LinkedNode<T>* myNextPtr){
		nextPtr = myNextPtr;
	}

	virtual LinkedNode<T>* getNext(){
		return nextPtr;
	}

	virtual LinkedNode<T>* getPrev(){
		return prevPtr;
	}

	/** The function call operator is overloaded so that a function can be passed as an argument, thereby allowing the user
	to transform the node's stored data; the function argument performs an operation on the stored data
	**/
	void operator()(void(*transform)(T&)){
		transform(dataItem);
	}

	LinkedNode<T>& operator=(const LinkedNode<T>& anotherLinkedNode);

	template<class P>
	LinkedNode operator+(const LinkedNode<P>& lhs, const LinkedNode<P>& rhs);

};


/** Eventually, the BranchedNode will become a nested class defined within the namespace of a container class;

**/

// template<class P>
// class BranchNode: public LinkedNode<P>{
// private:
// 	static int numberOfBranchNodes = 0;

// 	 The branch setting for each node allows user to change the direction of traversal; getNext() for BranchNodes is overriden 
// 	so that the next LinkedNodePtr returned by the function can be changed dynamically based on the branch node setting
	
// 	static int* branchSetting;
// 	LinkedNode<P>** nextBranchSet;
// public:
// 	BranchNode(): LinkedNode(){

// 	}

// }

#endif