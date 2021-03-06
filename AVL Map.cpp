#include "stdafx.h"
# include <iostream>
#include <fstream>
#include <string> 
#include <iomanip> 
#include<algorithm> 
#include<windows.h>
#include <stdio.h> 
using namespace std;
class Product;
template<class K, class T>
class AVLNode {
public:
	K key;
	T *data;
	int height;
	AVLNode<K, T> *left, *right;

	AVLNode(const K& k = NULL, T *D = NULL, const int& h = 0, AVLNode< K, T >* P = nullptr, AVLNode< K, T >* N = nullptr)
	{
		key = k;
		data = D;
		height = h;
		left = P;
		right = N;
	}

	~AVLNode()
	{
	}

};
template<class K, class T>
class AVLMap {
private:
	AVLNode< K, T >* root;
	int ALLOWED_IMBALANCE = 1;
public:
	AVLMap()
	{
		root = NULL;
	}
	~AVLMap()
	{
		destroy(root);
	}
	void Insert(K val, T *data = nullptr)
	{
		insert(root, val, data);
	}
	int height(AVLNode< K, T > *N)
	{
		if (N == NULL)
			return -1;
		else
			return max(height(N->left), height(N->right)) + 1;
	}
	void search(AVLMap<K, T> &a, const K& val)
	{
		if (search_recursively(root, val) == true)
			cout << "Yes, this item is present!" << endl;
		else
			cout << "Sorry! Item not found." << endl;
	}
	bool search_recursively(AVLNode< K, T >* & tree, const K& val)
	{
		if (tree == NULL)
			return false;
		else if (tree->key == val)
			return tree;
		else if (tree->key < val)
			return search_recursively(tree->right, val);
		else if (tree->key > val)
			return search_recursively(tree->left, val);
	}
	void inorder_recursively(AVLNode< K, T >*tree)
	{
		if (tree)
		{
			inorder_recursively(tree->left);
			cout << tree->key << " ";
			inorder_recursively(tree->right);
		}
	}
	void balance(AVLNode< K, T >* & t)
	{
		if (t == nullptr)
			return;
		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				return rightRotate(t);
			else
				return doubleLeftRightRotation(t);
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
			if (height(t->right->right) >= height(t->right->left))
				return leftRotate(t);
			else
				return doubleRightLeftRotation(t);
		t->height = max(height(t->left), height(t->right)) + 1;
	}
	void insert(AVLNode< K, T > *& tree, K val, T *data) {
		if (tree == nullptr)
			tree = new AVLNode< K, T >(val, data);
		else if (val < tree->key)
			insert(tree->left, val, data);
		else if (val > tree->key)
			insert(tree->right, val, data);
		balance(tree);
	}
	void doubleLeftRightRotation(AVLNode< K, T >*&X)
	{
		leftRotate(X->left);
		rightRotate(X);
	}
	void doubleRightLeftRotation(AVLNode< K, T >*&X)
	{
		rightRotate(X->right);
		leftRotate(X);
	}
	void rightRotate(AVLNode< K, T > *& x)
	{
		AVLNode< K, T > * orphan = x->left->right;
		AVLNode< K, T > * y = x->left;
		y->right = x;
		x->left = orphan;
		x->height = height(x);
		y->height = height(y);
		x = y;
	}
	void leftRotate(AVLNode< K, T > *& x)
	{
		AVLNode< K, T > * orphan = x->right->left;
		AVLNode< K, T > * y = x->right;
		y->left = x;
		x->right = orphan;
		x->height = height(x);
		y->height = height(y);
		x = y;
	}
	void destroy(AVLNode< K, T >*&tree)
	{
		if (tree)
		{
			destroy(tree->left);
			destroy(tree->right);
			delete tree;
			tree = NULL;
		}
	}
	void delete_BNode(AVLNode< K, T >* & tree, const K& D)
	{
		AVLNode< K, T >*temp = tree;
		if (tree->left == NULL)
		{
			tree = tree->right;
			delete temp;
		}
		else if (tree->right == NULL)
		{
			tree = tree->left;
			delete temp;
		}
		else
		{
			K val = Find_Max(tree->left);
			tree->key = val;
			delete_recursively(tree->left, D);
		}
	}
	K Find_Max(AVLNode< K, T >* & tree)
	{
		while (tree->right != NULL)
			tree = tree->right;
		return tree->key;
	}
	void delete_recursively(AVLNode< K, T >* & tree, const K& k)
	{
		if (tree)
		{
			if (tree->key > k)
				delete_recursively(tree->left, k);
			else if (tree->key < k)
				delete_recursively(tree->right, k);
			if (tree->key == k)
				delete_BNode(tree, k);
		}
	}
	void Delete(AVLMap<K, T> &a, const K& val)
	{
		delete_recursively(root, val);
		root->height = max(height(root->left), height(root->right)) + 1;
		cout << endl << endl;
		rebalance(root);
	}
	void rebalance(AVLNode< K, T >* & tree)
	{
		if (tree)
		{
			balance(tree);
			rebalance(tree->left);
			rebalance(tree->right);
		}
	}
	void PrintData(AVLNode< K, T >*tree)
	{
		if (tree)
		{
			PrintData(tree->left);
			cout << tree->key << "\t" << setw(20) << left << *tree->data;;
			PrintData(tree->right);
		}
	}
	int LeafCount(AVLNode< K, T >* & tree)
	{
		if (tree == NULL)
			return 0;
		if (tree->left == NULL && tree->right == NULL)
			return 1;
		else
			return LeafCount(tree->left) + LeafCount(tree->right);
	}
	void Print(AVLMap<K, T> &a)
	{
		int choice;
		cout << "To Print Inorder press 0 " << endl;
		cout << "To Print Tree Keys press 1" << endl;
		cout << "To Print Tree Data press 2" << endl;
		cout << "enter choice :\t";
		cin >> choice;
		cout << endl;
		if (choice == 0)
			inorder_recursively(root);
		if (choice == 1)
			printTree(root, 0, 15);
		if (choice == 2)
			PrintData(root);
		cout << endl;
	}
	void printTree(AVLNode< K, T >* & root, int space, int distance)
	{
		if (root == NULL)
			return;
		space += distance;
		printTree(root->right, space, distance);
		cout << endl;
		for (int i = distance; i < space; i++)
			cout << " ";
		cout << root->key;
		printTree(root->left, space, distance);
	}
};
class Product
{
	friend ostream& operator<<(ostream& out, const Product &);
private:
	int ProductID;
	string name;
	int quantity;
public:
	Product(string n = " ", int q = 0)
	{
		name = n;
		quantity = q;
	}
	ostream& operator *(ostream& out)
	{
		out << name << "\t" << setw(30) << left << quantity << endl;
		return out;
	}
};
void LoadAVL(ifstream &fin, AVLMap<int, Product> &ProductMap)
{
	char buffer[200];
	for (int i = 0; i < 3; i++)
		fin >> buffer;
	fin.getline(buffer, 200);

	char i[180];
	char n[180];
	char q[180];
	int len = 0;
	char*Name = nullptr;
	int id;
	int quant;

	while (!fin.eof())
	{
		fin.getline(buffer, 180);				//inputs a whole line
		strcpy(i, strtok(buffer, "\t"));		//tokenizes the line
		strcpy(n, strtok(NULL, "\t"));			//stores tokens in different variable
		strcpy(q, strtok(NULL, "\n"));

		id = atoi(i);
		quant = atoi(q);

		len = strlen(n);						//allocation and copy to char*
		Name = new char[len + 1];
		strcpy(Name, n);
		Name[len + 1] = '\0';

		Product *obj = new Product(Name, quant);
		ProductMap.Insert(id, obj);
	}
}
ostream& operator <<(ostream& out, const Product &obj)
{
	out << obj.name << "\t" << setw(20) << left << obj.quantity << endl;
	return out;
}
int  menu()
{
	int i = 1;
	int choice;
	cout << endl;
	cout << "--------------------------MENU--------------------------" << endl;
	cout << i++ << ". Insert" << endl;
	cout << i++ << ". Delete" << endl;
	cout << i++ << ". Search" << endl;
	cout << i++ << ". Print" << endl;
	cout << i++ << ". Exit" << endl;

	cout << "enter choice :\t";
	cin >> choice;
	cout << endl;
	return choice;
}
int main() {

	AVLMap<int, Product> ProductMap;

	string filename;
	cout << "enter the name of the data file: ";
	cin >> filename;
	ifstream fin(filename.c_str());
	if (fin)
	{
		LoadAVL(fin, ProductMap);
		fin.close();
	}

	int choice;
	choice = menu();

	while (choice < 6)
	{
		if (choice == 1)
		{
			string name;
			int id;
			int quantity;
			cout << "Name :\t";
			cin >> name;

			cout << "Product ID:\t";
			cin >> id;
			cout << "Quantity:\t";
			cin >> quantity;
			Product *obj = new Product(name, quantity);
			ProductMap.Insert(id, obj);
		}
		if (choice == 2)
		{
			string name;
			int id;
			cout << "Product ID:\t";
			cin >> id;
			ProductMap.Delete(ProductMap, id);
		}
		if (choice == 3)
		{
			string name = " ";
			int id = 0;
			int quantity = 0;
			cout << "Product ID:\t";
			cin >> id;
			ProductMap.search(ProductMap, id);
		}
		if (choice == 4)
		{
			ProductMap.Print(ProductMap);
		}
		if (choice == 5)
		{
			cout << "--------------------------Exiting----------------------";
			return 0;
		}
		choice = menu();
	}

	if (choice >= 7)
	{
		cout << "invalid choice" << endl;
		choice = menu();
	}
}