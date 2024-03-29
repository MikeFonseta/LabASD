
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  // ...
unsigned long size = 0;


public:

  // Destructor
  // ~Container() specifiers

  virtual ~Container() = default;


  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  Container& operator=(const Container&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  Container& operator=(const Container&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const Container&) const noexcept = delete;
  bool operator!=(const Container&) const noexcept = delete;

/* ************************************************************************ */

  // Specific member functions

  // type Empty() specifiers; // (concrete function should not throw exceptions)

  // type Size() specifiers; // (concrete function should not throw exceptions)

  // type Clear() specifiers;

virtual inline bool Empty() const noexcept{
  return (size==0);
}

virtual inline unsigned long Size () const noexcept{
  return size;
}

virtual void Clear() = 0;


} ;

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~LinearContainer() specifiers

  virtual ~LinearContainer() = default;


  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  LinearContainer& operator=(const LinearContainer&) = delete;


  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */
  LinearContainer& operator=(LinearContainer&&) noexcept = delete;

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

  bool operator==(const LinearContainer&) const noexcept = delete;
  bool operator!=(const LinearContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Front() specifiers; // (concrete function must throw std::length_error when empty)
  // type Back() specifiers; // (concrete function must throw std::length_error when empty)

  // type operator[](argument) specifiers; // (concrete function must throw std::out_of_range when out of range)

  virtual Data& Front() const = 0;
  virtual Data& Back() const = 0;

  virtual Data& operator[](const unsigned long) const = 0;

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer: virtual public Container{ // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~TestableContainer() specifiers

  virtual ~TestableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  TestableContainer& operator=(const TestableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  TestableContainer& operator=(TestableContainer&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(const TestableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Exists(argument) specifiers; // (concrete function should not throw exceptions)
  virtual bool Exists(const Data&) const noexcept = 0;
};

/* ************************************************************************** */

template <typename Data>
class MappableContainer: virtual public Container { // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~MappableContainer() specifiers

  /* ************************************************************************ */
  virtual ~MappableContainer() = default;

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  MappableContainer& operator=(const MappableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */
  MappableContainer& operator=( MappableContainer&&) noexcept = delete;

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */
  bool operator==(const MappableContainer&) const noexcept = delete;
  bool operator!=(const MappableContainer&) const noexcept = delete;
  // Specific member functions

  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void MapPreOrder(const MapFunctor, void*) = 0;
  virtual void MapPostOrder(const MapFunctor, void*) = 0;

  // type MapPreOrder(arguments) specifiers;
  // type MapPostOrder(arguments) specifiers;



};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer: virtual public TestableContainer<Data> { // Must extend TestableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~FoldableContainer() specifiers

  virtual ~FoldableContainer() = default;


  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.

  FoldableContainer& operator=(const FoldableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  FoldableContainer&& operator=(FoldableContainer&&) noexcept = delete;

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  bool operator==(const FoldableContainer&) const noexcept = delete;
  bool operator!=(const FoldableContainer&) const noexcept = delete;


  // Specific member functions

  typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;

  // type FoldPreOrder(arguments) specifiers;
  // type FoldPostOrder(arguments) specifiers;
  virtual void FoldPreOrder(const FoldFunctor, const void*, void*) const = 0;
  virtual void FoldPostOrder(const FoldFunctor, const void*, void*) const = 0;

  // type Exists(argument) specifiers; // Override TestableContainer member

  virtual bool Exists(const Data&) const noexcept override;


};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data>{ // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */


  // Copy assignment
  InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  InOrderMappableContainer& operator=(InOrderMappableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapInOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer: virtual public FoldableContainer<Data>{ // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~InOrderFoldableContainer() = default;

  /* ************************************************************************ */


  // Copy assignment
  InOrderFoldableContainer& operator=(const InOrderFoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  InOrderFoldableContainer& operator=(InOrderFoldableContainer&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const InOrderFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldInOrder(const FoldFunctor, const void*, void*) const = 0;


};


/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer: virtual public MappableContainer<Data>{ // Must extend MappableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BreadthMappableContainer& operator=(BreadthMappableContainer&&) const noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthMappableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapBreadth(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer: virtual public FoldableContainer<Data>{ // Must extend FoldableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthFoldableContainer& operator=(const BreadthFoldableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BreadthFoldableContainer& operator=(BreadthFoldableContainer&&) const noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthFoldableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldBreadth(const FoldFunctor, const void*, void*) const = 0;

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
