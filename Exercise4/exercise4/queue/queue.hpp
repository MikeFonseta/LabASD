#ifndef QUEUE_HPP
#define QUEUE_HPP


/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : virtual public Container{ // Must extend Container

private:


protected:


public:

  // Destructor
  ~Queue()=default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types should not be possible.
  Queue& operator=(const Queue&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types should not be possible.
  Queue& operator=(Queue&&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.
  bool operator==(const Queue&) const noexcept = delete;
  bool operator!=(const Queue&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  virtual void Enqueue(const Data&) = 0; // Copy of the value
  virtual void Enqueue(Data&&) noexcept = 0; // Move of the value
  virtual Data& Head() const = 0; // (concrete function must throw std::length_error when empty)
  virtual void Dequeue() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data HeadNDequeue() = 0; // (concrete function must throw std::length_error when empty)


};

/* ************************************************************************** */



}

#endif
