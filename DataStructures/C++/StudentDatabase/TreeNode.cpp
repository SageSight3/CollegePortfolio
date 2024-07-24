#include <iostream>
#include <string>
#include <cstdlib>
#include "TreeNode.h"
#include <exception>
#include "DRT.h"
using namespace std;

TreeNode::TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T) {

	k = key; d = data; left = l; right = r; parent = p; t = T;
	color = true; //sets color to black
}

TreeNode::~TreeNode() { //destructor

	delete left;
	delete right;
}

DRT* TreeNode::add(string key, string data, string n, string p) {
	if (key == k) {
		d = data;
		//cout << "key == k case with key, " << key << ", added" << endl;
		return new DRT(data, n, p);
	}
	if (key < k) {
		if (left) { return left->add(key, data, n, p); }
		left = new TreeNode(key, data, nullptr, nullptr, this, t);
		TreeNode* rebalance = left;
		addRebalance(rebalance);
		//cout << key << " added left" << endl;
		//cout << "left case with key, " << key << ", added" << endl;
		return searchnode(key, n, p);
	}

	if (right) { return right->add(key, data, n, p); }
	right = new TreeNode(key, data, nullptr, nullptr, this, t);
	TreeNode* rebalance = right;
	addRebalance(rebalance);
	//cout << key << " added right" << endl;
	//cout << "right case with key, " << key << ", added" << endl;
	return searchnode(key, n, p);
	return new DRT("", "", "");
}

void TreeNode::addRebalance(TreeNode* addedNode) {
	addedNode->color = false;

	if (!addedNode->parent) {
		addedNode->color = true;
		return;
	}

	if (addedNode->parent->color) {
		return; 
	}

	if (getSibling(addedNode->parent, addedNode->parent->parent)) {
		if (!getSibling(addedNode->parent, addedNode->parent->parent)->color) {
			addedNode->parent->color = true;;
			getSibling(addedNode->parent, addedNode->parent->parent)->color = true;
			addedNode->parent->parent->color = false;
			TreeNode* newRebalance = addedNode->parent->parent;
			addRebalance(newRebalance);
			return;
		}
	}

	if((addedNode->parent->parent->left == addedNode->parent && addedNode->parent->left == addedNode) || (addedNode->parent->parent->right == addedNode->parent && addedNode->parent->right == addedNode)) {
		addedNode->parent->rotate();
		return;
	}
	//cout << "Rule 7" << endl;
	addedNode->rotate();
	addedNode->rotate();
}

DRT* TreeNode::searchnode(string key, string n, string p) {

	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev);
	}

	if (k < key) {
		if (right) return right->searchnode(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p);
	return new DRT("", k, p);

}

TreeNode* TreeNode::first() {//left all the down
	if (!left) {
		return this;
	}
	return left->first();
}

TreeNode* TreeNode::last() { //right all the way down
	if (!right) {
		return this;
	}
	return right->last();
}

string TreeNode::getk() { return k; }
string TreeNode::getd() { return d; }
TreeNode* TreeNode::getright() { return right; }
TreeNode* TreeNode::getleft() { return left; }

string TreeNode::next() {
if (right) { return right->first()->getk(); }
return "";
}

string TreeNode::prev() {
	if (left) { return left->last()->getk(); }
	return "";
}

