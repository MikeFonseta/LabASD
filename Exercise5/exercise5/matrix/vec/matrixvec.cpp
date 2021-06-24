
namespace lasd {

/* ************************************************************************** */

// // Default constructor
// template <typename Data>
// MatrixVec<Data>::MatrixVec()
// {
//   row = 0;
//   column = 0;
//   vec.Resize(1);
// }

//Specific constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(const ulong row_, const ulong column_)
{
  row = row_;
  column = column_;
  vec.Resize(row*column);
}

//Copy constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(const MatrixVec<Data>& matrix)
{
  row = matrix.row;
  column = matrix.column;
  vec = matrix.vec;
}

//Move constructor
template <typename Data>
MatrixVec<Data>::MatrixVec(MatrixVec<Data>&& matrix) noexcept
{
  std::swap(row, matrix.row);
  std::swap(column, matrix.column);
  vec = std::move(matrix.vec);
}

//Copy assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(const MatrixVec<Data>& matrix)
{
  row = matrix.row;
  column = matrix.column;
  vec = matrix.vec;
  return *this;
}

//Move assignment
template <typename Data>
MatrixVec<Data>& MatrixVec<Data>::operator=(MatrixVec<Data>&& matrix) noexcept
{
  std::swap(row, matrix.row);
  std::swap(column, matrix.column);
  vec = std::move(matrix.vec);
  return *this;
}

//Destructor
template <typename Data>
MatrixVec<Data>::~MatrixVec()
{
  Clear();
}

//Clear
template <typename Data>
void MatrixVec<Data>::Clear()
{
  if(row*column > 0)
  {
    vec.Clear();
    row = 0;
    column = 0;
  }
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool MatrixVec<Data>::operator==(const MatrixVec<Data>& matrix) const noexcept
{
  if(row == matrix.row && column == matrix.column)
  {
    if(vec.Empty() && matrix.vec.Empty()) { return true; }

    return (vec == matrix.vec);
  }
  else
  {
    return false;
  }
}

template<typename Data>
inline bool MatrixVec<Data>::operator!=(const MatrixVec<Data>& matrix) const noexcept
{
  return !(*this == matrix);
}

/* ************************************************************************** */

//RowResize
template <typename Data>
void MatrixVec<Data>::RowResize(const ulong newRowSize)
{
  vec.Resize(newRowSize*column);
  row = newRowSize;
}

//ColumnResize
template <typename Data>
void MatrixVec<Data>::ColumnResize(const ulong newColumnSize)
{
  if(newColumnSize == 0)
  {
    column = 0;
    Clear();
  }
  else if(newColumnSize != column)
  {
    Vector<Data> tmp(row*newColumnSize);
    if(newColumnSize > column)
    {
      ulong index_ = 0;
      ulong countColumn = 0;
      for(ulong index = 0; index < row*column; index++)
      {
        std::swap(vec[index], tmp[index_]);
        countColumn++;

        if(countColumn == column)
        {
          countColumn = 0;
          index_ = index_ + (newColumnSize-column);
          index_++;
        }
        else
        {
          index_++;
        }
      }
    }
    if(newColumnSize < column)
    {
      ulong index_ = 0;
      ulong countColumn = 0;
      for(ulong index = 0; index < row*newColumnSize; index++)
      {
        std::swap(vec[index_], tmp[index]);
        countColumn++;

        if(countColumn == newColumnSize)
        {
          countColumn = 0;
          index_ = index_ + (column-newColumnSize);
          index_++;
        }
        else
        {
          index_++;
        }
      }
    }
    vec = std::move(tmp);
  }
  column = newColumnSize;
}

//ExistsCell
template <typename Data>
bool MatrixVec<Data>::ExistsCell(const ulong row_, const ulong column_) const noexcept
{
  if(row == 0 || column == 0)
  {
    return false;
  }
  if(row_*column + column_ > row*column)
  {
    return false;
  }
  return true;
}

//operator()
template <typename Data>
Data& MatrixVec<Data>::operator()(const ulong row_,const ulong column_)
{
  return const_cast<Data&>(static_cast<const MatrixVec<Data> *>(this)->operator()(row_,column_));
}

//const operator()
template <typename Data>
const Data& MatrixVec<Data>::operator()(const ulong row_, const ulong column_) const
{
  if(ExistsCell(row_,column_))
  {
    return vec[row_*column + column_];
  }
  else
  {
    throw std::out_of_range("Access at row: " + std::to_string(row_) + " and column: " + std::to_string(column_) + ". Matrix row: " + std::to_string(row) + " and column: " + std::to_string(column));
  }
}

/* ************************************************************************** */

template <typename Data>
void MatrixVec<Data>::MapPreOrder(const MapFunctor fun, void* par)
{
  vec.MapPreOrder(fun,par);
}

template <typename Data>
void MatrixVec<Data>::MapPostOrder(const MapFunctor fun, void* par)
{
  vec.MapPostOrder(fun,par);
}

template <typename Data>
void MatrixVec<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  vec.FoldPreOrder(fun,par,acc);
}

template <typename Data>
void MatrixVec<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  vec.FoldPostOrder(fun,par,acc);
}

}
