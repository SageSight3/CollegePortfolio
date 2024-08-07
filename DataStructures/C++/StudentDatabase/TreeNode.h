#ifndef _TREENODE_
#define _TREENODE_

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
using namespace std;

class DRT;
class Tree;
class TreeNode {
private:
	string k; string d;
	TreeNode* left, * right, * parent;
	Tree* t;
	bool color; //true == black, false == red
public:
	TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T); //constructor
	~TreeNode(); //destructor
	DRT* add(string key, string data, string n, string p);
	//similar to search; keeps nsf and psf
	DRT* searchnode(string key, string n, string p);
	//utilizes keeping track of next-so-far and prev-so-far
	TreeNode* first(); //left all the down
	TreeNode* last(); //right all the way down
	string getk(); //get
	string getd(); //get
	TreeNode* getright(); //get
	TreeNode* getleft(); //get
	string next(); //right once, left all the way down (makes use of first ())
	string prev(); //left once, right all the way down (makes use of last ())
	DRT* remove(string key, string n, string p);
	//similar to search; keeps track of nsf and psf
	//just works its down to the tree to find the node to remove
	//then calls remove ()
	void remove(); //the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
	void setparent(TreeNode* p); //set
	void setleft(TreeNode* l); //set
	void setright(TreeNode* r); //set
	bool getColor(); //returns node color
	void flipColor();//changes color of a node
	TreeNode* getSibling(TreeNode* child, TreeNode* par); //returns node's sibling if they have one
	void rotate(); //roates a node up
	void addRebalance(TreeNode* addedNode); //rebalances tree after adding a node
	void delRebalance(TreeNode* child, TreeNode* par); //rebalances tree after deleting a node
	int ValidNode();
	TreeNode* getparent();
};

#endif