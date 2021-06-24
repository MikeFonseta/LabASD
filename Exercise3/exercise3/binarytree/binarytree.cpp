
#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& node) const noexcept
{
  bool value = true;
  if(Element() == node.Element())
  {
    if(HasLeftChild() && node.HasLeftChild()) { value = (LeftChild() == node.LeftChild()); }
    else if(HasLeftChild() && !node.HasLeftChild()) return false;

    if(value)
    {
      if(HasRightChild() && node.HasRightChild()) { value = (RightChild() == node.RightChild()); }
      else if(HasRightChild() && !node.HasRightChild()) return false;
    }
  }else
  {
    return false;
  }
  return value;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& node) const noexcept
{
  return !(this == node);
}

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& bt) const noexcept
{
  if(size > 0 && bt.size > 0)
  {
    return (Root() == bt.Root());
  }
  else if(size == 0 && bt.size == 0)
  {
    return true;
  }
  return false;
}

template <typename Data>
inline bool BinaryTree<Data>::operator!=(const BinaryTree& bt) const noexcept
{
  if(size > 0 && bt.size > 0)
  {
    return !(Root() == bt.Root());
  }
  else if(size == 0 && bt.size == 0)
  {
    return false;
  }
  return true;
}

/* ************************************************************************** */

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par, Node& key)
{
  fun(key.Element(),par);
  if(key.HasLeftChild()) { MapPreOrder(fun,par,key.LeftChild()); }
  if(key.HasRightChild()){ MapPreOrder(fun,par,key.RightChild());}
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par, Node& key)
{
  if(key.HasLeftChild()) { MapPostOrder(fun,par,key.LeftChild()); }
  if(key.HasRightChild()){ MapPostOrder(fun,par,key.RightChild());}
  fun(key.Element(),par);
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par, Node& key)
{
  if(key.HasLeftChild()) { MapPostOrder(fun,par,key.LeftChild()); }
  fun(key.Element(),par);
  if(key.HasRightChild()){ MapPostOrder(fun,par,key.RightChild());}
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par, Node& key)
{
  QueueLst<Node*> queue;
  queue.Enqueue(&key);

  while (!queue.Empty())
  {
    Node * currnode = queue.HeadNDequeue();
    fun(currnode->Element(), par);
    if(currnode->HasLeftChild()) { queue.Enqueue(&(currnode->LeftChild())); }
    if(currnode->HasRightChild()) { queue.Enqueue(&(currnode->RightChild())); }
  }
}


template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const
{
  fun(key.Element(),par, acc);
  if(key.HasLeftChild()) { FoldPreOrder(fun,par,acc,key.LeftChild()); }
  if(key.HasRightChild()){ FoldPreOrder(fun,par,acc,key.RightChild());}
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const
{
  if(key.HasLeftChild()) { FoldPostOrder(fun,par,acc,key.LeftChild()); }
  if(key.HasRightChild()){ FoldPostOrder(fun,par,acc,key.RightChild());}
  fun(key.Element(),par, acc);
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc, Node& key) const
{
  if(key.HasLeftChild()) { FoldPostOrder(fun,par,acc,key.LeftChild()); }
  fun(key.Element(),par, acc);
  if(key.HasRightChild()){ FoldPostOrder(fun,par,acc,key.RightChild());}
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc, Node& key) const
{
  QueueLst<Node*> queue;
  queue.Enqueue(&key);

  while (!queue.Empty())
  {
    Node* node = queue.HeadNDequeue();
    fun(node->Element(), par, acc);
    if(node->HasLeftChild()) { queue.Enqueue(&(node->LeftChild())); }
    if(node->HasRightChild()) { queue.Enqueue(&(node->RightChild())); }
  }
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void* par)
{
  if(size > 0) { MapPreOrder(fun,par,Root()); }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void* par)
{
  if(size > 0) { MapPostOrder(fun,par,Root()); }
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void* par)
{
  if(size > 0) { MapInOrder(fun,par,Root()); }
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void* par)
{
  if(size > 0) { MapBreadth(fun,par,Root()); }
}


template <typename Data>
void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  if(size > 0) { FoldPreOrder(fun,par,acc,Root()); }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  if(size > 0) { FoldPostOrder(fun,par,acc,Root()); }
}


template <typename Data>
void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  FoldInOrder(fun,par,acc,Root());
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void* par, void* acc) const
{
  if(size > 0) { FoldBreadth(fun,par,acc,Root()); }
}

/* ************************************************************************** */

//BTPreOrderIterator
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt)
{
  if(bt.Size() != 0)
  {
    current = &(bt.Root());
  }
}

// Copy Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
}

// Move Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& iterator) noexcept
{
  std::swap(current,iterator.current);
  stk = std::move(iterator.stk);
}

// Copy Assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
  return *this;
}

