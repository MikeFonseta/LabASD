
namespace lasd {

/* ************************************************************************** */

// Specific Constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& con)
{
  root = createBinaryTreeLnk(0, root, con);
  size = con.Size();
}

// Auxilary Function For Specific Constructor
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::createBinaryTreeLnk(ulong i, BinaryTreeLnk<Data>::NodeLnk* node, const LinearContainer<Data>& con)
{
    if (i < con.Size())
    {
        NodeLnk* temp = new NodeLnk(con[i]);
        node = temp;
        node->Left = createBinaryTreeLnk((2 * i) + 1,node->Left, con);
        node->Right = createBinaryTreeLnk((2 * i) + 2,node->Right, con);
    }
    return node;
}

// Copy Constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt)
{
  if(bt.size > 0)
  {
    root = Add(bt.root);
    size = bt.size;
  }
  else
  {
    root = nullptr;
    size = 0;
  }
}

// Move Constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) noexcept
{
  std::swap(root, bt.root);
  std::swap(size, bt.size);
}

// Copy Assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt)
{
  BinaryTreeLnk<Data> *tmp = new BinaryTreeLnk<Data>(bt);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move Assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) noexcept
{
  root = std::move(bt.root);
  std::swap(size, bt.size);
  return *this;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const
{
  if(size > 0)
  {
    return *root;
  }
  else
  {
    throw std::length_error("BinaryTree is empty.");
  }
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk()
{
  Clear();
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear()
{
  if(size > 0)
  {
    delete root;
    root = nullptr;
    size = 0;
  }
}
/* ************************************************************************** */

//NodeLnk functions
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& value)
{
  data = value;
  Left = nullptr;
  Right = nullptr;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
{
  if(HasLeftChild())
  {
    delete Left;
    Left = nullptr;
  }
  if(HasRightChild())
  {
    delete Right;
    Right = nullptr;
  }
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::Add(NodeLnk* node)
{
  NodeLnk* tmp = new NodeLnk(node->Element());
  if(node->HasLeftChild())
  {
    tmp->Left = Add(node->Left);
  }
  if(node->HasRightChild())
  {
    tmp->Right = Add(node->Right);
  }
  return tmp;
}


template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept
{
  return data;
}

template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept
{
  return data;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept
{
  return (Left != nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept
{
  return (Right != nullptr);
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
{
  if(Left != nullptr)
  {
    return *Left;
  }
  else
  {
    throw std::out_of_range("Left child does not exsist");
  }
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const
{
  if(Right != nullptr)
  {
    return *Right;
  }
  else
  {
    throw std::out_of_range("Right child does not exsist");
  }
}


/* ************************************************************************** */


}
