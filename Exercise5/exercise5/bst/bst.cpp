
namespace lasd {

/* ************************************************************************** */

//Specific constructor from LinearContainer
template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& con)
{
  for(ulong i = 0; i < con.Size(); ++i) { Insert(con[i]); }
}

/* ************************************************************************** */

//Copy constructor
template <typename Data>
BST<Data>::BST(const BST<Data>& bst)
{
  BinaryTreeLnk<Data>::operator=(bst);
}

//Move constructor
template <typename Data>
BST<Data>::BST(BST<Data>&& bst) noexcept
{
  BinaryTreeLnk<Data>::operator=(std::move(bst));
}

//Copy assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst)
{
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

//Move assignment
template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept
{
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

//Comparison operators
template <typename Data>
bool BST<Data>::operator==(const BST<Data>& bst) const noexcept
{
  if(size > 0 && bst.Size() > 0 && (size == bst.Size()))
  {
    BTInOrderIterator<Data> iterator1(*this);
    BTInOrderIterator<Data> iterator2(bst);
    while(!iterator1.Terminated() && !iterator2.Terminated())
    {
      if(*iterator1 != *iterator2)
      {
        return false;
      }
    ++iterator1;
    ++iterator2;
    }
    return true;
  }
  else if(size == 0 && bst.Size() == 0)
  {
    return true;
  }
  return false;
}

template <typename Data>
inline bool BST<Data>::operator!=(const BST<Data>& bst) const noexcept
{
  return !(*this == bst);
}

// Insert copy
template <typename Data>
void BST<Data>::Insert(const Data& value) noexcept
{
  NodeLnk*& ptr = FindPointerTo(root, value);
  if(ptr == nullptr)
  {
    ptr = new NodeLnk(value);
    size++;
  }
}

// Insert move
template <typename Data>
void BST<Data>::Insert(Data&& value) noexcept
{
  NodeLnk*& ptr = FindPointerTo(root, value);
  if(ptr == nullptr)
  {
    ptr = new NodeLnk(std::move(value));
    size++;
  }
}

// Remove
template <typename Data>
void BST<Data>::Remove(const Data& value) noexcept
{
  delete Detach(FindPointerTo(root, value));
}

// Min
template <typename Data>
const Data& BST<Data>::Min() const
{
  if(root != nullptr) { return FindPointerToMin(root)->data; }
  else { throw std::length_error("Tree is empty"); }
}

// MinNRemove
template <typename Data>
Data BST<Data>::MinNRemove()
{
  if(root != nullptr)
  {
    NodeLnk* nodeToRemove = DetachMin(root);
    Data dataToRemove;
    std::swap(dataToRemove, nodeToRemove->data);
    delete nodeToRemove;
    return dataToRemove;
  }
  else { throw std::length_error("Tree is empty"); }
}

// RemoveMin
template <typename Data>
void BST<Data>::RemoveMin()
{
  if(root != nullptr) { delete DetachMin(root); }
  else { throw std::length_error("Tree is empty"); }
}

// Max
template <typename Data>
const Data& BST<Data>::Max() const
{
  if(root != nullptr) { return FindPointerToMax(root)->data; }
  else { throw std::length_error("Tree is empty"); }
}

// MaxNRemove
template <typename Data>
Data BST<Data>::MaxNRemove()
{
  if(root != nullptr)
  {
    NodeLnk* nodeToRemove = DetachMax(root);
    Data dataToRemove;
    std::swap(dataToRemove, nodeToRemove->data);
    delete nodeToRemove;
    return dataToRemove;
  }
  else { throw std::length_error("Tree is empty"); }
}

// RemoveMax
template <typename Data>
void BST<Data>::RemoveMax()
{
  if(root != nullptr) { delete DetachMax(root); }
  else { throw std::length_error("Tree is empty"); }
}


//Predecessor
template <typename Data>
const Data& BST<Data>::Predecessor(const Data& value) const
{
  NodeLnk* const& pointer = FindPointerToPredecessor(root, value);
  if(&pointer != nullptr)
  {
    return pointer->data;
  }
  else
  {
    throw std::length_error("No predecessor found.");
  }
}

//PredecessorNRemove
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& value)
{
  NodeLnk*& pointer = FindPointerToPredecessor(root, value);
  if(&pointer != nullptr)
  {
    NodeLnk* nodeToRemove = Detach(pointer);
    Data dataToRemove;
    std::swap(dataToRemove, nodeToRemove->data);
    delete nodeToRemove;
    return dataToRemove;
  }
  else
  {
    throw std::length_error("No predecessor found.");
  }
}

//RemovePredecessor
template <typename Data>
void BST<Data>::RemovePredecessor(const Data& value)
{
  NodeLnk*& pointer = FindPointerToPredecessor(root, value);
  if(&pointer != nullptr)
  {
    delete Detach(pointer);
  }
  else
  {
    throw std::length_error("No predecessor found.");
  }
}


//Successor
template <typename Data>
const Data& BST<Data>::Successor(const Data& value) const
{
  NodeLnk* const& pointer = FindPointerToSuccessor(root, value);
  if(&pointer != nullptr)
  {
    return pointer->data;
  }
  else
  {
    throw std::length_error("No successor found.");
  }
}

//SuccessorNRemove
template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& value)
{
  NodeLnk*& pointer = FindPointerToSuccessor(root, value);
  if(&pointer != nullptr)
  {
    NodeLnk* nodeToRemove = Detach(pointer);
    Data dataToRemove;
    std::swap(dataToRemove, nodeToRemove->data);
    delete nodeToRemove;
    return dataToRemove;
  }
  else
  {
    throw std::length_error("No successor found.");
  }
}