// Move Assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& iterator) noexcept
{
  std::swap(current,iterator.current);
  stk = std::move(iterator.stk);
  return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept
{
  return (current == nullptr);
}

template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const
{
  if(!Terminated())
  {
    return current->Element();
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++()
{
  if(!Terminated())
  {
    if(current->HasLeftChild())
    {
      if(current->HasRightChild())
      {
        stk.Push(&(current->RightChild()));
      }
      current = &(current->LeftChild());
    }else if(current->HasRightChild())
    {
        current = &(current->RightChild());
    }else
    {
      if(!stk.Empty())
      {
        current = stk.TopNPop();
      }else
      {
        current = nullptr;
      }
    }
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }

  return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& iterator) const noexcept
{
  if(current == iterator.current && stk == iterator.stk)
  {
    return true;
  }
  return false;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& iterator) const noexcept
{
  return !(*this == iterator);
}


/* ************************************************************************** */


//BTPostOrderIterator
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt)
{
  current = MostLeaf(&bt.Root());
}

template <typename Data>
typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::MostLeaf(typename BinaryTree<Data>::Node* node)
{
  if(node->HasLeftChild())
  {
    stk.Push(node);
    return MostLeaf(&node->LeftChild());
  }
  if(node->HasRightChild())
  {
    stk.Push(node);
    return MostLeaf(&node->RightChild());
  }
  return node;
}

// Copy Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
}

// Move Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  stk = std::move(iterator.stk);
}

// Copy Assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
  return *this;
}

// Move Assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  stk = std::move(iterator.stk);
  return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept
{
  return (current == nullptr);
}

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const
{
  if(!Terminated())
  {
    return current->Element();
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++()
{
  if(!Terminated())
  {
    if(!stk.Empty())
    {
      typename BinaryTree<Data>::Node* tmp = stk.Top();
      if(&tmp->LeftChild() == current && tmp->HasRightChild())
      {
        current = MostLeaf(&tmp->RightChild());
      }
      else
      {
        current = stk.TopNPop();
      }
    }
    else
    {
      current = nullptr;
    }
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }

  return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& iterator) const noexcept
{
  return (current == iterator.current && stk == iterator.stk);
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& iterator) const noexcept
{
  return !(*this == iterator);
}


/* ************************************************************************** */


//BTInOrderIterator
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt)
{
  current = leftMostNode(&bt.Root());
}

//BTInOrderIterator
template <typename Data>
typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::leftMostNode(typename BinaryTree<Data>::Node* node)
{
  if(node->HasLeftChild())
  {
    stk.Push(node);
    return leftMostNode(&node->LeftChild());
  }
  else
  {
    return node;
  }
}

// Copy Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
}

// Move Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  std::swap(stk, iterator.stk);
}

// Copy Assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& iterator)
{
  current = iterator.current;
  stk = iterator.stk;
  return *this;
}

// Move Assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  std::swap(stk, iterator.stk);
  return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept
{
  return (current == nullptr);
}

template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const
{
  if(!Terminated())
  {
    return current->Element();
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++()
{
  if(!Terminated())
  {
    if(current->HasRightChild())
    {
      current = &current->RightChild();
      current = leftMostNode(current);
    }
    else
    {
      if(!stk.Empty())
      {
        current = stk.TopNPop();
      }
      else
      {
        current = nullptr;
      }
    }
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }

  return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& iterator) const noexcept
{
  return ((current == iterator.current) && (stk == iterator.stk));
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& iterator) const noexcept
{
  return !(*this == iterator);
}


/* ************************************************************************** */

//BTBreadthIterator
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt)
{
  if(bt.Size() != 0)
  {
    current = &(bt.Root());
  }
}

// Copy Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator& iterator)
{
  current = iterator.current;
  queue = iterator.queue;
}

// Move Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  queue = std::move(iterator.move);
}

// Copy Assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& iterator)
{
  current = iterator.current;
  queue = iterator.queue;
  return *this;
}

// Move Assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& iterator) noexcept
{
  std::swap(current, iterator.current);
  queue = std::move(iterator.move);
  return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept
{
  return (current == nullptr);
}

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const
{
  if(!Terminated())
  {
    return current->Element();
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++()
{
  if(!Terminated())
  {
    if(current->HasLeftChild()) { queue.Enqueue(&current->LeftChild()); }
    if(current->HasRightChild()) { queue.Enqueue(&current->RightChild()); }
    if(!queue.Empty())
    {
      current = queue.HeadNDequeue();
    }
    else
    {
      current = nullptr;
    }
  }
  else
  {
    throw std::out_of_range("Visit is terminated");
  }

  return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& iterator) const noexcept
{
  return false;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& iterator) const noexcept
{
  return !(*this == iterator);
}


/* ************************************************************************** */

}
