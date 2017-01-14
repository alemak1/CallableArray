
#include <iostream>
#include <cassert>
#include <stdexcept>

#include "CallableArray.h"

using namespace std;

int main(){
	CallableArray<int> myArray;
	CallableArray<int> hisArray({12,15,18});
	CallableArray<int> herArray;

	herArray = hisArray;

	cout << "Number of values in herArray: ";
	cout << herArray.getNumberOfItems();

	cout << "After copying herArray into herArray, the result is: " << endl;
	cout << herArray << endl;

	cout << "Number of items in hisArray: ";
	cout << hisArray.getNumberOfItems();

	cout << "Now using the iterator defined for the CallableArray objec to iterate through all of its values: ";

	auto beg = hisArray.begin();

	while(beg != hisArray.end()){
		cout << *beg << " ";
		++beg;
	}

	cout << endl;

	cout << endl;

	cout << "Testing overloaded subscript operator: " << endl;

	cout << hisArray[0] << endl;
	cout << hisArray[1] << endl;
	cout << hisArray[2] << endl;


	cout << hisArray << endl;

	auto doubleItems = [](int& someInt){
		someInt *= 2;
	};

	/**Test the removeItem method for emptyArray situation
	try{
		myArray.removeItem();
	}catch(out_of_range e){
		cout << e.what() << endl;
	}
	**/

	myArray.addItem(10);
	myArray.addItem(20);
	myArray.addItem(30);

	cout << myArray << endl;
	cout << endl;

	myArray(doubleItems);
	hisArray(doubleItems);

	cout << myArray << endl;
	cout << endl;
	cout << hisArray << endl;

	return 0;
}