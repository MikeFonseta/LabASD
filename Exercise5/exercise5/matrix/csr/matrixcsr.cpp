
namespace lasd {

/* ************************************************************************** */

// // Default constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR()
{
  row = 0;
  column = 0;
  rowVector.Resize(row+1);
  head = nullptr;
  rowVector[0] = &head;
}

//Specific constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const ulong row_, const ulong column_)
{
  row = row_;
  column = column_;
  head = nullptr;
  rowVector.Resize(row+1);
  for(ulong index = 0; index < rowVector.Size(); index++)
  {
    rowVector[index] = &head;
  }
}

//Copy constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data>& matrix): MatrixCSR(matrix.row, matrix.column)
{
  for(ulong index = 0; index < row; index++)
  {
    for(Node** pointer = matrix.rowVector[index]; pointer != matrix.rowVector[index+1]; pointer = &((*pointer)->next))
    {
      Node& node = **pointer;
      (*this)(index, node.data.second) = node.data.first;
    }
  }
}

//Move constructor
template <typename Data>
MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data>&& matrix) noexcept
{
  std::swap(head, matrix.head);
  std::swap(row, matrix.row);
  std::swap(size, matrix.size);
  std::swap(column, matrix.column);
  std::swap(rowVector, matrix.rowVector);
}

//Copy assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(const MatrixCSR<Data>& matrix)
{
  MatrixCSR *newMatrix = new MatrixCSR(matrix);
  std::swap(*this, *newMatrix);
  delete newMatrix;
  return *this;
}

//Move assignment
template <typename Data>
MatrixCSR<Data>& MatrixCSR<Data>::operator=(MatrixCSR<Data>&& matrix) noexcept
{
  std::swap(head, matrix.head);
  std::swap(row, matrix.row);
  std::swap(size, matrix.size);
  std::swap(column, matrix.column);
  std::swap(rowVector, matrix.rowVector);
  for (ulong index = 0; index < size && rowVector[index] == &matrix.head; index++) { rowVector[index] = &head; }
  for (ulong index = 0; index < matrix.size && matrix.rowVector[index] == &head; index++) { matrix.rowVector[index] = &matrix.head; }
  return *this;
}

//Destructor
template <typename Data>
MatrixCSR<Data>::~MatrixCSR()
{
  Clear();
}

//Clear
template <typename Data>
void MatrixCSR<Data>::Clear()
{
  if(row > 0 || column > 0)
  {
    List<std::pair<Data,ulong>>::Clear();
    row = 0;
    column = 0;
    rowVector.Resize(row+1);
    rowVector[0] = &head;
  }
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool MatrixCSR<Data>::operator==(const MatrixCSR<Data>& matrix) const noexcept
{
  if(row == matrix.row && column == matrix.column && rowVector.Size() == matrix.rowVector.Size())
  {
    for(ulong index = 0; index < row; index++)
    {
      Node** m1 = rowVector[index];
      Node** m1next = rowVector[index+1];
      Node** m2 = matrix.rowVector[index];
      Node** m2next = matrix.rowVector[index+1];

      while(m1 != m1next && m2 != m2next)
      {
        if(((*m1)->data.first != (*m2)->data.first &&
        (*m1)->data.second == (*m2)->data.second) || ((*m1)->data.first == (*m2)->data.first && (*m1)->data.second != (*m2)->data.second))
        {
          return false;
        }
        m1 = &((*m1)->next);
        m2 = &((*m2)->next);
      }
      if((m1 != m1next && m2 == m2next) || (m1 == m1next && m2 !=m2next)) { return false; }
    }
    return true;
  }
  return false;
}

template<typename Data>
inline bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data>& matrix) const noexcept
{
  return !(*this == matrix);
}

/* ************************************************************************** */

//RowResize
template <typename Data>
void MatrixCSR<Data>::RowResize(const ulong newRowSize)
{
  if(newRowSize == 0)
  {
    ulong actualColumn = column;
    Clear();
    column = actualColumn;
  }
  else if(newRowSize < row)
  {
    Node* tmp = *rowVector[newRowSize];
    DeleteNextRow(tmp);
    rowVector.Resize(newRowSize+1);
    *rowVector[newRowSize] = nullptr;
    row = newRowSize;
  }
  else if(newRowSize > row)
  {
    rowVector.Resize(newRowSize+1);
    for(ulong index = row; index<newRowSize; index++)
    {
      rowVector[index+1] = rowVector[index];
    }
    row = newRowSize;
  }
}

