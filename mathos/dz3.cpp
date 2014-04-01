#include <iostream>

using namespace std;

class data
{
public:
   int key;
   data(){key = 0;};
   data(int val){ key = val; }
   void print()
   {
       cout << key << " ";
   }
};

class node
{
public:
   data d;
   node* prev;
   node* next;
   node();
   node(data& d, node* prev, node* next)
   {
       this->d = d;
       this->prev = prev;
       this->next = next;
   }
};

node::node(): d(0),prev(NULL),next(NULL)
{
}

class DLList
{
protected:
   node* _head;
   node* _tail;
public:
   DLList();
   DLList(const DLList& d);
   ~DLList();
   void push_front(data& d);
   void push_back(data& d);

   void pop_front();
   void pop_back();
   void remove(data* ptr_d);
   void printList();
   node* head() const;
   node* tail() const;
};

DLList::DLList()
{
   _head = NULL;
   _tail = NULL;
}

DLList::~DLList()
{
   if(_head)
   {
       while(_head)
       {
           pop_front();
       }
   }
}
void DLList::push_front(data& d)
{

   node * newNode = new node();
   newNode->d.key = d.key;
   newNode->next=_head;

   if(_head != NULL)
   {
       _head->prev = newNode;
   }
   else
   {
       _tail = newNode;
   }
   _head = newNode;
}


void DLList::push_back(data& d)
{
   node * newNode = new node();
   newNode->d.key = d.key;
   newNode->prev=_tail;
   if(_tail != NULL)
   {
       _tail->next = newNode;
   }
   else
   {
       _head = newNode;
   }
   _tail = newNode;
}


void DLList::pop_front()
{
   if(_head->next)
   {
       node * tmp = _head;
       _head = _head->next;
       _head->prev = NULL;
       delete tmp;
   }
   else if(_head)
   {
       node * tmp = _head;
       _head = NULL;
       delete tmp;
   }
}

void DLList::pop_back()
{
   if(_tail->prev)
   {
       node * tmp = _tail;
       _tail = _tail->prev;
       _tail->next = NULL;
       delete tmp;
   }
   else if(_tail)
   {
       node * tmp = _tail;
       _tail = NULL;
       delete tmp;
   }
}

void DLList::printList()
{
   if(_head)
   {
       node * tmp =_head;
       while(tmp)
       {
           tmp->d.print();
           tmp = tmp->next;
       }
   }
}
int main()
{
   data d1(5);
   data d2(4);
   data d3(-1);
   data d4(-7);
   data d5(11);

   DLList L;
   L.push_front(d1);
   L.push_front(d2);
   L.push_front(d3);
   L.printList();
   cout << endl;

   L.push_back(d4);
   L.push_back(d5);
   L.printList();
   cout << endl;

   L.pop_front();

   L.pop_back();
   L.printList();
   cout << endl;
   return 0;
}