
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
StackVec<Data>::StackVec(){
  Elements = new Data[1] {};
  size = 1;
  next = 0;
}

// A stack obtained from a LinearContainer
template <typename Data>
StackVec<Data>::StackVec(const LinearContainer<Data>& con)
{
  Elements = new Data[1] {};
  size = 1;
  next = 0;
  for (ulong i=0; i<con.Size(); i++)
  {
    Push(con[i]);
  }
}
/* ************************************************************************** */

// Copy constructor
template<typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& stackVec):Vector<Data>(stackVec)
{
  next = stackVec.next;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stackVec) noexcept
{
    std::swap(Elements, stackVec.Elements);
    std::swap(next, stackVec.next);
    std::swap(size, stackVec.size);
}

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stackVec)
{
  Vector<Data>::operator=(stackVec);
  next = stackVec.next;
  return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stackVec) noexcept
{
  Vector<Data>::operator=(std::move(stackVec));
  std::swap(next, stackVec.next);
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& stackVec) const noexcept
{
  if(next==stackVec.Size())
  {
    for(ulong i=stackVec.Size(); i>0; i--)
    {
      if(Elements[i-1]!=stackVec.Elements[i-1])
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool StackVec<Data>::operator!=(const StackVec<Data>& stackVec) const noexcept
{
  return !(*this == stackVec);
}

/* ************************************************************************** */

//Copy PUSH
template <typename Data>
void StackVec<Data>::Push(const Data& val)
{
  if(next == size-1)
  {
    Expand();
  }
  Elements[next] = val;
  next++;
}

//move PUSH
template <typename Data>
void StackVec<Data>::Push(Data&& val) noexcept
{
  if(next == size-1)
  {
    Expand();
  }
  Elements[next] = std::move(val);
  next++;
}

template <typename Data>
void StackVec<Data>::Pop()
{
  if(next > 0)
  {
    next--;
    if(next == (size/2))
    {
      Reduce();
    }
  }
  else
  {
    throw std::length_error("Stack is empty.");
  }
}

template <typename Data>
Data& StackVec<Data>::Top() const
{
  if(next > 0)
  {
    return Elements[next-1];
  }
  else
  {
    throw std::length_error("Stack is empty.");
  }
}

//TopNPop
template <typename Data>
Data StackVec<Data>::TopNPop()
{
  Data valueRemoved = Top();
  Pop();
  return valueRemoved;
}

template <typename Data>
void StackVec<Data>::Expand()
{
    this->Resize(size * 2);
}

template <typename Data>
void StackVec<Data>::Reduce()
{
    this->Resize(size - (size / 4));
}

/* ************************************************************************** */

template <typename Data>
bool StackVec<Data>::Empty() const noexcept
{
  return (next==0);
}

template <typename Data>
ulong StackVec<Data>::Size() const noexcept
{
  return next;
}

template <typename Data>
void StackVec<Data>::Clear()
{
  while(next>0)
  {
    Pop();
  }
}

}
