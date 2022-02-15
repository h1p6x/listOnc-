#include <iostream>
#include <fstream>
#include <cstdlib>
#include <locale.h>

using namespace std;

typedef struct List_s
{
  int field; /// ���� ������
  List_s* next; /// ��������� �� ��������� �������
  List_s* prev; /// ��������� �� ���������� �������
} List;

List* init(int value)  /// value - �������� ������� ����
{
  List *lst = (List*) malloc(sizeof(List));

  if (!lst)
  {
      cout<<"������ �� ��������";
      return NULL;
  }


  lst->field = value;
  lst->next = NULL;
  lst->prev = NULL;

  return(lst);
}

List* addelem(List* lst, int value)
{
  List *temp, *p;
  temp = (List*) malloc(sizeof(List));

  if(!temp)
  {
      cerr<<"������ �� ��������";
      return NULL;
  }

  p = lst->next; /// C��������� ��������� �� ��������� ����
  lst->next = temp; /// ���������� ���� ��������� �� �����������

  temp->field = value; /// ���������� ���� ������ ������������ ����
  temp->next = p; /// ��������� ���� ��������� �� ��������� ����
  temp->prev = lst; /// ��������� ���� ��������� �� ���������� ����

  if (p != NULL)
  {
    p->prev = temp;
  }

  return(temp);
}

List* deletelem(List* lst)
{
  List* prev, *next;

  prev = lst->prev; /// ����, �������������� lst
  next = lst->next; /// ����, ��������� �� lst

  if (prev != NULL)
  {
    prev->next = lst->next; /// ������������ ���������
  }

  if (next != NULL)
  {
    next->prev = lst->prev; /// ������������ ���������
  }

  free(lst); /// ����������� ������ ���������� ��������
  return(prev);
}

List* deletehead(List* root)
{
  List* temp;

  temp = root->next;
  temp->prev = NULL;

  free(root);   /// ������������ ������ �������� �����

  return(temp); /// ����� ������ ������
}

void listprint(List* lst)
{
  List* p = lst;

  do
  {
    cout << p->field << ' '; /// ����� �������� �������� p
    p = p->next; /// ������� � ���������� ����
  } while (p != NULL); /// ������� ��������� ������
}

int main()
{
  setlocale(0, "");
  ifstream input_file("input.txt");

  if (!input_file.is_open())
  {
    cerr << "���� �� ������!";
    return -1;
  }

  int buf = 0; /// ��������� � buf ����� �� �����

  input_file >> buf;
  List* root = init(buf); /// �������� �������

  input_file >> buf;
  List* endOfList = addelem(root, buf); /// ��������� �� ��������� �������

  /// ���������� ��� ����� �� ����� � ������
  while (!input_file.eof())
  {
    input_file >> buf;
    endOfList = addelem(endOfList, buf);
  }

  long long s = 1; /// ��������� ���������

  List* begin = root;    /// ������ ������� ������
  List* end = endOfList; /// ��������� ������� ������

  while (begin != NULL)
  {
    int x1 = begin->field;
    int x2 = end->field;

    s *= (x1 * x1) - (x2 * x2);

    begin = begin->next;
    end = end->prev;
  }

  cout << "\n\n\t������� ���������� � ������ = ";
  listprint(root);
  cout << "\n\n\t�������� ��������� S = " << s << endl;

  cout << endl << endl;

  /// ����������� ������
  while (endOfList != NULL)
  {
    endOfList = deletelem(endOfList);
  }
}
