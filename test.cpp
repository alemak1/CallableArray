
#include <iostream>
#include <cassert>

#include "LinkedNode.h"

using namespace std;

int main(){
	LinkedNode<int>* node1 = new LinkedNode<int>(20);
	LinkedNode<int>* node2 = new LinkedNode<int>(30);
	LinkedNode<int>* node3 = new LinkedNode<int>(40);

	BranchNode<int>* newBranchedNode = new BranchNode<int>(50);
	newBranchedNode->addNext(node1);
	newBranchedNode->addNext(node2);
	newBranchedNode->addNext(node3);

	cout << "The next node for this branch is: " << (newBranchedNode->getNext())->getItem() << endl;
	cout << "The branch setting for the first branch node is: " << BranchNode<int>::branchSettings[0] << endl;

	newBranchedNode->resetCurrentBranchNodeSetting(1);

	cout << "The next node for this branch is: " << (newBranchedNode->getNext())->getItem() << endl;
	cout << "The branch setting for the first branch node is: " << BranchNode<int>::branchSettings[0] << endl;

	newBranchedNode->resetCurrentBranchNodeSetting(2);

	cout << "The next node for this branch is: " << (newBranchedNode->getNext())->getItem() << endl;
	cout << "The branch setting for the first branch node is: " << BranchNode<int>::branchSettings[0] << endl;

	// cout << "The value of node1's previous node (i.e. newBranchNode) should be 50: " << (node1->getPrev())->getItem() << endl;
	// cout << "The value of node2's previous node (i.e. newBranchNode) should be 50: " << (node2->getPrev())->getItem() << endl;
	// cout << "The value of node3's previous node (i.e. newBranchNode) should be 50: " << (node3->getPrev())->getItem() << endl;


	// LinkedNode<int>* nodeA = new LinkedNode<int>();
	// nodeA->setItem(20);
	// assert(nodeA->getItem() == 20);

	// LinkedNode<int> nodeB(12);
	// assert(nodeB.getItem() == 12);

	// LinkedNode<int> nodeC;

	// try{
	// 	nodeC.getItem();
	// }catch(out_of_range oor){
	// 	cout << oor.what() << endl;
	// }

	// auto add3 = [](int& someInt){
	// 	someInt += 3;
	// };

	// auto multiplyBy10 = [](int& someInt){
	// 	someInt *= 10;
	// };

	// auto divideBy10 = [](int& someInt){
	// 	someInt /= 10;
	// };

	// auto subtract3 = [](int& someInt){
	// 	someInt -= 3;
	// };

	// (*nodeA)(add3);
	// assert(nodeA->getItem() == 23);

	// (*nodeA)(multiplyBy10);
	// assert(nodeA->getItem() == 230);

	// (*nodeA)(divideBy10);
	// assert(nodeA->getItem() == 23);

	// (*nodeA)(subtract3);
	// assert(nodeA->getItem() == 20);

	// cout << "After passing in the add lambda function into nodeA: " << nodeA->getItem() << endl;


	return 0;
}