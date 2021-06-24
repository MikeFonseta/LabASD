
namespace lasd {

/* ************************************************************************** */

// Specific constructor
template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& con)
{
  for(ulong index = 0; index < con.Size(); ++index)
  {
    Enqueue(con[index]);
  }
}

/* ************************************************************************** */

// Copy constructor
template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst& queue)
{
  typename List<Data>::Node* tmp = queue.head;
  while(tmp != nullptr)
  {
    Enqueue(tmp->data);
    tmp = tmp->next;
  }
}

// Move constructor
template<typename Data>
QueueLst<Data>::QueueLst(QueueLst&& queue) noexcept
{
  std::swap(queue.head, head);
  std::swap(queue.tail, tail);
  std::swap(queue.size, size);
}

// Copy assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst& queue)
{
  QueueLst<Data> *tmp = new QueueLst<Data>(queue);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;

}

// Move assignment
template<typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst&& queue) noexcept
{
  std::swap(queue.head, head);
  std::swap(queue.tail, tail);
  std::swap(queue.size, size);
  return *this;

}
/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept
{
  typename List<Data>::Node* queue1 = head;
  typename List<Data>::Node* queue2 = queue.head;
  if(this->Size()==queue.Size())
  {
    while(queue1 != nullptr && queue2 != nullptr)
    {
      if((queue1->data) != (queue2->data))
      {
        return false;
      }
      queue1 = queue1->next;
      queue2 = queue2->next;
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept
{
  return !(*this == queue);
}

/* ************************************************************************** */

// Specific member functions (inherited from queue)
template<typename Data>
void QueueLst<Data>::Enqueue(const Data& val) //Copy
{
  this->InsertAtBack(val);
}

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& val) noexcept //Move
{
  this->InsertAtBack(std::move(val));
}

template<typename Data>
Data& QueueLst<Data>::Head() const {
  if(size > 0)
  {
    return this->Front();
  }
  else
  {
    throw std::length_error("Queue is empty.");
  }
}

template<typename Data>
void QueueLst<Data>::Dequeue(){
  if(size > 0)
  {
    this->RemoveFromFront();
  }
  else
  {
    throw std::length_error("Queue is empty.");
  }
}

template<typename Data>
Data QueueLst<Data>::HeadNDequeue(){
  if(size > 0)
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
void QueueLst<Data>::Clear(){
  while(size > 0)
  {
    Dequeue();
  }
}

/* ************************************************************************** */
}
