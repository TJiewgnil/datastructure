#include <iostream>
using namespace std;

#define MAXSIZE 10000
#define OK 0
#define ERROR -1

typedef struct student {
	string no;
	string name;
}stu;

typedef struct seqlist {
	stu elem[MAXSIZE];
	int length;
}List;

List L;

int InputSize(int& size)
{
	cin >> size;
	if (!cin.fail())
		return OK;
	else
		return ERROR;
}

int InitList(List* L)//初始化
{
	L->length = 0;
	return OK;
}

int CreateList(List* L, int size)
{
	int i;
	for (i = 0; i < size; i++) 
		cin >> L->elem[i].no >> L->elem[i].name;
	L->length = size;
	return OK;
}

int InsertElem(List* L, int location)
{
	int i;
	if (location <= 0 || location > L->length + 1)//合法：1--length+1  对应数组中0--length
		return ERROR;
	location--;
	if (location + 1 < L->length + 1)
		for (i = L->length; i > location; i--) {
			L->elem[i].no = L->elem[i - 1].no;
			L->elem[i].name = L->elem[i - 1].name;
		}
	cin >> L->elem[location].no >> L->elem[location].name;
	L->length++;
	return OK;
}

int RemoveElem(List* L, int location)
{
	if (location <= 0 || location > L->length)//合法：1--length
		return ERROR;
	if (location != L->length - 1) {
		location--;
		for (int i = location; i + 1 < L->length; i++) {
			L->elem[i].no = L->elem[i + 1].no;
			L->elem[i].name = L->elem[i + 1].name;
		}
	}
	L->length--;
	return OK;
}

int CheckNo(List* L, string no)
{
	for (int i = 0; i < L->length; i++)
		if (L->elem[i].no == no)
			return i+1;
	return ERROR;
}

int CheckName(List* L, string name)
{
	for (int i = 0; i < L->length; i++)
		if (L->elem[i].name == name)
			return i+1;
	return ERROR;
}

int PrintElem(List* L, int location)
{
	if (location == ERROR) {
		cout << -1 << endl;
		return ERROR;
	}
	else {
		cout << location<< " " << L->elem[location-1].no << " " << L->elem[location-1].name << endl;
		return OK;
	}
}

int main()
{
	int size;
	InputSize(size);
	InitList(&L);
	CreateList(&L, size);
	string order, name, no;
	int location;
	while (1) {
		cin >> order;
		if (order == "insert") {
			cin >> location;
			if (location > MAXSIZE)
				return ERROR;
			cout << InsertElem(&L, location) << endl;
		}
		else if (order == "remove") {
			cin >> location;
			if (location > MAXSIZE)
				return ERROR;
			cout << RemoveElem(&L, location) << endl;
		}
		else if (order == "check") {
			cin >> order;
			if (order == "no") {
				cin >> no;
				location = CheckNo(&L, no);
				PrintElem(&L, location);
			}
			else if (order == "name") {
				cin >> name;
				location = CheckName(&L, name);
				PrintElem(&L, location);
			}
		}
		else if (order == "end") {
			cout << L.length << endl;
			break;
		}
	}
}
