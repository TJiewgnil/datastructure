#include <iostream>
using namespace std;
#define OK 1
#define ERROR -1
#define operation_plus 0
#define operation_mul 1
#define operation_plus_mul 2

struct ElemType {
	int coe;
	int exp;
	struct ElemType* next;
};

int InputSize(int& size)
{
	cin >> size;
	if (!cin.fail())
		return OK;
	else
		return 0;
}

int CreateList(ElemType* Head, int size)
{
	int i;
	ElemType* ListNode = Head;
	for (i = 0; i < size; i++) {
		ElemType* NewNode = new(nothrow) ElemType;
		if (NewNode == 0)
			return ERROR;
		cin >> NewNode->coe >> NewNode->exp;
		ListNode->next = NewNode;
		ListNode = NewNode;
	}
	ListNode->next = NULL;
	return OK;
}

int NewElem(ElemType* Front)
{
	ElemType* NewNode = new(nothrow) ElemType;
	if (NewNode == 0)
		return ERROR;
	Front->next = NewNode;
	return OK;
}

int Plus(ElemType* Head1, ElemType* Head2, ElemType* HeadResult)
{
	ElemType* p1 = Head1->next, * p2 = Head2->next, * p3 = HeadResult;
	while (p1 != NULL&& p2 != NULL) {
		if ((p1->exp == p2->exp) && !(p1->coe + p2->coe)) {
			p1 = p1->next;
			p2 = p2->next;
		}
		else {
			if (NewElem(p3) == ERROR)
				return ERROR;
			p3 = p3->next;
			if (p1->exp < p2->exp) {
				p3->exp = p1->exp;
				p3->coe = p1->coe;
				p1 = p1->next;
			}
			else if (p1->exp == p2->exp) {
				p3->exp = p1->exp;
				p3->coe = p1->coe + p2->coe;
				p1 = p1->next;
				p2 = p2->next;
			}
			else if (p1->exp > p2->exp) {
				p3->exp = p2->exp;
				p3->coe = p2->coe;
				p2 = p2->next;
			}
		}
	}
	if (p1==NULL)
		while (p2 != NULL) {
			if (NewElem(p3) == ERROR)
				return ERROR;
			p3 = p3->next;
			p3->exp = p2->exp;
			p3->coe = p2->coe;
			p2 = p2->next;
		}
	else if (p2 == NULL)
		while (p1 != NULL) {
			if (NewElem(p3) == ERROR)
				return ERROR;
			p3 = p3->next;
			p3->exp = p1->exp;
			p3->coe = p1->coe;
			p1 = p1->next;
		}
	p3->next = NULL;
	return OK;
}

int Multiply(ElemType* Head1, ElemType* Head2, ElemType* HeadResult)
{
	int s1, s2, e1, e2, exp = 0;
	ElemType* p1 = Head1, * p2 = Head2, * p3 = HeadResult;

	s1 = p1->next->exp;//得到要构建的中间数组的大小
	s2 = p2->next->exp;
	while (p1->next != NULL)
		p1 = p1->next;
	e1 = p1->exp;
	while (p2->next != NULL)
		p2 = p2->next;
	e2 = p2->exp;

	int size = e1 + e2 - s1 - s2 + 1;//初始化数组
	int(*pm)[2] = new(nothrow)int[size][2];
	if (!pm)
		return ERROR;
	for (int i = 0; i < size; i++) {
		pm[i][0] = 0;//coe
		pm[i][1] = s1 + s2 + i;//exp
	}

	for (p1 = Head1->next; p1 != NULL; p1 = p1->next)//计算各项系数
		for (p2 = Head2->next; p2 != NULL; p2 = p2->next) 
			pm[p1->exp + p2->exp - s1 - s2][0] += p1->coe*p2->coe;

	for (int i = 0; i < size; i++) //将非零项的系数和指数存储到链表中
		if (pm[i][0]) {
			if (NewElem(p3) == ERROR)
				return ERROR;
			p3 = p3->next;
			p3->coe = +pm[i][0];
			p3->exp = pm[i][1];
		}
	p3->next = NULL;
	delete[]pm;
	return OK;
}

void PrintList(ElemType* Head)
{
	ElemType* p = Head;
	while (p->next != NULL) {
		p = p->next;
		cout << p->coe << " " << p->exp << " ";
	}
	cout << endl;
}

int main()
{
	ElemType Head1, Head2, HeadResult1, HeadResult2;
	int size;
	InputSize(size);
	CreateList(&Head1, size);
	InputSize(size);
	CreateList(&Head2, size);
	int order;
	cin >> order;
	if (order == operation_plus || order == operation_plus_mul)
		if (Plus(&Head1, &Head2, &HeadResult1))
			PrintList(&HeadResult1);
	if (order == operation_mul || order == operation_plus_mul)
		if (Multiply(&Head1, &Head2, &HeadResult2))
			PrintList(&HeadResult2);
	return 0;
}