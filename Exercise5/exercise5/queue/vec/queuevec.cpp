#include <iostream>

namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
QueueVec<Data>::QueueVec(){
  Elements = new Data[2] {};
  size = 2;
  actualSize = 0;
  head = 0;
  tail = 0;
}

// A stack obtained from a LinearContainer
template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& con)
{
  Elements = new Data[2] {};
  size = 2;
  actualSize = 0;
  head = 0;
  tail = 0;
  for(ulong index = 0; index < con.Size(); ++index)
  {
    Enqueue(con[index]);
  }
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& queue)
{
  Elements = new Data[queue.size];
  std::copy(queue.Elements, queue.Elements + queue.size, Elements);
  head = queue.head;
  tail = queue.tail;
  size = queue.size;
  actualSize = queue.actualSize;
}

// Move constructor
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept
{
  std::swap(queue.Elements, Elements);
  std::swap(queue.head, head);
  std::swap(queue.tail, tail);
  std::swap(queue.size, size);
  std::swap(queue.actualSize, actualSize);
}

// Copy assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue)
{
  QueueVec<Data> *tmp = new QueueVec<Data>(queue);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment
template<typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept
{
  std::swap(queue.Elements, Elements);
  std::swap(queue.head, head);
  std::swap(queue.tail, tail);
  std::swap(queue.size, size);
  std::swap(queue.actualSize, actualSize);
  return *this;
}

/************************************************************************** */

// Comparison operators
template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept
{
  if(actualSize == queue.actualSize)
  {
    for(ulong index = 0; index<actualSize; index++)
    {
      if(Elements[(index+head)%size] != queue.Elements[(index+queue.head)%queue.size])
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

template<typename Data>
inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept
{
  return !(*this == queue);
}

/* ************************************************************************** */

// Specific member functions (inherited from queue)
template<typename Data>
void QueueVec<Data>::Enqueue(const Data& val) //Copy
{
  if(actualSize + 1 == size)
  {
    Expand();
  }
  Elements[tail] = val;
  tail=(tail+1)%size;
  actualSize++;
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data&& val) noexcept //Move
{
  if(actualSize + 1 == size)
  {
    Expand();
  }
  Elements[tail] = std::move(val);
  tail=(tail+1)%size;
  actualSize++;
}

template<typename Data>
Data& QueueVec<Data>::Head() const {
  if(actualSize > 0)
  {
    return Elements[head];
  }
  else
  {
    throw std::length_error("Queue is empty.");
  }
}

template<typename Data>
void QueueVec<Data>::Dequeue(){
  if(actualSize > 0)
  {
    if(actualSize - 1 == (size - (size/4)))
    {
      Reduce();
    }
    head=(head+1)%size;
    actualSize--;
  }
  else
  {
    throw std::length_error("Queue is empty.");
  }
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue(){
  if(actualSize > 0)
  {
    Data deletedElement = Head();
    Dequeue();
    return deletedElement;
  }
  else
  {
    throw std::length_error("Queue is empty.");
  }
}

template<typename Data>
bool QueueVec<Data>::Empty() const noexcept{
  return (actualSize == 0);
}

template<typename Data>
ulong QueueVec<Data>::Size() const noexcept{
  return actualSize;
}

template<typename Data>
void QueueVec<Data>::Clear(){
  delete[] Elements;
  Elements = new Data[2] {};
  size = 2;
  actualSize = 0;
  head = 0;
  tail = 0;
}

template<typename Data>
void QueueVec<Data>::Expand(){
  Data* vec = new Data[size*2] {};
  ulong j=0;
  for(ulong index = 0; index<actualSize; index++)
  {
    std::swap(Elements[(index+head)%size], vec[j]);
    j++;
  }
  std::swap(Elements, vec);
  size = size*2;
  head = 0;
  tail = actualSize;
  delete[] vec;
}

template<typename Data>
void QueueVec<Data>::Reduce(){
  Data* vec = new Data[(size - (size/4))] {};
  ulong j=0;
  for(ulong index = 0; index<actualSize; index++)
  {
    std::swap(Elements[(index+head)%size], vec[j]);
    j++;
  }
  std::swap(Elements, vec);
  size = (size - (size/4));
  head = 0;
  tail = actualSize;
  delete[] vec;
}

/* ************************************************************************** */
}