DRT* TreeNode::remove(string key, string n, string p) {
	//cout << this << " Key: " << k << endl;
	if (k == key) {
		this->remove();
		return new DRT("", n, p);
	}

	if (k < key) {
		if (right) return right->remove(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->remove(key, k, p);
	return new DRT("", k, p);

}

void TreeNode::delRebalance(TreeNode* child, TreeNode* par) {

	if (child) {
		if (!child->color) {
			child->flipColor();
			//cout << "rule 4" << endl;
			return;
		}
	}

	if (!par) {
		//cout << "rule 5" << endl;
		return;
	}

	TreeNode* sibling = getSibling(child, par);

	if (sibling) {
		if (!sibling->color) {
			sibling->rotate();
			delRebalance(child, par);
			//cout << "rule 6" << endl;
			return;
		}
	}

	//gets if both of sibling's children are black
	bool bothBlack = true;
	if (sibling) {
		if (sibling->left) {
			if (!sibling->left->color) {
				bothBlack = false;
			}
		}

		if (sibling->right) {
			if (!sibling->right->color) {
				bothBlack = false;
			}
		}
	}

	if (bothBlack) {
		sibling->color = false;
		child = par;
		par = par->parent;
		delRebalance(child, par);
		//cout << "rule 7" << endl;
		return;
	}

	if (sibling->parent->left == sibling) {
		if (sibling->left) {
			if (!sibling->left->color) {
				sibling->left->flipColor();
				sibling->rotate();
				//cout << "rule 8" << endl;
				return;
			}
		}
	}
	else {
		if (sibling->right) {
			if (!sibling->right->color) {
				sibling->right->flipColor();
				//cout << "rule 9" << endl;
				sibling->rotate();
				//cout << "rule 9 rotated" << endl;
				return;
			}
		}
	}

	//cout << "rule 10" << endl;
	TreeNode* indirectChild;
	if (sibling->parent->left == sibling) {
		indirectChild = sibling->right;
		indirectChild->rotate();
		//cout << "rule 10 rotated once" << endl;
		indirectChild->rotate();
	}
	else {
		indirectChild = sibling->left;
		indirectChild->rotate();
		//cout << "rule 10 rotated once" << endl;
		indirectChild->rotate();
	}

	sibling->color = true;
	//cout << "rule 10 rotated twice" << endl;
}

void TreeNode::remove() {
	//the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
	//TreeNode* temp = nullptr;
	if (left && right) { //two child case
		d = right->first()->getd();
		k = right->first()->getk();
		right->first()->remove();
		return;
	}
	TreeNode* actualDelPar = this->parent;
	TreeNode* child;
	if (left) {
		child = left;
	}
	else if (right) {
		child = right;
	}
	else {
		child = nullptr;
	}

	if (left || right) { //one child case
		if (parent == nullptr) { //node is root
			if (left) {
				t->setroot(left);
				left->parent = nullptr;
				this->left = nullptr;
				if (color) {
					delRebalance(child, actualDelPar);
				}
				return;
			}
			else {
				t->setroot(right);
				right->parent = nullptr;
				this->right = nullptr;
				if (color) {
					delRebalance(child, actualDelPar);
				}
				return;
			}
		}
		else if (parent->left == this) { //node is parent's left child
			if (left) { //if node's child is left
				left->parent = parent;
				parent->left = left;
				left = nullptr;
			}
			else { //if node's child is right
				right->parent = parent;
				parent->left = right;
				right = nullptr;
			}
		}
		else { //node is parent's right child
			if (left) { //if node's child is left
				left->parent = parent;
				parent->right = left;
				left = nullptr;
			}
			else { //if node's child is right
				right->parent = parent;
				parent->right = right;
				right = nullptr;
			}
		}
		parent = nullptr;
	}
	else {
		if (parent == nullptr) {
			t->setroot(nullptr);
		}
		else if (parent->left == this) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
		parent = nullptr;
	}
	if (color) {
		delRebalance(child, actualDelPar);
	}
	//cout << "color is " << color << endl;
	//cout << "rule 2" << endl;
	delete this;
}

void TreeNode::setparent(TreeNode* p) { parent = p; }
void TreeNode::setleft(TreeNode* l) { left = l; }
void TreeNode::setright(TreeNode* r) { right = r; }

bool TreeNode::getColor() {
	return color;
}

void TreeNode::flipColor() {
	color = !color; //sets color to it's opposite, black to red, red to black
}

TreeNode* TreeNode::getSibling(TreeNode* child, TreeNode* par) {
	if (par->left == child) {
		return par->right;
	}
	return par->left;
}

void TreeNode::rotate() {
	bool tempColor = parent->color;
	parent->color = color;
	color = tempColor;

	if (!parent) {
		cout << "error, trying to rotate root" << endl;
		return;
	}

	TreeNode* temp;
	TreeNode* oldGrandparent = parent->parent;

	//updating old grandparent's changing child
	if (oldGrandparent) {
		if (oldGrandparent->left == parent) {
			oldGrandparent->left = this;
		}
		else {
			oldGrandparent->right = this;
		}
	}

	//get what child node is of parent
	if (parent->left == this) {
		temp = right;
		//move parent down
		right = parent;
		//moving zizgag: node old right becomes old parent left
		right->left = temp;
		//moving zigzag: node old right parent becomes old parent
		if (right->left) {
			right->left->parent = right;
		}
		//old parent's parent becomes node
		right->parent = this;
	}
	else {
		temp = left;
		//move parent down
		left = parent;
		//moving zizgag: node old left becomes old parent right
		left->right = temp;
		//moving zigzag: node old left parent becomes old parent
		if (left->right) {
			left->right->parent = left;
		}
		//old parent's parent becomes node
		left->parent = this;
	}

	//update parent to oldGrandparent
	parent = oldGrandparent;
	if (!oldGrandparent) { //updates root if needed
		t->setroot(this);
	}
}

TreeNode* TreeNode::getparent() {
	return parent;
}