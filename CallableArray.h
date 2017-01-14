
#ifndef CALLABALE_ARRAY_H
#define CALLABALE_ARRAY_H

#include <stdexcept>
#include <string>
#include <cctype>
#include <iterator>
#include <initializer_list>

using namespace std;

template<class P>
class ArrayIterator;


template<class T>
class CallableArray{
private:
	const static int DEFAULT_CAPACITY = 20;
	int itemCount;
	int maxItems;
	T* items;

protected:
	virtual void printArray(ostream& os, char delimiter = ' '){
		for(unsigned i = 0; i < itemCount; i++){
			os << items[i] << delimiter;
		}
	};
public:
	CallableArray(){
		items = new T[DEFAULT_CAPACITY];
		itemCount = 0;
		maxItems = DEFAULT_CAPACITY;
	}

	CallableArray(size_t user_capacity){
		items = new T[user_capacity];
		itemCount = 0;
		maxItems = user_capacity;
	}

	CallableArray(initializer_list<T> il){
		items = new T[il.size()];
		maxItems = il.size();
		itemCount = 0;

		for(auto beg = il.begin(); beg != il.end(); beg++, itemCount++){
			items[itemCount] = *beg;
		}

	}

	bool isEmpty() const{
		return itemCount == 0;
	}

	int getNumberOfItems() const{
		return itemCount;
	}

	void addItem(const T& newItem){
		if(itemCount == maxItems){
			string error_message = "Operation addItem() failed: callable array has already reached capacity";
			throw out_of_range(error_message);
		}

		items[itemCount] = newItem;
		++itemCount;

	}

	void removeItem(){
		if(itemCount == 0){
			string error_message = "Operation removeItem() failed: callable array is alrady empty";
			throw out_of_range(error_message);
		}

		--itemCount;
	}

	void operator()(void fnc(T&)){
		for(unsigned i = 0; i < itemCount; i++){
			fnc(items[i]);
		}
	};


	const T& operator[](size_t index) const{
		if(index < 0 || index > itemCount){
			throw out_of_range("Subscript operation failed: the requested index value is out of range");
		}

		return items[index];
	}

	T& operator[](size_t index) {
		if(index < 0 || index > itemCount){
			throw out_of_range("Subscript operation failed: the requested index value is out of range");
		}

		return items[index];
	}

	CallableArray& operator=(const CallableArray& anotherArray){

		T* oldArray = items;
		delete [] oldArray;
		oldArray = nullptr;

		items = new T[anotherArray.maxItems];

		for(unsigned i = 0; i < anotherArray.itemCount; i++){
			addItem(anotherArray[i]);
		}

		return *this;
	}


	ArrayIterator<T> begin(){
		return ArrayIterator<T>(this, 0);
	}

	ArrayIterator<T> end(){
		return ArrayIterator<T>(this, itemCount);
	}

	template<class P>
	friend ostream& operator<<(ostream& os, const CallableArray<P>& anArray);

	template<class P>
	friend istream& operator>>(istream& is, CallableArray<P>& anArray);

	void print(){
		printArray(cout,' ');
	}



};

template<class P>
ostream& operator<<(ostream& os, CallableArray<P>& anArray){
	anArray.print();
	return os;
};

//Fix bug associated with overloaded input operator
template<class P>
istream& operator>>(istream& is, CallableArray<P>& anArray){
	P newItem;
	is >> newItem;
	anArray.addItem(newItem);
	return is;
};

template<class T>
class ArrayIterator: public iterator<input_iterator_tag, int>{
private:
	const CallableArray<T>* callableArrayPtr;
	int currentItemIndex;
public:
	ArrayIterator(const CallableArray<T>* someCallableArray, int itemIndex){
		callableArrayPtr = someCallableArray;
		currentItemIndex = itemIndex;
	}

	const T operator*(){
		CallableArray<T> callableArray = *callableArrayPtr;
		return callableArray[currentItemIndex];
	}

	ArrayIterator<T>& operator++(){
		currentItemIndex++;
		return *this;
	}

	ArrayIterator<T>& operator--(){
		currentItemIndex--;
		return *this;
	}

	bool operator==(const ArrayIterator<T>& rhs) const{
		return (callableArrayPtr == rhs.callableArrayPtr) && currentItemIndex == rhs.currentItemIndex;
	}
	bool operator!=(const ArrayIterator<T>& rhs) const{
		return (callableArrayPtr != rhs.callableArrayPtr) || currentItemIndex != rhs.currentItemIndex;
	}

};



#endif