#include <iostream>
using namespace std;
#define MAXSIZE 50000
#define OK 1

typedef struct seqlist {
    int elem[MAXSIZE];
    int length;
}List;

int SizeInput(int& size)
{
    cin >> size;
    if (!cin.fail())
        return OK;
    else
        return 0;
}

int InitList(List* L)//³õÊ¼»¯
{
    L->length = 0;
    return OK;
}

int CreateList(List* L, int size)
{
    int i;
    for (i = 0; i < size; i++) 
        cin >> L->elem[i];
    L->length = size;
    return OK;
}

int DeleteRepeat(List* L)
{
    int i, j, k;
    for (i = 0; i + 1 < L->length; i++)
        for (j = i + 1; j < L->length; j++) {
            if (L->elem[i] == L->elem[j]) {
                if (j == L->length - 1)
                    L->elem[j] = 0;
                else {
                    for (k = j; k < L->length; k++)
                        L->elem[k] = L->elem[k + 1];
                    L->elem[k] = 0;
                }
                L->length--;
                j--;
            }
        }
    return OK;
}

int PrintList(List* L)
{
    for (int i = 0; i < L->length; i++)
        cout << L->elem[i] << " ";
    cout << endl;
    return OK;
}

int main()
{
    int size = 0;
    List L;
    if (!SizeInput(size)) {
        cout << "input error!";
        return 0;
    }
    InitList(&L);
    CreateList(&L, size);
    DeleteRepeat(&L);
    PrintList(&L);
}