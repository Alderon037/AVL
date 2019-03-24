#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
class AVL;
class Node
{
	int val,h;
	Node *st,*dr;
	static unsigned nro;
public:
	Node(int x=0,Node*l=NULL,Node*r=NULL);
	Node(Node&);
	friend class AVL;
	friend void afisare(AVL);
};
#endif // NODE_H_INCLUDED
