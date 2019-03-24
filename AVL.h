#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "Node.h"
using namespace std;
class AVL
{
    Node*root;
	unsigned nr;
	unsigned nivel(Node*);
	int getDif(Node*);
	Node* rot_st(Node*);
    Node* rot_dr(Node*);
public:
	AVL();
	AVL(AVL&);
	~AVL();
	Node* insertieR(Node*,int);
	void insertie(int);
	unsigned getSize();
    int* inordine() const;
    int getVal(Node*);
    Node* getSt(Node*);
    Node* getDr(Node*);
    Node* getRoot(AVL);
	static int* preordine(AVL);
	static int* postordine(AVL);
	unsigned inaltime();
	static void print(AVL,int);
	bool cautare(int);
	void el(int);
	friend ostream& operator<<(ostream&, const AVL&);
	friend istream& operator<<(istream&, const AVL&);
	friend AVL operator+(AVL,AVL);
    bool operator<(const AVL&r)
    {
        Node*p1=root;
        Node*p2=r.root;
        while(p1->dr!=NULL)
            p1=p1->dr;
        while(p2->dr!=NULL)
            p2=p2->dr;
        if(p1->val<p2->val)
            return true;
        else
            return false;
    }
    bool operator>(const AVL&arb)
    {
        Node*p1=root;
        Node*p2=arb.root;
        while(p1->dr!=NULL)
            p1=p1->dr;
        while(p2->dr!=NULL)
            p2=p2->dr;
        if(p1->val>p2->val)
            return true;
        else
            return false;
    }
    int* operator-(const AVL&arb) //Metoda preia elementele arborilor si returneaza vectorul ce contine
    {                             //Elementele primului arbore ce nu sunt in al doilea
        int*v1=new int[nr];
        int*v2=new int[arb.nr];
        int*v=new int[nr];
        Node**s1=new Node*[nr];
        Node**s2=new Node*[arb.nr];
        int n=0,m=0,dim1=0,dim2=0;
        s1[dim1]=root;
        s2[dim2]=arb.root;
        dim1++;
        dim2++;
        while(dim1>0)
        {
            Node*p1=s1[dim1-1];
            dim1--;
            v1[n]=p1->val;
            n++;
            if(p1->dr!=NULL)
            {
                s1[dim1]=p1->dr;
                dim1++;
            }
            if(p1->st!=NULL)
            {
                s1[dim1]=p1->st;
                dim1++;
            }
        }
        delete[] s1;
        while(dim2>0)
        {
            Node*p2=s2[dim2-1];
            dim2--;
            v2[m]=p2->val;
            m++;
            if(p2->dr!=NULL)
            {
                s2[dim2]=p2->dr;
                dim2++;
            }
            if (p2->st!=NULL)
            {
                s2[dim2]=p2->st;
                dim2++;
            }
        }
        delete[] s2;
        dim1=0;
        bool ok=true;
        for(int i=0;i<n;i++)
            {for(int j=0;j<m;j++)
                if(v1[i]==v2[j])
                    ok=false;
            if(ok==true)
                {v[dim1]=v1[i];
                dim1++;}
            ok=true;
            }
        delete[] v1;
        delete[] v2;
        return v;
    }
    AVL operator=(AVL arb)
    {
        root=arb.root;
        nr=arb.nr;
        Node**s=new Node*[arb.nr];
        Node*p1=root;
        int dim=0;
        s[dim]=arb.root;
        dim++;
        while(dim>0)
        {
            Node*p=s[dim-1];
            dim--;
            p1->st=p->st;
            p1->dr=p->dr;
            if(p->dr!=NULL)
            {
                s[dim]=p->dr;
                dim++;
            }
            if(p->st!=NULL)
            {
                s[dim]=p->st;
                dim++;
            }
        }
        return *this;
    }
};
#endif // AVL_H_INCLUDED
