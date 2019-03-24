#include <iostream>
#include "Node.h"
#include "AVL.h"
using namespace std;
int main()
{
    int *v;
    unsigned i;
    AVL a,b,c;
    a.insertie(10);
	a.insertie(8);
	a.insertie(4);
	a.insertie(16);
	a.insertie(13);
	a.insertie(11);
	a.insertie(20);
	a.insertie(22);
	a.insertie(26);
	a.insertie(23);
	b.insertie(11);
	b.insertie(9);
	b.insertie(5);
	b.insertie(17);
	b.insertie(14);
	b.insertie(12);
	b.insertie(21);
	b.insertie(23);
	if(a>b)
        cout<<"Yep"<<endl;
	unsigned n=a.getSize();
	cout<<a;
    cout<<endl;
    v=a-b;
    for(i=0;i<8;i++)
        cout<<v[i]<<' ';
    cout<<endl;
    c=a+b;
    cout<<c;
    cout<<endl;
    cout<<a.inaltime();
    return 0;
}
