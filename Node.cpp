#include "Node.h"

Node::Node(int x,Node*l,Node*r):val(x),st(l),dr(r)
{
	nro++;
}

Node::Node(Node&n):val(n.val),st(n.st),dr(n.dr)
{
	nro++;
}
unsigned Node::nro=0;
