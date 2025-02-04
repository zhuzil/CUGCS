#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;

struct Term {
	float coef;                               //系数
	int exp;                                  //指数
	Term *link;
	Term(float c, int e, Term *next = NULL)
	{
		coef = c; exp = e; link = next;
	}
	Term *InsertAfter(float c, int e);
	friend ostream& operator<<(ostream&, const Term&);
};

class Polynomial {
public:
	Polynomial() { first = new Term(0, -1); }     //建立空链表
	Polynomial(Polynomial&R);
	int maxOrder();
	Term *getHead() const { return first; }    //取得多项式单链表的表头指针
private:
	Term *first;
	friend ostream&operator<<(ostream&, const Polynomial&);
	friend istream&operator>>(istream&, Polynomial&);
	friend Polynomial operator+(Polynomial&, Polynomial&);
	friend Polynomial operator-(Polynomial&, Polynomial&);
};

Term*Term::InsertAfter(float c, int e) {        //在当前由this指针指示的项后面插入一个新项
	link = new Term(c, e, link);
	return link;
};

ostream&operator<<(ostream&out, const Term&x) {  //输出一个项x的内容到输出流out中
	if (x.coef == 0.0) return out;     //系数为0返回输出流
	if (x.coef != 1 && x.coef != -1) out << x.coef;     //系数不为1或-1，输出系数
	switch (x.exp) {
	case 0: {
		if (fabs(x.coef) == 1) out << x.coef;      //如果指数为0且系数为1或-1，直接输出系数
	} break;
	case 1: {
		if (x.coef == -1) out << "-x";    //指数为1的情况下，如果系数为-1则输出-x
		else out << "x";      //否则输出x
	}break;
	default: {
		if (x.coef == -1) out << "-x^" << x.exp; 
		else out << "x^" << x.exp;
	}break;
	}
	return out;
};

Polynomial::Polynomial(Polynomial&R) {         //用已有多项式对象R初始化当前多项式对象
	first = new Term(0, -1);
	Term *destptr = first, *srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
};

int Polynomial::maxOrder() {                  //计算最大阶数
	Term *current = first;
	while (current->link != NULL) current = current->link;
	return current->exp;
};

istream&operator>>(istream&in, Polynomial&x) {  //输入多项式
	Term *rear = x.getHead();
	float c;
	int e;
	while (1) {
		cout << "Input a term(coef,exp):" << endl;
		in >> c >> e;
		if (c == 0 && e == -1) break;                //系数为0，指数为1时输入结束
		rear = rear->InsertAfter(c, e);
	}
	return in;
};

ostream&operator<<(ostream&out, Polynomial&x) {  //输出得到的和/差多项式链表
	Term *current = x.getHead()->link;
	cout << "The polynomal is:" << endl;
	bool isEnd = true;
	while (current != NULL) {
		if (isEnd == false && current->coef > 0.0) out << "+";   //输入未结束则输出一个“+”
		isEnd = false;
		out << *current;      //输出当前项
		current = current->link;
	}
	out << endl;
	return out;
};

Polynomial operator + (Polynomial&A, Polynomial&B) {  //加法的重载
	Term*pa, *pb, *pc, *p;
	float temp;
	Polynomial C; pc = C.first;
	pa = A.getHead()->link; pb = B.getHead()->link;
	while (pa != NULL && pb != NULL) {
		if (pa->exp == pb->exp) {
			temp = pa->coef + pb->coef;
			if (fabs(temp) > 0.001)                    //系数相加不为0
				pc = pc->InsertAfter(temp, pa->exp);
			pa = pa->link; pb = pb->link;
		}
		else if (pa->exp < pb->exp) {
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;
		}
		else {
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;
		}
	}
	if (pa != NULL) p = pa;                             //处理链剩余部分
	else p = pb;
	while (p != NULL) {
		pc = pc->InsertAfter(p->coef, p->exp);
		p = p->link;
	}
	return C;
};

Polynomial operator - (Polynomial&A, Polynomial&B) {  //减法的重载
	Term*pa, *pb, *pd, *p;
	float temp;
	Polynomial D; pd = D.first;
	pa = A.getHead()->link; pb = B.getHead()->link;
	while (pa != NULL && pb != NULL) {
		if (pa->exp == pb->exp) {
			temp = pa->coef - pb->coef;
			if (fabs(temp) > 0.001)
				pd = pd->InsertAfter(temp, pa->exp);
			pa = pa->link; pb = pb->link;
		}
		else if (pa->exp < pb->exp) {
			pd = pd->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;
		}
		else {
			pd = pd->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;
		}
	}
	if (pa != NULL) p = pa;
	else p = pb;
	while (p != NULL) {
		pd = pd->InsertAfter(-(p->coef), p->exp);
		p = p->link;
	}
	return D;
};

int main() {
	int a;
	Polynomial A, B, C, D;
	cin >> A;
	cout << A;
	cin >> B;
	cout << B;
	cout << "选择进行的运算方式:" << endl;
	cout << '\t' << "1.加法" << endl;
	cout << '\t' << "2.减法" << endl;
	cout << "Input:";
	cin >> a;
	if (a == 1) {
		C = A + B;
		cout << C << endl;
	}
	else {
		D = A - B;
		cout << D << endl;
	}
	return 0;
}