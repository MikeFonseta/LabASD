#include "test.hpp"
#include "../matrix/csr/matrixcsr.hpp"
#include "../matrix/vec/matrixvec.hpp"
#include <iostream>
#include <math.h>

void SelectOption(uint& choice)
{
  choice=0;
  while(choice==0)
  {
    choice=0;
    std::cout << '\n';
    std::cout<<"1) Create and test a structure (MatrixVec or MatrixCSR) "<<std::endl;
    std::cout<<"2) Execute the Prof's test"<<std::endl;
    std::cout<<"3) Exit " << std::endl;
    std::cout<<"Select an option: ";
    std::cin>>choice;
    std::cout << ((choice < 1 || choice > 3) ? "Invalid choice." : "") << '\n';
  }
}

void SelectDataStructure()
{
  uint dataStructure=0;
  while(dataStructure==0 || (dataStructure!=1 && dataStructure!=2))
  {
    dataStructure=0;
    std::cout << '\n';
    std::cout<<"1) Create a random MatrixVec "<<std::endl;
    std::cout<<"2) Create a random MatrixCSR "<<std::endl;
    std::cout<<"Enter a number: ";
    std::cin>>dataStructure;
    std::cout << ((dataStructure != 1 && dataStructure !=2) ? "Invalid choice." : "") << '\n';
  }
  SelectType(dataStructure);
}

void SelectType(const uint& dataStructure)
{
  uint type=0;
  while(type==0 || type > 3)
  {
    type=0;
    std::cout<< ((dataStructure == 1) ? "MatrixVec" : "MatrixCSR") <<" type selection "<<std::endl;
    std::cout<<"1) Int "<<std::endl;
    std::cout<<"2) Float "<<std::endl;
    std::cout<<"3) String "<<std::endl;
    std::cout<< std::endl<<"Enter a number: ";
    std::cin>>type;
    std::cout << ((type==0 || type > 3) ? "Invalid choice." : "") << '\n';
  }
  SelectSize(dataStructure,type);
}

void SelectSize(const uint& dataStructure, const uint& type)
{

  int row = -1;
  int column = -1;
  std::string typeString;
  switch (type) {
    case 1:
    typeString = "Int";
    break;
    case 2:
    typeString = "Float";
    break;
    case 3:
    typeString = "String";
    break;
  }

  while(row < 0)
  {
    row=0;
    std::cout<< ((dataStructure == 1) ? "Enter MatrixVec(" : "MatrixCSR(")<< typeString <<") row size:";
    std::cin>>row;
    std::cout << ((row < 0) ? "Size of row can't be a negative number." : "")<< '\n';
  }
  std::cout << "" << '\n';
  while(column < 0)
  {
    column=0;
    std::cout<< ((dataStructure == 1) ? "Enter MatrixVec(" : "MatrixCSR(")<< typeString <<") column size:";
    std::cin>>column;
    std::cout << ((row < 0) ? "Size of column can't be a negative number." : "")<< '\n';
  }

  CreateStructure(dataStructure,type,row,column);
}

//Fold functions for menu
template <typename Data>
void FoldFunctionMenu(const Data&, const void*, void*) {}

template<>
void FoldFunctionMenu<int>(const int& dat, const void* par, void* acc) {
  if(dat < *((int*) par))
  {
    *((int*) acc) *= dat;
  }
}

template<>
void FoldFunctionMenu<float>(const float& dat, const void* par, void* acc) {
  if(dat > *((float*) par))
  {
    *((float*) acc) += dat;
  }
}

template<>
void FoldFunctionMenu<std::string>(const std::string& word, const void* par, void* acc){
  if(word.length() <= *((int*) par))
  {
    *((std::string*) acc) += word;
  }
}

//Map functions for menu
template <typename Data>
void MapPrint(const Data& dat, void* _) {
  std::cout << dat << " ";
}

template <typename Data>
void MapFunctionMenu(Data& dat, void* _) {}

template<>
void MapFunctionMenu(int& dat, void* _) {
  dat = 2*dat;
}

template<>
void MapFunctionMenu<float>(float& dat, void* _) {
  dat = pow(-dat, 3);
}

template<>
void MapFunctionMenu<std::string>(std::string& word, void* par) {
  word = *((std::string*) par) + word;
}

