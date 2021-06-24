
namespace lasd {

/* ************************************************************************** */

// Specific Constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& con)
{
  vec.Resize(con.Size());
  size = con.Size();
  for(int i = 0; i < size; i++)
  {
    NodeVec* tmp = new NodeVec();
    tmp->data = con[i];
    tmp->index = i;
    tmp->treevec = &vec;
    vec[i] = tmp;
  }
}

// Copy Constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& bt)
{
  vec.Resize(bt.size);
  size = bt.size;
  for(int i = 0; i < size; i++)
  {
    NodeVec* tmp = new NodeVec();
    tmp->data = bt.vec[i]->data;
    tmp->index = bt.vec[i]->index;
    tmp->treevec = bt.vec[i]->treevec;
    vec[i] = tmp;
  }
}

// Move Constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& bt) noexcept
{
  vec = std::move(bt.vec);
  std::swap(size, bt.size);
}

// Copy Assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& bt)
{
  BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(bt);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move Assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& bt) noexcept
{
  vec = std::move(bt.vec);
  std::swap(size, bt.size);
  return *this;
}

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec& bt) const noexcept
{
  return (vec==bt.vec && size==bt.size);
}

template <typename Data>
inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec& bt) const noexcept
{
  return !(*this==bt);
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const
{
  if(size > 0)
  {
    return *vec[0];
  }
  else
  {
    throw std::length_error("BinaryTree is empty.");
  }
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec()
{
  Clear();
}

template <typename Data>
void BinaryTreeVec<Data>::Clear()
{
  if(size > 0)
  {
    for(ulong i = 0; i < vec.Size(); i++)
    {
      NodeVec *tmp = vec[i];
      vec[i]->treevec = nullptr;
      vec[i] = nullptr;
      delete tmp;
    }
    vec.Resize(0);
    size = 0;
  }
}

/* ************************************************************************** */


template <typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept
{
  return data;
}

template <typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept
{
  return data;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
{
  return (2*(index) + 1 < treevec->Size());
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
{
  return (2*(index) + 2 < treevec->Size());
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const
{
  if(treevec->Size() > 0)
  {
    return *(treevec->operator[]((index*2)+1));
  }
  else
  {
    throw std::out_of_range("Left child does not exsist");
  }
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const
{
  if(treevec->Size() > 0)
  {
    return *(treevec->operator[]((index*2)+2));
  }
  else
  {
    throw std::out_of_range("Right child does not exsist");
  }
}


/* ************************************************************************** */
}
