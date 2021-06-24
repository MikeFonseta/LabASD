
#include <iostream>
namespace lasd {

/* ************************************************************************** */

// Constructors
template<typename Data>
List<Data>::List(const LinearContainer<Data>& con)
{
  for(ulong i = 0; i < con.Size(); i++)
  {
    InsertAtBack(con[i]);
  }
}

/* ************************************************************************** */

// Destructor
template<typename Data>
List<Data>::~List()
{
  Clear();
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
List<Data>::List(const List& list)
{
  if(list.size > 0)
  {
    for(unsigned long i = 0; i < list.Size(); i++)
    {
      InsertAtBack(list[i]);
    }
  }
  size = list.size;
}

// Move constructor
template<typename Data>
List<Data>::List(List&& list) noexcept
{
  std::swap(list.head, head);
  std::swap(list.tail, tail);
  std::swap(list.size, size);
}

// Copy assignment
template<typename Data>
List<Data>& List<Data>::operator=(const List& list)
{
  List<Data> *tmp = new List<Data>(list);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
List<Data>& List<Data>::operator=(List&& list) noexcept
{
  std::swap(list.head, head);
  std::swap(list.tail, tail);
  std::swap(list.size, size);
  return *this;
}

/**************************************************/

// Specific member functions
template<typename Data>
void List<Data>::InsertAtFront(const Data& val){ //Copy

  Node* tmp = new Node(val);
  tmp->next = head;
  head = tmp;
  if(size == 0)
  {
    tail = tmp;
  }
  size++;
}

template<typename Data>
void List<Data>::InsertAtFront(Data&& val) noexcept //Move
{
  Node* tmp = new Node(std::move(val));
  tmp->next = head;
  head = tmp;
  if(size == 0)
  {
    tail = tmp;
  }
  size++;
}

template<typename Data>
void List<Data>:: RemoveFromFront()
{
  if(head != nullptr)
  {
    Node* tmp;
    tmp = head;
    head = tmp->next;
    size --;
    delete tmp;
  }
  else
  {
    throw std::length_error("List is empty.");
  }
}

template<typename Data>
Data List<Data>::FrontNRemove()
{
  if(head != nullptr)
  {
    Data deletedElement = Front();
    RemoveFromFront();
    return deletedElement;
  }
  else
  {
    throw std::length_error("List is empty.");
  }

}

template<typename Data>
void List<Data>::InsertAtBack(const Data& val) //Copy
{
    Node* tmp = new Node(val);
    if(head == nullptr)
	  {
		  head = tmp;
      tail = tmp;
    }
    else
    {
      tail->next = tmp;
      tail = tmp;
    }
    size++;
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& val) noexcept //Move
{
    Node* tmp = new Node();
    std::swap(tmp->data, val);
    if(head == nullptr)
	  {
      head = tmp;
      tail = tmp;
    }
    else
    {
      tail->next = tmp;
      tail = tmp;
    }
    size++;
}

template<typename Data>
void List<Data>::Clear()
{
  while(head != nullptr)
  {
    RemoveFromFront();
  }
}

template<typename Data>
Data& List<Data>::Front() const
{
  if(head == nullptr)
  {
    throw std::length_error("List is empty.");
  }
  else
  {
    return head->data;
  }
}

template<typename Data>
Data& List<Data>::Back() const
{
  if(head == nullptr)
  {
    throw std::length_error("List is empty.");
  }
  else
  {
    return tail->data;
  }
}

/**************************************************/

// Operators
template<typename Data>
Data& List<Data>::operator[](const unsigned long index) const
{
  Node *tmp;
  int i = 0;
  if(index == 0)
  {
    return head->data;
  }
  if(index == size - 1)
  {
    return tail->data;
  }
  if(index < size)
  {
    tmp = head;
    while(i != index)
    {
      tmp = tmp->next;
      i++;
    }
      return tmp->data;
  }
  else
  {
    throw std::out_of_range("Unable to access the location " + std::to_string(index) + " in a list of dimension " + std::to_string(size) + ".");
  }
}

template <typename Data>
bool List<Data>::operator==(const List<Data>& list) const noexcept
{
  Node* tmp = head;
  Node* list2 = list.head;
  if(size==list.size)
  {
    while(tmp != nullptr)
    {
      if((tmp->data) != (list2->data))
      {
        return false;
      }
      tmp = tmp->next;
      list2 = list2->next;
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& vec) const noexcept
{
  return !(*this == vec);
}

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)
template<typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par){
  for(ulong index = 0; index < size; index++){
    fun((*this)[index], par);
  }
}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par){
  for(ulong index = size; index > 0; index--){
    fun((*this)[index-1], par);
  }
}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)
template <typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const{
  for(ulong index = 0; index < size; ++index){
    fun((*this)[index], par, acc);
  }
}

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const{
  for(ulong index = size; index > 0; --index){
    fun((*this)[index-1], par, acc);
  }
}

/* ************************************************************************** */

}