template<typename Data>
void MenuMatrix(lasd::Matrix<Data>& matrix, const uint& type)
{
  uint choice=0;
  std::string typeString = "";
  std::string fourthSelection = "4) ";
  std::string fifthSelection = "5) ";
  switch (type) {
    case 1:
    typeString = "Int";
    fourthSelection = "4) Computes the product for elements less than n";
    fifthSelection = "5) Apply the 2n function to all elements";
    break;
    case 2:
    typeString = "Float";
    fourthSelection = "4) Sum for elements greater than n";
    fifthSelection = "5) Apply the -n^3 function to all elements";
    break;
    case 3:
    typeString = "String";
    fourthSelection = "4) Concatenation of strings with length less than or equal to n";
    fifthSelection = "5) Head concatenation of a specific string str";
    break;
  }

  while(choice != 6)
  {
    std::cout << "===================== Matrix("<< typeString << ") Menu ======= Row: "<< matrix.RowNumber() << " Column: "<< matrix.ColumnNumber() << '\n' << '\n';
    std::cout << "1) Print the matrix (PreOrder / PostOrder)" << '\n';
    std::cout << "2) Access / Modify a cell "<< '\n';
    std::cout << "3) Check if a value exists" << '\n';
    std::cout << fourthSelection << '\n';
    std::cout << fifthSelection << '\n';
    std::cout << "6) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      {
        uint choice = 0;
        while(choice < 1 || choice > 2)
        {
          std::cout << "1) PreOrder" << '\n';
          std::cout << "2) PostOrder" << '\n';
          std::cout << "Select PreOrder or PostOrder: ";
          std::cin >> choice;
          std::cout << ((choice != 1 && choice != 2 ) ? "Invalid option" : "") << '\n';
        }
        switch (choice)
        {
          case 1:
            std::cout << "Matrix (PreOrder): ";
            matrix.MapPreOrder(&MapPrint<Data>, 0);
            std::cout << "" << '\n';
            break;
          case 2:
            std::cout << "Matrix (PreOrder): ";
            matrix.MapPostOrder(&MapPrint<Data>, 0);
            std::cout << "" << '\n';
            break;
        }
      }
      break;
      case 2:
      {
        ulong row,column;
        std::cout << "Enter row: ";
        std::cin >> row;
        std::cout << "Enter column: ";
        std::cin >> column;
        uint choice=0;
        try
        {
          Data value = matrix(row,column);
          while(choice == 0 || choice > 2)
          {
            std::cout << "Value of cell ("<< row << ","<< column <<") :"<< value << '\n';
            std::cout << "1) Modify the cell value" << '\n';
            std::cout << "2) Go back to the main menu" << '\n';
            std::cout << "Select an option: ";
            std::cin >> choice;
          }
          if(choice == 1)
          {
            Data newValue;
            std::cout << "Insert the new value: ";
            std::cin >> newValue;
            matrix(row,column) = newValue;
          }
        }
        catch (const std::exception& ex)
        {
          std::cout << ex.what() << '\n';
        }
      }
      break;
      case 3:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        std::cout << value <<  ((matrix.Exists(value)==0) ? " doesn't": "") << " exists" << '\n';
      }
      break;
      case 4:
      {
        switch (type){
          case 1:
          {
            int value;
            int acc=1;
            std::cout << "Enter n value: ";
            std::cin >> value;
            matrix.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 2:
          {
            float value;
            float acc=0;
            std::cout << "Enter n value: ";
            std::cin >> value;
            matrix.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 3:
          {
            int value;
            std::string acc="";
            std::cout << "Enter n value: ";
            std::cin >> value;
            matrix.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
        }
      }
      break;
      case 5:
      {
        switch (type){
          case 1:
          matrix.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 2:
          matrix.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 3:
          Data stringToAdd;
          std::cout << "Insert the str: ";
          std::cin >> stringToAdd;
          matrix.MapPreOrder(&MapFunctionMenu<Data>, &stringToAdd);
          std::cout << "Done! " << '\n';
          break;
        }
      }
    }
  }
}


void CreateStructure(const unsigned int& dataStructure, const unsigned int& type, const unsigned int& row, const unsigned int& column)
{
  if(dataStructure==1)
  {
    if(type==1)
    {
      lasd::MatrixVec<int> matrix(row,column);
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,row*column);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          matrix(index, index_) = dist(gen);
        }
      }
      MenuMatrix(matrix,type);
    }
    if(type==2)
    {
      lasd::MatrixVec<float> matrix(row,column);
      int range=row*column;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<float> dist((-range),range);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          float value = (int)(dist(gen) * 100 + .5);
          matrix(index, index_) = (value/100);
        }
      }
      MenuMatrix(matrix,type);
    }
    if(type==3)
    {
      lasd::MatrixVec<std::string> matrix(row,column);
      std::string CHARACTERS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,62);
      std::uniform_int_distribution<int> dist1(0,row*column);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          int wordLength = dist1(gen);
          while(wordLength > 0)
          {
            matrix(index, index_) += CHARACTERS[dist(gen)];
            wordLength--;
          }
        }
      }
      MenuMatrix(matrix,type);
    }
  }
  else
  {
    if(type==1)
    {
      lasd::MatrixCSR<int> matrix(row,column);
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,row*column);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          matrix(index, index_) = dist(gen);
        }
      }
      MenuMatrix(matrix,type);
    }
    if(type==2)
    {
      lasd::MatrixCSR<float> matrix(row,column);
      int range=row*column;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<float> dist((-range),range);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          float value = (int)(dist(gen) * 100 + .5);
          matrix(index, index_) = (value/100);
        }
      }
      MenuMatrix(matrix,type);
    }
    if(type==3)
    {
      lasd::MatrixCSR<std::string> matrix(row,column);
      std::string CHARACTERS = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,62);
      std::uniform_int_distribution<int> dist1(0,row*column);
      for(ulong index=0; index < row; ++index)
      {
        for(ulong index_=0; index_ < column; ++index_)
        {
          int wordLength = dist1(gen);
          while(wordLength > 0)
          {
            matrix(index, index_) += CHARACTERS[dist(gen)];
            wordLength--;
          }
        }
      }
      MenuMatrix(matrix,type);
    }
  }
}
