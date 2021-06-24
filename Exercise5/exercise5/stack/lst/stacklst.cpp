
namespace lasd {

/* ************************************************************************** */

//Specific constructor
template<typename Data>
StackLst<Data>::StackLst(const LinearContainer<Data>& con)
{
  ulong i = 0;
  while(i < con.Size())
  {
    this->InsertAtBack(con[i]);
    i++;
  }
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& stack)
{
  typename List<Data>::Node* tmp = stack.head;
  while(tmp != nullptr)
  {
    this->InsertAtBack(tmp->data);
    tmp = tmp->next;
  }
}

// Move constructor
template<typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& stack) noexcept
{
  std::swap(stack.head, head);
  std::swap(stack.size, size);
}

// Copy assignment
template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack)
{
  StackLst<Data> *tmp = new StackLst<Data>(stack);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack) noexcept
{
  std::swap(stack.head, head);
  std::swap(stack.size, size);
  return *this;
}
/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stacklst) const noexcept
{
  typename List<Data>::Node* stack1 = head;
  typename List<Data>::Node* stack2 = stacklst.head;
  if(this->Size()==stacklst.Size())
  {
    while(stack1 != nullptr && stack2 != nullptr)
    {
      if((stack1->data) != (stack2->data))
      {
        return false;
      }
      stack1 = stack1->next;
      stack2 = stack2->next;
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool StackLst<Data>::operator!=(const StackLst<Data>& stack) const noexcept
{
  return !(*this == stack);
}

/* ************************************************************************** */
// Specific member functions (inherited from Stack)
template<typename Data>
void StackLst<Data>::Push(const Data& val)  {  //Copy
  this->InsertAtFront(val);
}

template<typename Data>
void StackLst<Data>::Push(Data&& val) noexcept{  //Move
  this->InsertAtFront(val);
}

template<typename Data>
Data& StackLst<Data>::Top() const {
  if(size > 0)
  {
    return this->Front();
  }
  else
  {
    throw std::length_error("Stack is empty.");
  }
}

template<typename Data>
void StackLst<Data>::Pop(){
  if(size > 0)
  {
    this->RemoveFromFront();
  }
  else
  {
    throw std::length_error("Stack is empty.");
  }
}

template<typename Data>
Data StackLst<Data>::TopNPop(){
  if(size > 0)
  {
    Data deletedElement = Top();
    Pop();
    return deletedElement;
  }
  else
  {
    throw std::length_error("Stack is empty.");
  }
}

template<typename Data>
void StackLst<Data>::Clear(){
  while(size > 0)
  {
    Pop();
  }
}
/* ************************************************************************** */
}
