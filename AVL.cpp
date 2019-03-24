#include "AVL.h"
using namespace std;
AVL::AVL()
{
    root=NULL;
    nr=0;
}
AVL::AVL(AVL& arb)
{
	root=NULL;
	nr=0;
	Node**s=new Node*[arb.nr];
	unsigned dim=0;
	s[dim]=arb.root;
	dim++;
	while(dim>0)
    {
		Node*p=s[dim-1];
        dim--;
		insertie(p->val);
		if (p->dr!=NULL)
        {
			s[dim]=p->dr;
            dim++;
		}
		if (p->st!=NULL)
        {
			s[dim]=p->st;
            dim++;
		}
	}
	delete[] s;
	nr=arb.nr;
}
unsigned AVL::getSize()
{
	return nr;
}
int AVL::getVal(Node*p)
{
    return p->val;
}
Node* AVL::getSt(Node*p)
{
    return p->st;
}
Node* AVL::getDr(Node*p)
{
    return p->dr;
}
Node* AVL::getRoot(AVL arb)
{
    return arb.root;
}
unsigned AVL::nivel(Node*p)           //Functie pentru calcularea inaltimii unui nod
{
	if(p==NULL)
    {
		return 0;
	}
	unsigned r=nivel(p->dr);
	unsigned l=nivel(p->st);
	if(l>r)
    {
		return l+1;
	}
	return r+1;
}
unsigned AVL::inaltime()
{
	return nivel(root);
}
int AVL::getDif(Node*p)            //Functie pentru aflarea echilibrului unui nod
{
    if(p==NULL)
        return 0;
    return nivel(p->st)-nivel(p->dr);
}
Node* AVL::rot_st(Node*p)
{
    Node*t=p->dr;
    Node*t2=t->st;
    t->st=p;
    p->dr=t2;
    p->h=max(getDif(p->st),getDif(p->dr)) + 1;
    t->h=max(getDif(t->st),getDif(t->dr)) + 1;
    return t;
}
Node* AVL::rot_dr(Node*p)
{
    Node*t=p->st;
    Node*t2=t->dr;
    t->dr=p;
    p->st=t2;
    p->h=max(getDif(p->st),getDif(p->dr)) + 1;
    t->h=max(getDif(t->st),getDif(t->dr)) + 1;
    return t;
}
Node* AVL::insertieR(Node*p,int x)   //Functia insereaza si apoi verifica echilibrul fiecarui nivel
{                                    //La primul nod nebalansat se aplica rotatia in functie de caz
    if(p==NULL)
        {
            nr++;
            p=new Node(x);
            return p;
        }
	if(x<p->val)
        p->st=insertieR(p->st,x);
    else
        if(x>p->val)
            p->dr=insertieR(p->dr,x);
        else
            return p;
    p->h=1+max(nivel(p->st),nivel(p->dr));
    if(getDif(p)>1 && x<p->st->val)
        return rot_dr(p);
    if(getDif(p)>1 && x>p->st->val)
        {p->st=rot_st(p->st);
        return rot_dr(p);}
    if(getDif(p)<-1 && x>p->dr->val)
        return rot_st(p);
    if(getDif(p)<-1 && x<p->dr->val)
        {p->dr=rot_dr(p->dr);
        return rot_st(p);}
    return p;
}
void AVL::insertie(int x)
{
    root=insertieR(root,x);
}
int* AVL::inordine() const
{
	if (root==NULL)
    {
		return 0;
	}
	int*v=new int[nr];
	int n=0;
	Node** s=new Node*[nr];
	unsigned dim=0;
	Node* p=root;
	while (p!=NULL || dim>0)
    {
        if (p!=NULL)
        {
            s[dim]=p;
            dim++;
            p=p->st;
		}
		else
        {
			p=s[dim-1];
			v[n]=p->val;
            n++;
			dim--;
			p=p->dr;
		}
	}
	for(int i=0;i<n;i++)
        cout<<v[i]<<' ';
    delete[] s;
	return v;
}
int* AVL::preordine(AVL arb)
{
	if(arb.root==NULL)
    {
		return NULL;
	}
	Node**s=new Node*[arb.nr];
	int*v=new int[arb.nr];
	int n=0;
	unsigned dim=0;
	s[dim]=arb.root;
    dim++;
	while(dim>0)
    {
		Node*p=s[dim-1];
        dim--;
		v[n]=p->val;
		n++;
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
	delete[] s;
	return v;
}
int* AVL::postordine(AVL arb)
{
	if (arb.root==NULL)
    {
		return NULL;
	}
	Node**s=new Node*[arb.nr];
	int*v=new int[arb.nr];
	int n=0;
	unsigned dim=0;
	Node*p=arb.root;
	do
	{
		while(p!=NULL)
		{
			if(p->dr!=NULL)
			{
				s[dim]=p->dr;
                dim++;
			}
			s[dim]=p;
			dim++;
			p=p->st;
		}
		p=s[dim-1];
		dim--;
		if(p->dr!=NULL && s[dim-1]==p->dr)
        {
			s[dim-1]=p;
			p=p->dr;
		}
		else
		{
			v[n]=p->val;
            n++;
			p=NULL;
		}
	}
	while(dim>0);
	delete[] s;
	return v;
}
bool AVL::cautare(int x)    //Functia cauta elementul de valoare x in arbore si
{                           //Returneaza valoarea de adevar corespunzatoare
    Node*p=root;
    bool gasit=false;
    while(!gasit && p!=NULL)
        if(p->val==x)
            gasit=true;
        else
            if (x<p->val)
                p=p->st;
            else
                p=p->dr;
    if(gasit)
        return true;
    else
        return false;
}
void AVL::print(AVL arb,int x)
{
	int *v;
	if(x==0)
    {
		v=preordine(arb);
	}
	else
	{
		v=postordine(arb);
	}
	for(unsigned i=0;i<arb.getSize();i++)
	{
		cout<<v[i]<<' ';
	}
	delete[] v;
}
void AVL::el(int x) //Functia elimina elementul de valoare x din arbore
{
	Node*p=root;
	Node*t=root;
	bool gasit=false;
	while(!gasit && p!=NULL)
    {
		if(p->val==x)
        {
			gasit=true;
		}
		else
            if (x<p->val)
            {
                t=p;
                p=p->st;
            }
            else
            {
                t=p;
                p=p->dr;
            }
	}
	if(!gasit)
	{
		return;
	}
	if(p->dr==NULL && p->st==NULL)
	{
		if(t->dr==p)
		{
			t->dr=NULL;
		}
		else
		{
			t->st=NULL;
		}
		delete p;
	}
	else
        if (p->st!=NULL && p->dr==NULL)
        {
            if(t->dr==p)
            {
                t->dr=p->st;
            }
            else
            {
                t->st=p->st;
            }
            delete p;
        }
        else
            if(p->st==NULL && p->dr!=NULL)
            {
                if (t->dr==p)
                {
                    t->dr=p->dr;
                }
                else
                {
                    t->st=p->dr;
                }
                delete p;
            }
            else
            {
                Node*succesor=p->dr;
                t=p;
                while (succesor->st!=NULL)
                {
                    t=succesor;
                    succesor=succesor->st;
                }
                p->val=succesor->val;
                delete succesor;
                if (t==p)
                {
                    t->dr=NULL;
                }
                else
                {
                    t->st=NULL;
                }
            }
	nr--;
}
AVL::~AVL()
{
	Node**s=new Node*[nr];
	unsigned dim=0;
	s[dim]=root;
	dim++;
	while(dim>0)
    {
		Node*p=s[dim-1];
        dim--;
		if(p->st!=NULL)
        {
			s[dim]=p->st;
            dim++;
		}
		if(p->dr!=NULL)
        {
			s[dim]=p->dr;
            dim++;
		}
		delete p;
	}
	root=NULL;
	nr=0;
}
ostream& operator<<(ostream& out, const AVL&arb)
{
    arb.inordine();
    return out;
}
istream& operator>>(istream& in, AVL&arb)
{
    int x,n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        in>>x;
        arb.insertie(x);
    }
    return in;
}
AVL operator+(AVL arb1,AVL arb2)   //Metoda preia elementele a doi arbori si le reuneste
{
    int*v=new int[arb2.getSize()];
    Node**s=new Node*[arb2.getSize()];
    int n=0,dim=0,i;
    s[dim]=arb2.getRoot(arb2);
    dim++;
    while(dim>0)
    {
        Node*p=s[dim-1];
        dim--;
        v[n]=arb2.getVal(p);
        n++;
        if(arb2.getDr(p)!=NULL)
        {
            s[dim]=arb2.getDr(p);
            dim++;
        }
        if(arb2.getSt(p)!=NULL)
        {
            s[dim]=arb2.getSt(p);
            dim++;
        }
    }
    delete[] s;
    for(i=0;i<n;i++)
        arb1.insertie(v[i]);
    return arb1;
}
