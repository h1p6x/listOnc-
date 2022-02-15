#include <iostream>
#include <fstream>
#include <cstdlib>
#include <locale.h>

using namespace std;

typedef struct List_s
{
  int field; /// Поле данных
  List_s* next; /// Указатель на следующий элемент
  List_s* prev; /// Указатель на предыдущий элемент
} List;

List* init(int value)  /// value - значение первого узла
{
  List *lst = (List*) malloc(sizeof(List));

  if (!lst)
  {
      cout<<"Память не доступна";
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
      cerr<<"Память не доступна";
      return NULL;
  }

  p = lst->next; /// Cохранение указателя на следующий узел
  lst->next = temp; /// Предыдущий узел указывает на создаваемый

  temp->field = value; /// Сохранение поля данных добавляемого узла
  temp->next = p; /// Созданный узел указывает на следующий узел
  temp->prev = lst; /// Созданный узел указывает на предыдущий узел

  if (p != NULL)
  {
    p->prev = temp;
  }

  return(temp);
}

List* deletelem(List* lst)
{
  List* prev, *next;

  prev = lst->prev; /// Узел, предшествующий lst
  next = lst->next; /// Узел, следующий за lst

  if (prev != NULL)
  {
    prev->next = lst->next; /// Переставляем указатель
  }

  if (next != NULL)
  {
    next->prev = lst->prev; /// Переставляем указатель
  }

  free(lst); /// Освобождаем память удаляемого элемента
  return(prev);
}

List* deletehead(List* root)
{
  List* temp;

  temp = root->next;
  temp->prev = NULL;

  free(root);   /// Освобождение памяти текущего корня

  return(temp); /// Новый корень списка
}

void listprint(List* lst)
{
  List* p = lst;

  do
  {
    cout << p->field << ' '; /// Вывод значения элемента p
    p = p->next; /// Переход к следующему узлу
  } while (p != NULL); /// Условие окончания обхода
}

int main()
{
  setlocale(0, "");
  ifstream input_file("input.txt");

  if (!input_file.is_open())
  {
    cerr << "Файл не найден!";
    return -1;
  }

  int buf = 0; /// Считываем в buf числа из файла

  input_file >> buf;
  List* root = init(buf); /// Корневой элемент

  input_file >> buf;
  List* endOfList = addelem(root, buf); /// Указатель на последний элемент

  /// Записываем все числа из файла в список
  while (!input_file.eof())
  {
    input_file >> buf;
    endOfList = addelem(endOfList, buf);
  }

  long long s = 1; /// Результат выражения

  List* begin = root;    /// Первый элемент списка
  List* end = endOfList; /// Последний элемент списка

  while (begin != NULL)
  {
    int x1 = begin->field;
    int x2 = end->field;

    s *= (x1 * x1) - (x2 * x2);

    begin = begin->next;
    end = end->prev;
  }

  cout << "\n\n\tЗачения записанные в список = ";
  listprint(root);
  cout << "\n\n\tЗначение выражения S = " << s << endl;

  cout << endl << endl;

  /// Освобождаем память
  while (endOfList != NULL)
  {
    endOfList = deletelem(endOfList);
  }
}