//RemoveSuccessor
template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& value)
{
  NodeLnk*& pointer = FindPointerToSuccessor(root, value);
  if(&pointer != nullptr)
  {
    delete Detach(pointer);
  }
  else
  {
    throw std::length_error("No successor found.");
  }
}

// Exists override
template <typename Data>
bool BST<Data>::Exists(const Data& value) const noexcept
{
  return(FindPointerTo(root, value) != nullptr);
}

// Auxiliary functions

//Detach
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(typename BST<Data>::NodeLnk*& node) noexcept
{
  if(node != nullptr)
  {
    if(node->Left == nullptr)
    {
      NodeLnk* rightNode = nullptr;
      std::swap(rightNode, node->Right);
      std::swap(rightNode, node);
      --size;
      return rightNode;
    }
    else if(node->Right == nullptr)
    {
      NodeLnk* leftNode = nullptr;
      std::swap(leftNode, node->Left);
      std::swap(leftNode, node);
      --size;
      return leftNode;
    }
    else
    {
      NodeLnk* detachMax = DetachMax(node->Left);
      std::swap(node->data, detachMax->data);
      return detachMax;
    }
  }
  return nullptr;
}

// DetachMin
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& node) noexcept
{
  NodeLnk*& min = FindPointerToMin(node);
  NodeLnk* rightNode = nullptr;
  if(min != nullptr)
  {
    std::swap(rightNode, min->Right);
    std::swap(rightNode, min);
    --size;
  }
  return rightNode;
}

// DetachMax
template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnk*& node) noexcept
{
  NodeLnk*& max = FindPointerToMax(node);
  NodeLnk* leftNode = nullptr;
  if(max != nullptr)
  {
    std::swap(leftNode, max->Left);
    std::swap(leftNode, max);
    --size;
  }
  return leftNode;
}


//FindPointerToMin
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk*& node) noexcept
{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

//FindPointerToMin
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk* const& node) const noexcept
{
  typename BST<Data>::NodeLnk* const* pointer = &node;
  if((*pointer)!= nullptr)
  {
    while ((*pointer)->Left != nullptr)
    {
      pointer = &((*pointer)->Left);
    }
  }
  return *pointer;
}


//FindPointerToMax
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& node) noexcept
{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

//FindPointerToMax
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& node) const noexcept
{
  typename BST<Data>::NodeLnk* const* pointer = &node;
  if((*pointer)!= nullptr)
  {
    while ((*pointer)->Right != nullptr)
    {
      pointer = &((*pointer)->Right);
    }
  }
  return *pointer;
}

//FindPointerTo
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept
{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(node,value));
}

//FindPointerTo
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept
{
  NodeLnk* const* pointer = &node;
  while((*pointer)!= nullptr)
  {
    if(value < (*pointer)->Element())
    {
      pointer = &((*pointer)->Left);
    }
    else if(value > (*pointer)->Element())
    {
      pointer = &((*pointer)->Right);
    }
    else
    {
      return *pointer;
    }
  }
  return *pointer;
}

//FindPointerToPredecessor
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept
{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node,value));
}

//FindPointerToPredecessor
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept
{
  NodeLnk* const* pointer = nullptr;
  NodeLnk* const* current = &node;

  while ((*current)!=nullptr)
  {
      if (value < (*current)->Element()) {
          current = &(*current)->Left;
      }
      else if (value > (*current)->Element())
      {
          pointer = current;
          current = &(*current)->Right;
      }
      else {
          if((*current)->Left) {
              pointer = &FindPointerToMax((*current)->Left);
          }
          return *pointer;
      }
  }

  return *pointer;
}

//FindPointerToSuccessor
template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk*& node, const Data& value) noexcept
{
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node,value));
}

//FindPointerToSuccessor
template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk* const& node, const Data& value) const noexcept
{
  NodeLnk* const* pointer = nullptr;
  NodeLnk* const* current = &node;

  while ((*current)!=nullptr)
  {
      if (value > (*current)->Element()) {
          current = &(*current)->Right;
      }
      else if (value < (*current)->Element())
      {
          pointer = current;
          current = &(*current)->Left;
      }
      else {
          if((*current)->Right) {
              pointer = &FindPointerToMin((*current)->Right);
          }
          return *pointer;
      }
  }
  return *pointer;
}

}
