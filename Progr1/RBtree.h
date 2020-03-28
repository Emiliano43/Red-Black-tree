#pragma once
#include "Node.h"
#include <iostream>
#include "List.h"
#include <windows.h>
using namespace std;
template <typename Key, typename Value>
class RBtree
{
private:
	Node<Key, Value>* root;
	
	void SetColor(int text, int background)				//sets color of text
	{
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
	}
	
	void fixInsertion(Node<Key, Value>*& node) {					//balances tree after insertation
		if (root == node) {				//color the root
			node->setColor(black);
			return;
		}
		Color c;
		Node<Key, Value>* parent = nullptr, *grandparent = nullptr, *uncle = nullptr;
		while (node != root && node->getColor() == red && node->getParent()->getColor() == red) {
			parent = node->getParent();
			grandparent = parent->getParent();
			if (parent == grandparent->getLeft()) {			//if dad is left child of grandfather
				uncle = grandparent->getRight();
				if (uncle->getColor() == red) {						//case 1: uncle is red
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else {
					if (node == parent->getRight()) {				//case 2: dad and grandfather in different directions
						leftRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					rightRotate(grandparent);						//case 3: dad and grandfather in same directions
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
					node = parent;
				}
			}
			else {													//if dad is right child of grandfather
				uncle = grandparent->getLeft();
				if (uncle->getColor() == red) {
					parent->setColor(black);
					grandparent->setColor(red);
					uncle->setColor(black);
					node = grandparent;
				}
				else {
					if (node == parent->getLeft()) {		//case 2
						rightRotate(parent);
						node = parent;
						parent = node->getParent();
					}
					leftRotate(grandparent);				//case 3
					c = parent->getColor();
					parent->setColor(grandparent->getColor());
					grandparent->setColor(c);
					node = parent;
				}
			}
		}
		root->setColor(black);							//color the root
	}
	
	Node<Key, Value>* minValueNode(Node<Key, Value>* node) {			//returns minimal left element

		Node<Key, Value>* ptr = node;

		while (ptr->getLeft() != nullptr)
			ptr = ptr->getLeft();

		return ptr;
	}

	void leftRotate(Node<Key, Value>* node) {
		Node<Key, Value>* right_child = node->getRight();
		node->setRight(right_child->getLeft());

		if (node->getRight() != nullptr)
			node->getRight()->setParent(node);

		right_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = right_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(right_child);
		else
			node->getParent()->setRight(right_child);

		right_child->setLeft(node);
		node->setParent(right_child);
	}
	void rightRotate(Node<Key, Value>* node) {
		Node<Key, Value>* left_child = node->getLeft();
		node->setLeft(left_child->getRight());

		if (node->getLeft() != nullptr)
			node->getLeft()->setParent(node);

		left_child->setParent(node->getParent());

		if (node->getParent() == nullptr)
			root = left_child;
		else if (node == node->getParent()->getLeft())
			node->getParent()->setLeft(left_child);
		else
			node->getParent()->setRight(left_child);

		left_child->setRight(node);
		node->setParent(left_child);
	}
	
	void delAllTree(Node<Key, Value>* node) {				//auxiliary function for deleting map
		while (node != nullptr) {
			delAllTree(node->getLeft());
			delAllTree(node->getRight());
			delete node;
			node = nullptr;
		}
		root = nullptr;
	}
	
	void print_levels(Node<Key, Value>* node, int level, bool side)			//auxiliary function for output
	{
		for (int i = 0; i < level; i++)
			cout << ' ';
		if (level != 0)
		{
			cout << '|';
			cout << "->";
			if (side == false)
				cout << "L: ";
			else
				cout << "R: ";
		}
		else
			cout << ' ';
		if (node) {
			if (node->getColor() == black)
				SetColor(9, 0);
			else
				SetColor(12, 0);
			cout << node->getKey() << '(' << node->getValue() << ')' << endl;
			SetColor(7, 0);
		}
		else {
			SetColor(9, 0);
			cout << "nil" << endl;
			SetColor(7, 0);
		}
		if (node)
		{
			if (level > 0)
			{
				if (node->getLeft() || node->getRight())
				{
					print_levels(node->getLeft(), level + 3, false);
					print_levels(node->getRight(), level + 3, true);
				}
			}
			else
			{
				if (node->getLeft() || node->getRight())
				{
					print_levels(node->getLeft(), level + 1, false);
					print_levels(node->getRight(), level + 1, true);
				}
			}
		}
	}

	void setKeys(List<Key> &ls, Node<Key, Value>* node) {
		while (node) {
			setKeys(ls, node->getLeft());
			ls.push_back(node->getKey());
			setKeys(ls, node->getRight());
			return;
		}
	}
	void setValues(List<Value> &ls, Node<Key, Value>* node) {
		while (node) {
			setValues(ls, node->getLeft());
			ls.push_back(node->getValue());
			setValues(ls, node->getRight());
			return;
		}
	}
	 
	Node<Key, Value>* replace(Node<Key, Value>* x) {					//finds node that replaces a deleted node in BST

		if (x->getLeft() != nullptr && x->getRight() != nullptr)		//when node have 2 children 
			return minValueNode(x->getRight());

		if (x->getLeft() == nullptr && x->getRight() == nullptr)		//when leaf
			return nullptr;

		if (x->getLeft() != nullptr)									//when single child
			return x->getLeft();
		else
			return x->getRight();
	}
	 
	Node<Key, Value>* search(Key key) {								//returns pointer to element with required key
		Node<Key, Value>* temp = root;
		while (temp != NULL && key != temp->getKey()) {
			if (key < temp->getKey()) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}
		return temp;
	}

	void swapValues(Node<Key, Value>* u, Node<Key, Value>* v) {
		Key key = u->getKey();
		u->setKey(v->getKey());
		v->setKey(key);
		Value value = u->getValue();
		u->setValue(v->getValue());
		v->setValue(value);
	}
	 
	void deleteNode(Node<Key, Value>* cur) {				// deletes the given node - cur
		Node<Key, Value>* aux = replace(cur);

		bool uvBlack = ((aux == nullptr || aux->getColor() == black) && (cur->getColor() == black));				// True when cur and aux are both black
		Node<Key, Value>* parent = cur->getParent();

		if (aux == nullptr) {					//aux is nullptr therefore cur is leaf
			 
			if (cur == root) {						//cur is root, making root nullptr
				root = nullptr;
			}
			else {
				if (uvBlack) {
					//aux and cur both black 
					fixDoubleBlack(cur);				// cur is leaf, fix double black at cur
				}
				else {
					//aux or cur is red 
					if (cur->brother() != nullptr)					//brother is not nullptr, make it red
						cur->brother()->setColor(red);
				}

				if (cur->isOnLeft()) {					// delete cur from the tree
					parent->setLeft(nullptr);
				}
				else {
					parent->setRight(nullptr);
				}
			}
			delete cur;
			return;
		}
		if (cur->getLeft() == nullptr || cur->getRight() == nullptr) {
			// cur has 1 child 
			if (cur == root) {						//cur is root, assign the value of aux to cur, and delete aux
				cur->setKey(aux->getKey());
				cur->setLeft(nullptr);
				cur->setRight(nullptr);
				delete aux;
			}
			else {								//detach cur from tree and move aux up
				if (cur->isOnLeft()) {
					parent->setLeft(aux);
				}
				else {
					parent->setRight(aux);
				}
				delete cur;
				aux->setParent(parent);
				if (uvBlack) {
					//aux and cur both black, fix double black at aux 
					fixDoubleBlack(aux);
				}
				else {
					//aux or cur red, color aux black 
					aux->setColor(black);
				}
			}
			return;
		}
		swapValues(aux, cur);						//cur has 2 children, swap values
		deleteNode(aux);
	}
	
	void fixDoubleBlack(Node<Key, Value>* x) {					//fixes tree after deletion
		if (x == root)					//reached root
			return;

		Node<Key, Value>* brother = x->brother(), *parent = x->getParent();
		if (brother == nullptr) {								//no brother, double black pushed up
			fixDoubleBlack(parent);
		}
		else {
			if (brother->getColor() == red) {					//case 1: brother red
				parent->setColor(red);
				brother->setColor(black);
				if (brother->isOnLeft()) {					//if brother left
					rightRotate(parent);
				}
				else {
					leftRotate(parent);						//if brother right
				}
				fixDoubleBlack(x);
			}
			else {
				if (brother->hasRedChild()) {				//case 2: brother black
					 
					if (brother->getLeft() != nullptr && brother->getLeft()->getColor() == red) {				//case 2.1: at least 1 red children
						if (brother->isOnLeft()) {															//if brother left and his red child left
							brother->getLeft()->setColor(brother->getColor());
							brother->setColor(parent->getColor());
							rightRotate(parent);
						}
						else {
							brother->getLeft()->setColor(parent->getColor());								//if brother right and his red child left
							rightRotate(brother);
							leftRotate(parent);
						}
					}
					else {
						if (brother->isOnLeft()) {
							brother->getRight()->setColor(parent->getColor());								//if brother left and his red child right
							leftRotate(brother);
							rightRotate(parent);
						}
						else {
							brother->getRight()->setColor(brother->getColor());								//if brother right and his red child right
							brother->setColor(parent->getColor());
							leftRotate(parent);
						}
					}
					parent->setColor(black);
				}
				else {
																		//2 black children
					brother->setColor(red);
					if (parent->getColor() == black)
						fixDoubleBlack(parent);
					else
						parent->setColor(black);
				}
			}
		}
	}
public:
	RBtree() : root(nullptr) {}
	~RBtree() {
		delAllTree(root);
	}

	void insert(Key key, Value value) {										//inserts node using key with value
		Node<Key, Value>* temp = new Node<Key, Value>(key, value);
		if (!root) {
			root = temp;
		}
		else {
			Node<Key, Value>* p = root;
			Node<Key, Value>* q = nullptr;
			while (p != nullptr) {
				q = p;
				if (p->getKey() < temp->getKey()) {
					p = p->getRight();
				}
				else if (p->getKey() == temp->getKey())
				{
					throw invalid_argument("This element is already in the map");
				}
				else {
					p = p->getLeft();
				}
			}
			temp->setParent(q);
			if (q->getKey() <= temp->getKey()) {
				q->setRight(temp);
			}
			else {
				q->setLeft(temp);
			}
		}
		fixInsertion(temp);
	}

	void remove(Key key) {								//removes an element
		if (root == nullptr)
			throw invalid_argument("Map is empty");

		Node<Key, Value>* node = search(key);

		if (node->getKey() != key) {
			throw invalid_argument("This element isn't in the map");
		}
		deleteNode(node);
	}

	Value find(Key key) {									//returns the value using key
		if (!root)
			throw invalid_argument("Map is empty");
		Node<Key, Value>* temp = root;
		while (temp && temp->getKey() != key) {
			if (temp->getKey() < key)
				temp = temp->getRight();
			else
				temp = temp->getLeft();
		}
		if (!temp)
			throw invalid_argument("This element isn't in the map");
		return temp->getValue();
	}

	void clear() {											//cleans the map
		if (root == nullptr)
			throw out_of_range("The map is empty");
		delAllTree(root);
	}

	List<Key> get_keys() {						//returns a copy of list that contains keys of map
		List<Key> ls;
		setKeys(ls, root);
		return ls;
	}

	List<Value> get_values() {					//returns a copy of list that contains values of map
		List<Value> ls;
		setValues(ls, root);
		return ls;
	}

	void print()								//prints red-black map
	{
		if (root == nullptr)
			throw runtime_error("Map is empty");
		int level = 0;
		print_levels(root, level, false);
		cout << endl;
	}
};