//ColumnResize
template <typename Data>
void MatrixCSR<Data>::ColumnResize(const ulong newColumnSize)
{
  if(newColumnSize == 0)
  {
    ulong actualrow = row;
    Clear();
    row = actualrow;
  }
  else if(newColumnSize < column)
  {
    //Start from second row
    ulong index = 1;
    Node** pointer = &head;

    while(index <= row)
    {
      Node* node;
      Node** end = rowVector[index];
      //While we goot good column
      while(pointer != end && (*pointer)->data.second < newColumnSize)
      {
        node = *pointer;
        pointer = &(node->next);
      }
      //If we reached the end of the next line
      if(pointer != end)
      {
        Node*tmp = *pointer;
        *pointer = *end;
        *end = nullptr;
        //Delete the nodes
        DeleteNext(tmp, newColumnSize);
      }
      //Set the corret addres for the line till the next
      for(;index <= row && rowVector[index] == end; index++)
      {
        rowVector[index] = &(node->next);
      }
    }
  }
  column = newColumnSize;
}

template <typename Data>
void MatrixCSR<Data>::DeleteNext(Node* node,const  ulong nColumn)
{
  if(node != nullptr)
  {
    if(node->data.second >= nColumn)
    {
      DeleteNext(node->next, nColumn);
      size--;
      delete node;
    }
  }
}

template <typename Data>
void MatrixCSR<Data>::DeleteNextRow(Node* node)
{
  if(node != nullptr)
  {
    DeleteNextRow(node->next);
    size--;
    std::cout << "Elimino: "<< node->data.first << '\n';
    delete node;
  }
}

//ExistsCell
template <typename Data>
bool MatrixCSR<Data>::ExistsCell(const ulong row_, const ulong column_) const noexcept
{
  if(row_ < row && column_ < column)
  {
    Node** pointer = rowVector[row_];
    while(pointer != rowVector[row_+1])
    {
      Node& node = **pointer;
      if(node.data.second == column_)
      {
        return true;
      }
      pointer = &(node.next);
    }
    return false;
  }
  return false;
}

//operator()
template <typename Data>
Data& MatrixCSR<Data>::operator()(const ulong row_, const ulong column_)
{
  if(row_ < row && column_ < column)
  {
    Node **node = rowVector[row_];
    while (node!=rowVector[row_+1] && (*node)->data.second<=column_)
    {
      //If column is found return the data
      if((**node).data.second==column_) { return (**node).data.first; }
      node = &((**node).next);
    }

    Node *tmp = new Node();
    size++;
    tmp->data.second = column_;
    tmp->next = &(**node);
    *node = tmp;
    //Insert on empty line ot at the end of the line
    if(node == rowVector[row_+1])
    {
      ulong index = 0;
      Node **nodeNext = rowVector[row_+1];
      rowVector[row_+1] = &(tmp->next);
      while(row_+index+2 < row+1 && nodeNext == rowVector[row_+index+ 2])
      {
        rowVector[row_+index+2] = &(tmp->next);
        index++;
      }
    }
    return tmp->data.first;
  }
  else
  {
    throw std::out_of_range("Access at row: " + std::to_string(row_) + " and column: " + std::to_string(column_) + ". Matrix row: " + std::to_string(row) + " and column: " + std::to_string(column));
  }
}

//const operator()
template <typename Data>
const Data& MatrixCSR<Data>::operator()(const ulong row_, const ulong column_) const
{
  if(row_ < row && column_ < column)
  {
    Node** pointer = rowVector[row_];
    while(pointer != rowVector[row_ + 1])
    {
      Node& node = **pointer;
      if(node.data.second == column_)
      {
        return node.data.first;
      }
      pointer = &(node.next);
    }

    throw std::length_error("Cell (" + std::to_string(row_) + "," + std::to_string(column_) + ") not present"  );
  }
  else
  {
    throw std::out_of_range("Access at (" + std::to_string(row_) + "," + std::to_string(column_) + ") . Matrix row: " + std::to_string(row) + " and column: " + std::to_string(column));
  }
}

/* ************************************************************************** */

template <typename Data>
void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void* par)
{
  Node* tmphead = head;
  while(tmphead != nullptr) { fun(tmphead->data.first, par); tmphead = tmphead->next; }
}

template <typename Data>
void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void* par)
{
  AuxFunctionForMapPostOrder(head,fun,par);
}

template <typename Data>
void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  Node* tmphead = head;
  while(tmphead != nullptr) { fun(tmphead->data.first, par, acc); tmphead = tmphead->next; }
}

template <typename Data>
void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const
{
  AuxFunctionForFoldPostOrder(head,fun,par,acc);
}

template <typename Data>
void MatrixCSR<Data>::AuxFunctionForMapPostOrder(Node* node, const MapFunctor fun, void* par)
{
  if (node != nullptr)
  {
    AuxFunctionForMapPostOrder(node->next, fun, par);
    fun(node->data.first, par);
  }
}

template <typename Data>
void MatrixCSR<Data>::AuxFunctionForFoldPostOrder(Node* node, const FoldFunctor fun, const void* par, void* acc) const
{
  if (node != nullptr)
  {
    AuxFunctionForFoldPostOrder(node->next, fun, par,acc);
    fun(node->data.first, par,acc);
  }
}

/* ************************************************************************** */

}
