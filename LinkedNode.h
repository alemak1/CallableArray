

#ifndef LINKED_NODE_H
#define LINKED_NODE_H

#include <stdexcept>

using namespace std;

template<class T>
class LinkedNode{
private:
	T* dataItem = nullptr;
protected:
	LinkedNode<T>* nextPtr = nullptr;
	LinkedNode<T>* prevPtr = nullptr;
public:
	LinkedNode(): nextPtr(nullptr),prevPtr(nullptr){};
	LinkedNode(const T& item){
		dataItem = new T(item);
	}
	
	T getItem() {
		T newItem;;

		if(dataItem != nullptr){
			newItem = *dataItem;
		}else{
			throw out_of_range("Error: getItem() request could not be completed because the current item has no associated data value");
		}

		return newItem;
	}

	void setItem(const T& myDataItem){
		T* oldDataItem = dataItem;
		dataItem = new T(myDataItem);

		delete oldDataItem;
		oldDataItem = nullptr;
	}

	virtual void setPrev(LinkedNode<T>* myPrevPtr){
		prevPtr = myPrevPtr;

		//FIX ERROR ASSOCIATED WITH THIS CODE
		myPrevPtr->setNext(this);
	}

	virtual void setNext(LinkedNode<T>* myNextPtr){
		nextPtr = myNextPtr;

		//FIX ERROR ASSOCIATED WITH THIS CODE
		myNextPtr->setPrev(this);
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
	void operator()(void transform(T&)){
		transform(*dataItem);
	}

	// LinkedNode<T> operator=(const LinkedNode<T>& anotherLinkedNode){
	// 	setItem(anotherLinkedNode.getItem());
	// 	return *this;
	// }

	// template<class P>
	// LinkedNode operator+(const LinkedNode<P>& lhs, const LinkedNode<P>& rhs);

};


/** Eventually, the BranchedNode will become a nested class defined within the namespace of a container class;

**/

template<class P>
class BranchNode: public LinkedNode<P>{
public:
	static int* branchSettings;
private:
	const static int MAX_NUMBER_OF_BRANCHES = 10;
	static int numberOfBranchNodes;

	LinkedNode<P>** nextBranchSet;
	int itemCount = 0;
	int branchNodeID;
public:
	BranchNode(): LinkedNode<P>(){
		nextBranchSet = new LinkedNode<P>*[MAX_NUMBER_OF_BRANCHES];

		branchNodeID = numberOfBranchNodes;
		branchSettings[branchNodeID] = 0;
		numberOfBranchNodes++;

	}

	BranchNode(const P& newItem): LinkedNode<P>(newItem){
		nextBranchSet = new LinkedNode<P>*[MAX_NUMBER_OF_BRANCHES];

		branchNodeID = numberOfBranchNodes;
		branchSettings[branchNodeID] = 0;
		numberOfBranchNodes++;

	}



	virtual LinkedNode<P>* getNext(){
		int currentBranchSetting = branchSettings[branchNodeID];
		return nextBranchSet[currentBranchSetting];
	}

	virtual void setNext(LinkedNode<P>* nextLinkedNodePtr){
		int currentBranchSetting = branchSettings[branchNodeID];
		nextBranchSet[currentBranchSetting] = nextLinkedNodePtr;

		//FIX ERROR ASSOCIATED WITH THIS CODE
		// nextLinkedNodePtr->setPrev(this);
		// this->nextPtr = nextLinkedNodePtr;
	}

	void addNext(LinkedNode<P>* anotherNode){
		if(itemCount == MAX_NUMBER_OF_BRANCHES){
			throw out_of_range("Operation failed: max number of branches for branch node has been exceeded");
		}
		nextBranchSet[itemCount] = anotherNode;
		++itemCount;

		//FIX ERROR ASSOCIATED WITH THIS CODE
		// anotherNode->setPrev(dynamic_cast<LinkedNode<P>*>(this));
	}

	void resetCurrentBranchNodeSetting(int updatedBranchSetting){
		if(updatedBranchSetting < 0 || updatedBranchSetting >= itemCount){
			throw out_of_range("Operation failed: a branch setting must correspond to a valid array-index for a branch in the current branch's branchset");
		}
		branchSettings[branchNodeID] = updatedBranchSetting;
	}

};

template<class P>
int BranchNode<P>::numberOfBranchNodes = 0;

template<class P>
int* BranchNode<P>::branchSettings = new int[BranchNode<P>::MAX_NUMBER_OF_BRANCHES];

#endif