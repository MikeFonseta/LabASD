
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public BinaryTree<Data> { // Must extend BinaryTree<Data>

private:

  // ...

protected:


  struct NodeLnk: virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

  protected:

    // Data data;
    // NodeLnk* Left=nullptr;
    // NodeLnk* Right=nullptr;

  public:

    Data data;
    NodeLnk* Left=nullptr;
    NodeLnk* Right=nullptr;

    NodeLnk() = default;
    NodeLnk(const Data&);
    ~NodeLnk();
    Data& Element() noexcept override;
    const Data& Element() const noexcept override;
    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;
    NodeLnk& LeftChild() const override;
    NodeLnk& RightChild() const override;

    friend class BinaryTreeLnk<Data>;
  };

  using BinaryTree<Data>::size;
  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;
  NodeLnk* createBinaryTreeLnk(ulong, NodeLnk*, const LinearContainer<Data>&);
  NodeLnk* Add(NodeLnk*);
  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator==(const BinaryTreeLnk&) const noexcept;
  // inline bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  typename BinaryTreeLnk<Data>::NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
