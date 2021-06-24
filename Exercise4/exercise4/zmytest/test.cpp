#include "test.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"
#include <iostream>
#include <math.h>

void SelectOption(uint& choice)
{
  choice=0;
  while(choice==0)
  {
    choice=0;
    std::cout << '\n';
    std::cout<<"1) Create and test a structure (Vector or List) "<<std::endl;
    std::cout<<"2) Create and test a structure (Stack or Queue) "<<std::endl;
    std::cout<<"3) Create and test a structure (BinaryTree) "<<std::endl;
    std::cout<<"4) Create and test a structure (BinarySearchTree) "<<std::endl;
    std::cout<<"5) Execute the Prof's test"<<std::endl;
    std::cout<<"6) Exit " << std::endl;
    std::cout<<"Select an option: ";
    std::cin>>choice;
    std::cout << ((choice < 1 || choice > 6) ? "Invalid choice." : "") << '\n';
  }
}

void SelectDataStructure(const uint& choice)
{
  uint dataStructure=0;
  while(dataStructure==0 || (dataStructure!=1 && dataStructure!=2))
  {
    dataStructure=0;
    std::cout << '\n';
    std::cout<<"1) Create a random " << ((choice==1) ? "Vector" : "Stack") << std::endl;
    std::cout<<"2) Create a random " << ((choice==1) ? "List" : "Queue") << std::endl;
    std::cout<<"Enter a number: ";
    std::cin>>dataStructure;
    std::cout << ((dataStructure != 1 && dataStructure !=2) ? "Invalid choice." : "") << '\n';
  }
  SelectType(choice,dataStructure);
}

void SelectType(const uint& choice, const uint& dataStructure)
{
  uint type=0;
  while(type==0 || type > 4)
  {
    type=0;
    switch (choice) {
      case 1:
      std::cout<< ((dataStructure == 1) ? "Vector" : "List") <<" type selection "<<std::endl;
      break;
      case 2:
      std::cout<< ((dataStructure == 1) ? "Stack" : "Queue") <<" type selection "<<std::endl;
      case 3:
      std::cout<< "BinaryTree type selection "<<std::endl;
      break;
      case 4:
      std::cout << "BinarySearchTree type selection " << '\n';
      break;
    }
    std::cout<<"1) Int "<<std::endl;
    std::cout<<"2) Float "<<std::endl;
    std::cout<<"3) Double "<<std::endl;
    std::cout<<"4) String "<<std::endl;
    std::cout<< std::endl<<"Enter a number: ";
    std::cin>>type;
    std::cout << ((type==0 || type > 4) ? "Invalid choice." : "") << '\n';
  }
  SelectSize(choice,dataStructure,type);
}

void SelectSize(const uint& choice, const uint& dataStructure, const uint& type)
{

  int size= -1;
  std::string typeString,structureString;
  switch (type) {
    case 1:
    typeString = "Int";
    break;
    case 2:
    typeString = "Float";
    break;
    case 3:
    typeString = "Double";
    break;
    case 4:
    typeString = "String";
    break;
  }

  while(size < 0)
  {
    size=0;
    switch (choice) {
      case 1:
      std::cout << ((dataStructure == 1) ? "Enter Vector(" : "Enter List(") << typeString << ") size: ";
      break;
      case 2:
      std::cout << ((dataStructure == 1) ? "Enter Stack(" : "Enter Queue(") << typeString << ") size: ";
      case 3:
      std::cout << "Enter BinaryTree " << typeString << " size: ";
      break;
      case 4:
      std::cout << "Enter BinarySearchTree " << typeString << " size: ";
      break;
    }
    std::cin>>size;
    std::cout << ((size < 0) ? "Size can't be a negative number." : "") << '\n';
  }
  if(choice==1)
  {
    CreateVectorOrList(dataStructure,type,size);
  }
  else if(choice == 3)
  {
    SelectImplementation(dataStructure,type,size);
  }
  else if(choice == 4)
  {
    CreateBinarySearchTree(type,size);
  }
}

//Fold functions for menu
template <typename Data>
void FoldFunctionMenu(const Data&, const void*, void*) {}
template <typename Data>
void FoldFunctionBtMenu(const Data&, const void*, void*) {}

template<>
void FoldFunctionMenu<int>(const int& dat, const void* par, void* acc) {
  if(dat < *((int*) par))
  {
    *((int*) acc) += dat;
  }
}

template<>
void FoldFunctionBtMenu<int>(const int& dat, const void* par, void* acc) {
  if(dat < *((int*) par))
  {
    *((int*) acc) *= dat;
  }
}

template<>
void FoldFunctionMenu<float>(const float& dat, const void* par, void* acc) {
  if(dat > *((float*) par))
  {
    *((float*) acc) *= dat;
  }
}

template<>
void FoldFunctionBtMenu<float>(const float& dat, const void* par, void* acc) {
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

template<>
void FoldFunctionBtMenu<std::string>(const std::string& word, const void* par, void* acc){
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
template <typename Data>
void MapFunctionBtMenu(Data& dat, void* _) {}

template<>
void MapFunctionMenu(int& dat, void* _) {
  dat = 2*dat;
}

template<>
void MapFunctionBtMenu(int& dat, void* _) {
  dat = 3*dat;
}

template<>
void MapFunctionMenu<float>(float& dat, void* _) {
  dat = pow(dat, 2);
}

template<>
void MapFunctionBtMenu(float& dat, void* _) {
  dat = pow(dat, 3);
}

template<>
void MapFunctionMenu<std::string>(std::string& word, void* _) {
  for(uint index = 0; index<word.length(); ++index)
  {
    word[index] = toupper(word[index]);
  }
}

template<>
void MapFunctionBtMenu<std::string>(std::string& word, void* par) {
  word = *((std::string*) par) + word;
}

template<typename Data>
void MenuVector(lasd::Vector<Data>& vec, const uint& type)
{
  uint choice=0;
  std::string typeString = "";
  std::string fourthSelection = "4) ";
  std::string fifthSelection = "5) ";
  switch (type) {
    case 1:
    typeString = "Int";
    fourthSelection = "4) Computes the sum for elements less than n";
    fifthSelection = "5) Apply the 2n function to all elements";
    break;
    case 2:
    typeString = "Float";
    fourthSelection = "4) Product for elements greater than n";
    fifthSelection = "5) Apply the n^2 function to all elements";
    break;
    case 3:
    typeString = "Double";
    fourthSelection = "4) Not defined";
    fifthSelection = "5) Not defined";
    break;
    case 4:
    typeString = "String";
    fourthSelection = "4) Concatenation of strings with length less than or equal to n";
    fifthSelection = "5) Apply the uppercase function to all elements";
    break;
  }

  while(choice != 6)
  {
    std::cout << "===================== Vector("<< typeString << ") Menu =====================" << '\n' << '\n';
    std::cout << "1) Print the first, last or a specific element (specific index)" << '\n';
    std::cout << "2) Print the vector" << '\n';
    std::cout << "3) Check if a value exists" << '\n';
    std::cout << fourthSelection << '\n';
    std::cout << fifthSelection << '\n';
    std::cout << "6) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      {
        uint choice_=0;
        while(choice_==0)
        {
          std::cout << "1) Print the first element" << '\n';
          std::cout << "2) Print the last element" << '\n';
          std::cout << "3) Print a specific element (specific index)" << '\n' << '\n';
          std::cout << "Select an option: ";
          std::cin>>choice_;

          switch (choice_) {
            case 1:
            std::cout << "First element: " << vec.Front() << '\n';
            break;
            case 2:
            std::cout << "Last element: " << vec.Back() << '\n';
            break;
            case 3:
            {
              int index_= -1;
              while(index_ == -1)
              {
                std::cout << "Enter an index: ";
                std::cin >> index_;
                if(index_ >= 0 && index_<vec.Size())
                {
                  std::cout << "Element at index "<< index_ << ": " << vec[index_] << '\n';
                }else
                {
                  std::cout << "Invalid index." << '\n';
                }
              }
            }
          }
        }
      }
      break;

      case 2:{
      std::cout << "Size Vector("<< typeString << ") : " << vec.Size() << '\n';
      vec.MapPreOrder(&MapPrint<Data>, 0);
      std::cout << '\n';
      break;
}
      case 3:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        std::cout << value <<  ((vec.Exists(value)==0) ? " doesn't": "") << " exists" << '\n';
      }
      break;
      case 4:
      {
        switch (type){
          case 1:
          {
            int value;
            int acc=0;
            std::cout << "Enter n value: ";
            std::cin >> value;
            vec.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 2:
          {
            float value;
            float acc=1;
            std::cout << "Enter n value: ";
            std::cin >> value;
            vec.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            int value;
            std::string acc="";
            std::cout << "Enter n value: ";
            std::cin >> value;
            vec.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          break;
        }
      }
      break;
      case 5:
      {
        switch (type){
          case 1:
          vec.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 2:
          vec.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          vec.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
        }
      }
    }
  }
}

template<typename Data>
void MenuList(lasd::List<Data>& list, const uint& type)
{
  uint choice=0;
  std::string typeString = "";
  std::string fourthSelection = "4) ";
  std::string fifthSelection = "5) ";
  switch (type) {
    case 1:
    typeString = "Int";
    fourthSelection = "4) Computes the sum for elements less than n";
    fifthSelection = "5) Apply the 2n function to all elements";
    break;
    case 2:
    typeString = "Float";
    fourthSelection = "4) Product for elements greater than n";
    fifthSelection = "5) Apply the n^2 function to all elements";
    break;
    case 3:
    typeString = "Double";
    fourthSelection = "4) Not defined";
    fifthSelection = "5) Not defined";
    break;
    case 4:
    typeString = "String";
    fourthSelection = "4) Concatenation of strings with length less than or equal to n";
    fifthSelection = "5) Apply the uppercase function to all elements";
    break;
  }

  while(choice != 6)
  {
    std::cout << "===================== List("<< typeString << ") Menu =====================" << '\n' << '\n';
    std::cout << "1) Print the first, last or a specific element (specific index)" << '\n';
    std::cout << "2) Print the list" << '\n';
    std::cout << "3) Check if a value exists" << '\n';
    std::cout << fourthSelection << '\n';
    std::cout << fifthSelection << '\n';
    std::cout << "6) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      {
        uint choice_=0;
        while(choice_==0)
        {
          std::cout << "1) Print the first element" << '\n';
          std::cout << "2) Print the last element" << '\n';
          std::cout << "3) Print a specific element (specific index)" << '\n' << '\n';
          std::cout << "Select an option: ";
          std::cin>>choice_;

          switch (choice_) {
            case 1:
            std::cout << "First element: " << list.Front() << '\n';
            break;
            case 2:
            std::cout << "Last element: " << list.Back() << '\n';
            break;
            case 3:
            {
              int index_= -1;
              while(index_ == -1)
              {
                std::cout << "Enter an index: ";
                std::cin >> index_;
                if(index_ >= 0 && index_<list.Size())
                {
                  std::cout << "Element at index "<< index_ << ": " << list[index_] << '\n';
                }else
                {
                  std::cout << "Invalid index." << '\n';
                }
              }
            }
          }
        }
      }
      break;

      case 2:
      std::cout << "Size List("<< typeString << ") : " << list.Size() << '\n';
      list.MapPreOrder(&MapPrint<Data>, 0);
      std::cout << '\n';
      break;

      case 3:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        std::cout << value <<  ((list.Exists(value)==0) ? " doesn't": "") << " exists" << '\n';
      }
      break;
      case 4:
      {
        switch (type){
          case 1:
          {
            int value;
            int acc=0;
            std::cout << "Enter n value: ";
            std::cin >> value;
            list.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 2:
          {
            float value;
            float acc=1;
            std::cout << "Enter n value: ";
            std::cin >> value;
            list.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            int value;
            std::string acc="";
            std::cout << "Enter n value: ";
            std::cin >> value;
            list.FoldPreOrder(&FoldFunctionMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          break;
        }
      }
      break;
      case 5:
      {
        switch (type){
          case 1:
          list.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 2:
          list.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          list.MapPreOrder(&MapFunctionMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
        }
      }
    }
  }
}

template<typename Data>
void MenuStack(lasd::Stack<Data>& stack)
{
    uint choice = 0;

    while(choice != 7)
    {
      std::cout << "===================== Stack Menu =====" << " Size: "<< stack.Size() <<" ==========" << '\n' << '\n';
      std::cout << "1) Push" << '\n';
      std::cout << "2) Pop" << '\n';
      std::cout << "3) Front" << '\n';
      std::cout << "4) PushNPop" << '\n';
      std::cout << "5) Check if stack it's empty" << '\n';
      std::cout << "6) Clear the stack" << '\n';
      std::cout << "7) Go back to Menu" << '\n';
      std::cout << "Select an option: ";
      std::cin>>choice;

      switch (choice) {
        case 1:
        {
        Data valueToAdd;
        std::cout << "Insert the value: ";
        std::cin>>valueToAdd;
        stack.Push(valueToAdd);
        }
        break;
        case 2:
        stack.Pop();
        break;
        case 3:
        std::cout << "The head is: "<< stack.Top()<< '\n';
        break;
        case 4:
        std::cout << "The head before TopNPop is: "<< stack.TopNPop()<< '\n';
        break;
        case 5:
        std::cout << "The stack is "<< ((stack.Empty()==0) ? "not " : "") << "empty"<< '\n';
        break;
        case 6:
        stack.Clear();
        break;
      }
    }
}

template<typename Data>
void MenuQueue(lasd::Queue<Data>& queue)
{
  uint choice = 0;

  while(choice != 7)
  {
    std::cout << "===================== Queue Menu =====" << " Size: "<< queue.Size() <<" ==========" << '\n' << '\n';
    std::cout << "1) Enqueue" << '\n';
    std::cout << "2) Dequeue" << '\n';
    std::cout << "3) Head" << '\n';
    std::cout << "4) HeadNDequeue" << '\n';
    std::cout << "5) Check if queue it's empty" << '\n';
    std::cout << "6) Clear the queue" << '\n';
    std::cout << "7) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      {
      Data valueToAdd;
      std::cout << "Insert the value: ";
      std::cin>>valueToAdd;
      queue.Enqueue(valueToAdd);
      }
      break;
      case 2:
      queue.Dequeue();
      break;
      case 3:
      std::cout << "The head is: "<< queue.Head()<< '\n';
      break;
      case 4:
      std::cout << "The head before Dequeue is: "<< queue.HeadNDequeue()<< '\n';
      break;
      case 5:
      std::cout << "The queue is "<< ((queue.Empty()==0) ? "not " : "") << "empty"<< '\n';
      break;
      case 6:
      queue.Clear();
      break;
    }
  }
}

void SelectImplementation(const unsigned int& dataStructure,const unsigned int& type,const unsigned int& size)
{
  uint imp=0;
  while(imp==0 || (imp!=1 && imp!=2))
  {
    imp=0;
    std::cout << "Select the implementation of the ";
    if(dataStructure == 1 || dataStructure == 2)
    {
      std::cout << ((dataStructure==1) ? "Stack" : "Queue")<< '\n';
      std::cout<<"1) Vector"<< std::endl;
      std::cout<<"2) List" << std::endl;
    }
    if(dataStructure == 3)
    {
      std::cout << "BinaryTree" << '\n';
      std::cout<<"1) Vector"<< std::endl;
      std::cout<<"2) Pointers" << std::endl;
    }
    std::cout<<"Enter a number: ";
    std::cin>>imp;
    std::cout << ((imp != 1 && imp !=2) ? "Invalid choice." : "") << '\n';
  }
  if(dataStructure == 1 || dataStructure == 2)
  {
    CreateStackOrQueue(imp,dataStructure,type,size);
  }
  if(dataStructure == 3)
  {
    CreateBinaryTree(imp, type, size);
  }
}

void CreateVectorOrList(const unsigned int& dataStructure, const unsigned int& type, const unsigned int& size)
{
  if(dataStructure==1)
    {
      if(type==1)
      {
        lasd::Vector<int> vec(size);
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0,size);
        for(ulong index=0; index < size; ++index)
        {
          vec[index] = dist(gen);
        }
        MenuVector(vec,type);
      }
      if(type==2)
      {
        lasd::Vector<float> vec(size);
        int range=size;
        std::default_random_engine gen(std::random_device{}());
        std::uniform_real_distribution<float> dist((-range),range);
        for(ulong index=0; index < size; ++index)
        {
          float value = (int)(dist(gen) * 100 + .5);
          vec[index] = (value/100);
        }
        MenuVector(vec,type);
      }
      if(type==3)
      {
        lasd::Vector<double> vec(size);
        int range=size;
        std::default_random_engine gen(std::random_device{}());
        std::uniform_real_distribution<double> dist((-range),range);
        for(ulong index=0; index < size; ++index)
        {
          double value = (int)(dist(gen) * 10000 + .5);
          vec[index] = (value/10000);
        }
        MenuVector(vec,type);
      }
      if(type==4)
      {
        lasd::Vector<std::string> vec(size);
        std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0,62);
        for(int i=0; i<size; ++i)
        {
          int wordLength = dist(gen);
          while(wordLength > 0)
          {
            vec[i] += CHARACTERS[dist(gen)];
            wordLength--;
          }
        }
        MenuVector(vec,type);
      }
    }
    else
    {
      if(type==1)
      {
        lasd::List<int> list;
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0,size);
        for(ulong index=0; index < size; ++index)
        {
          int element = dist(gen);
          list.InsertAtBack(element);
        }
        MenuList(list,type);
      }
      if(type==2)
      {
        lasd::List<float> list;
        int range=size;
        std::default_random_engine gen(std::random_device{}());
        std::uniform_real_distribution<float> dist((-range),range);
        for(ulong index=0; index < size; ++index)
        {
          float element = dist(gen);
          list.InsertAtBack(element);
        }
        MenuList(list,type);
      }
      if(type==3)
      {
        lasd::List<double> list;
        int range=size;
        std::default_random_engine gen(std::random_device{}());
        std::uniform_real_distribution<double> dist((-range),range);
        for(ulong index=0; index < size; ++index)
        {
          double element = dist(gen);
          list.InsertAtBack(element);
        }
        MenuList(list,type);
      }
      if(type==4)
      {
        lasd::List<std::string> list;
        std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0,62);
        std::uniform_int_distribution<int> distWord(0,size);
        for(int i=0; i<size; ++i)
        {
          int wordLength = distWord(gen);
          std:: string word_ = "";
          while(wordLength > 0)
          {
            word_ += CHARACTERS[dist(gen)];
            wordLength--;
          }
          list.InsertAtBack(word_);
        }
        MenuList(list,type);
      }
    }
}

void CreateStackOrQueue(const unsigned int& imp, const unsigned int& dataStructure, const unsigned int& type, const unsigned int& size)
{
  if(imp==1)
  {
    if(dataStructure==1)
      {
        if(type==1)
        {
          lasd::StackVec<int> stack;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,size);
          for(ulong index=0; index < size; ++index)
          {
            stack.Push(dist(gen));
          }
          MenuStack(stack);
        }
        if(type==2)
        {
          lasd::StackVec<float> stack;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<float> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            float value = (int)(dist(gen) * 100 + .5);
            stack.Push((value/100));
          }
          MenuStack(stack);
        }
        if(type==3)
        {
          lasd::StackVec<double> stack;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<double> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            double value = (int)(dist(gen) * 10000 + .5);
            stack.Push(value/10000);
          }
          MenuStack(stack);
        }
        if(type==4)
        {
          lasd::StackVec<std::string> stack;
          std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,62);
          for(int i=0; i<size; ++i)
          {
            int wordLength = dist(gen);
            std::string word = "";
            while(wordLength > 0)
            {
              word += CHARACTERS[dist(gen)];
              wordLength--;
            }
            stack.Push(word);
          }
          MenuStack(stack);
        }
      }
      else
      {
        if(type==1)
        {
          lasd::QueueVec<int> queue;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,size);
          for(ulong index=0; index < size; ++index)
          {
            int element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==2)
        {
          lasd::QueueVec<float> queue;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<float> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            float element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==3)
        {
          lasd::QueueVec<double> queue;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<double> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            double element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==4)
        {
          lasd::QueueVec<std::string> queue;
          std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,62);
          for(int i=0; i<size; ++i)
          {
            int wordLength = dist(gen);
            std::string word = "";
            while(wordLength > 0)
            {
              word += CHARACTERS[dist(gen)];
              wordLength--;
            }
            queue.Enqueue(word);
          }
          MenuQueue(queue);
        }
      }
  }
  else if(imp==2)
  {
    if(dataStructure==1)
      {
        if(type==1)
        {
          lasd::StackLst<int> stack;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,size);
          for(ulong index=0; index < size; ++index)
          {
            stack.Push(dist(gen));
          }
          MenuStack(stack);
        }
        if(type==2)
        {
          lasd::StackLst<float> stack;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<float> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            float value = (int)(dist(gen) * 100 + .5);
            stack.Push((value/100));
          }
          MenuStack(stack);
        }
        if(type==3)
        {
          lasd::StackLst<double> stack;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<double> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            double value = (int)(dist(gen) * 10000 + .5);
            stack.Push(value/10000);
          }
          MenuStack(stack);
        }
        if(type==4)
        {
          lasd::StackLst<std::string> stack;
          std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,62);
          for(int i=0; i<size; ++i)
          {
            int wordLength = dist(gen);
            std::string word = "";
            while(wordLength > 0)
            {
              word += CHARACTERS[dist(gen)];
              wordLength--;
            }
            stack.Push(word);
          }
          MenuStack(stack);
        }
      }
      else
      {
        if(type==1)
        {
          lasd::QueueLst<int> queue;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,size);
          for(ulong index=0; index < size; ++index)
          {
            int element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==2)
        {
          lasd::QueueLst<float> queue;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<float> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            float element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==3)
        {
          lasd::QueueLst<double> queue;
          int range=size;
          std::default_random_engine gen(std::random_device{}());
          std::uniform_real_distribution<double> dist((-range),range);
          for(ulong index=0; index < size; ++index)
          {
            double element = dist(gen);
            queue.Enqueue(element);
          }
          MenuQueue(queue);
        }
        if(type==4)
        {
          lasd::QueueLst<std::string> queue;
          std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
          std::default_random_engine gen(std::random_device{}());
          std::uniform_int_distribution<int> dist(0,62);
          for(int i=0; i<size; ++i)
          {
            int wordLength = dist(gen);
            std::string word = "";
            while(wordLength > 0)
            {
              word += CHARACTERS[dist(gen)];
              wordLength--;
            }
            queue.Enqueue(word);
          }
          MenuQueue(queue);
        }
      }
  }
}

template <typename Data>
void MenuBinaryTree(lasd::BinaryTree<Data>& bt, const unsigned int& type)
{
  uint choice = 0;
  struct lasd::BinaryTree<Data>::Node::Node* current = &bt.Root();
  struct lasd::BinaryTree<Data>::Node::Node* last = &bt.Root();

  std::string typeString = "";
  std::string SelectionN5 = "5) ";
  std::string SelectionN6 = "6) ";
  switch (type) {
    case 1:
    typeString = "Int";
    SelectionN5 = "5) Product for elements less than n";
    SelectionN6 = "6) Apply the 3n function to all elements";
    break;
    case 2:
    typeString = "Float";
    SelectionN5 = "5) Computes the sum for elements grater than n";
    SelectionN6 = "6) Apply the n^3 function to all elements";
    break;
    case 3:
    typeString = "Double";
    SelectionN5 = "5) Not defined";
    SelectionN6 = "6) Not defined";
    break;
    case 4:
    typeString = "String";
    SelectionN5 = "5) Concatenation of strings with length less than or equal to n";
    SelectionN6 = "6) Head concatenation of a specific string str";
    break;
  }

  while(choice != 11)
  {
    std::cout << "===================== BinaryTree<"<<typeString<<"> Menu =====" << " Size: "<< bt.Size() <<" == Current element: " << current->Element() << '\n';
    std::cout << "1) Print the tree (Breath)" << '\n';
    std::cout << "2) Print the tree (PreOrder)" << '\n';
    std::cout << "3) Print the tree (InOrder)" << '\n';
    std::cout << "4) Print the tree (Post)" << '\n';
    std::cout << SelectionN5 << '\n';
    std::cout << SelectionN6 << '\n';
    std::cout << "7) Go to left child (if exists)" << '\n';
    std::cout << "8) Go to right child (if exists)" << '\n';
    std::cout << "9) Check if element exists" << '\n';
    std::cout << "10) Clear the tree" << '\n';
    std::cout << "11) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      bt.MapBreadth(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 2:
      bt.MapPreOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 3:
      bt.MapInOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 4:
      bt.MapPostOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 5:
        switch (type){
          case 1:
          {
            int value;
            int acc=1;
            std::cout << "Enter n value: ";
            std::cin >> value;
            bt.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 2:
          {
            float value;
            float acc=0;
            std::cout << "Enter n value: ";
            std::cin >> value;
            bt.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            int value;
            std::string acc="";
            std::cout << "Enter n value: ";
            std::cin >> value;
            bt.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
        break;
      }
      break;
      case 6:
      {
        switch (type){
          case 1:
          bt.MapPreOrder(&MapFunctionBtMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 2:
          bt.MapPreOrder(&MapFunctionBtMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            std::string str="";
            std::cout << "Enter str: ";
            std::cin >>str;
            bt.MapPreOrder(&MapFunctionBtMenu<Data>, &str);
            break;
          }
          break;
        }
      }
      break;
      case 7:
      if(current->HasLeftChild())
      {
        last = current;
        current = &current->LeftChild();
      }
      else
      {
        std::cout << "Current node hasn't left child" << '\n';
      }
      break;
      case 8:
      if(current->HasRightChild())
      {
        last = current;
        current = &current->RightChild();
      }
      else
      {
        std::cout << "Current node hasn't right child" << '\n';
      }
      break;
      case 9:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        std::cout << value <<  ((bt.Exists(value)==0) ? " doesn't": "") << " exists" << '\n';
      }
      break;
      case 10:
      bt.Clear();
      std::cout << "Test is terminated." << '\n';
      choice = 11;
      break;
    }
  }
}

void CreateBinaryTree(const unsigned int& imp, const unsigned int& type, const unsigned int& size)
{
  if(imp == 1)
  {
    //BinaryTreeVec
    if(type == 1)
    {
      lasd::Vector<int> vec(size);
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,size);
      for(ulong index=0; index < size; ++index)
      {
        vec[index] = dist(gen);
      }
      lasd::BinaryTreeVec<int> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==2)
    {
      lasd::Vector<float> vec(size);
      int range=size;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<float> dist((-range),range);
      for(ulong index=0; index < size; ++index)
      {
        float value = (int)(dist(gen) * 100 + .5);
        vec[index] = (value/100);
      }
      lasd::BinaryTreeVec<float> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==3)
    {
      lasd::Vector<double> vec(size);
      int range=size;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<double> dist((-range),range);
      for(ulong index=0; index < size; ++index)
      {
        double value = (int)(dist(gen) * 10000 + .5);
        vec[index] = (value/10000);
      }
      lasd::BinaryTreeVec<double> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==4)
    {
      lasd::Vector<std::string> vec(size);
      std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,62);
      for(int i=0; i<size; ++i)
      {
        int wordLength = dist(gen);
        while(wordLength > 0)
        {
          vec[i] += CHARACTERS[dist(gen)];
          wordLength--;
        }
      }
      lasd::BinaryTreeVec<std::string> bt(vec);
      MenuBinaryTree(bt, type);
    }
  }
  if(imp == 2)
  {
    //BinaryTreeLnk
    if(type == 1)
    {
      lasd::Vector<int> vec(size);
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,size);
      for(ulong index=0; index < size; ++index)
      {
        vec[index] = dist(gen);
      }
      lasd::BinaryTreeLnk<int> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==2)
    {
      lasd::Vector<float> vec(size);
      int range=size;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<float> dist((-range),range);
      for(ulong index=0; index < size; ++index)
      {
        float value = (int)(dist(gen) * 100 + .5);
        vec[index] = (value/100);
      }
      lasd::BinaryTreeLnk<float> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==3)
    {
      lasd::Vector<double> vec(size);
      int range=size;
      std::default_random_engine gen(std::random_device{}());
      std::uniform_real_distribution<double> dist((-range),range);
      for(ulong index=0; index < size; ++index)
      {
        double value = (int)(dist(gen) * 10000 + .5);
        vec[index] = (value/10000);
      }
      lasd::BinaryTreeLnk<double> bt(vec);
      MenuBinaryTree(bt, type);
    }
    if(type==4)
    {
      lasd::Vector<std::string> vec(size);
      std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      std::default_random_engine gen(std::random_device{}());
      std::uniform_int_distribution<int> dist(0,62);
      for(int i=0; i<size; ++i)
      {
        int wordLength = dist(gen);
        while(wordLength > 0)
        {
          vec[i] += CHARACTERS[dist(gen)];
          wordLength--;
        }
      }
      lasd::BinaryTreeLnk<std::string> bt(vec);
      MenuBinaryTree(bt, type);
    }
  }
}

template <typename Data>
void MenuBinarySearchTree(lasd::BST<Data>& bst, const unsigned int& type)
{
  uint choice = 0;
  struct lasd::BinaryTree<Data>::Node::Node* current = &bst.Root();
  struct lasd::BinaryTree<Data>::Node::Node* last = &bst.Root();

  std::string typeString = "";
  std::string SelectionN5 = "5) ";
  std::string SelectionN6 = "6) ";
  switch (type) {
    case 1:
    typeString = "Int";
    SelectionN5 = "5) Product for elements less than n";
    SelectionN6 = "6) Apply the 3n function to all elements";
    break;
    case 2:
    typeString = "Float";
    SelectionN5 = "5) Computes the sum for elements grater than n";
    SelectionN6 = "6) Apply the n^3 function to all elements";
    break;
    case 3:
    typeString = "Double";
    SelectionN5 = "5) Not defined";
    SelectionN6 = "6) Not defined";
    break;
    case 4:
    typeString = "String";
    SelectionN5 = "5) Concatenation of strings with length less than or equal to n";
    SelectionN6 = "6) Head concatenation of a specific string str";
    break;
  }

  while(choice != 19)
  {
    std::cout << "===================== BinarySearchTree<"<<typeString<<"> Menu =====" << " Size: "<< bst.Size()<< '\n';
    std::cout << "1) Print the BinarySearchTree (Breath)" << '\n';
    std::cout << "2) Print the BinarySearchTree (PreOrder)" << '\n';
    std::cout << "3) Print the BinarySearchTree (InOrder)" << '\n';
    std::cout << "4) Print the BinarySearchTree (Post)" << '\n';
    std::cout << SelectionN5 << '\n';
    std::cout << SelectionN6 << '\n';
    std::cout << "7) Insert an element" << '\n';
    std::cout << "8) Check if element exists" << '\n';
    std::cout << "9) Delete a element" << '\n';
    std::cout << "10) Print min" << '\n';
    std::cout << "11) Delete min" << '\n';
    std::cout << "12) Print max" << '\n';
    std::cout << "13) Delete max" << '\n';
    std::cout << "14) Print predecessor" << '\n';
    std::cout << "15) Delete predecessor" << '\n';
    std::cout << "16) Print successor" << '\n';
    std::cout << "17) Delete successor" << '\n';
    std::cout << "18) Clear the tree" << '\n';
    std::cout << "19) Go back to Menu" << '\n';
    std::cout << "Select an option: ";
    std::cin>>choice;

    switch (choice) {
      case 1:
      bst.MapBreadth(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 2:
      bst.MapPreOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 3:
      bst.MapInOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 4:
      bst.MapPostOrder(&MapPrint<Data>, 0);
      std::cout << "Done! " << '\n';
      break;
      case 5:
        switch (type){
          case 1:
          {
            int value;
            int acc=1;
            std::cout << "Enter n value: ";
            std::cin >> value;
            bst.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 2:
          {
            float value;
            float acc=0;
            std::cout << "Enter n value: ";
            std::cin >> value;
            bst.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            int value;
            std::string acc="";
            std::cout << "Enter n value: ";
            std::cin >> value;
            bst.FoldPreOrder(&FoldFunctionBtMenu<Data>,&value,&acc);
            std::cout << "Result: "<< acc << '\n';
            break;
          }
        break;
      }
      break;
      case 6:
      {
        switch (type){
          case 1:
          bst.MapPreOrder(&MapFunctionBtMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 2:
          bst.MapPreOrder(&MapFunctionBtMenu<Data>, nullptr);
          std::cout << "Done! " << '\n';
          break;
          case 3:
          std::cout << "Not defined" << '\n';
          break;
          case 4:
          {
            std::string str="";
            std::cout << "Enter str: ";
            std::cin >>str;
            bst.MapPreOrder(&MapFunctionBtMenu<Data>, &str);
            break;
          }
          break;
        }
      }
      break;
      case 7:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        bst.Insert(value);
        std::cout << "Value "<< value << " inserted" << '\n';
      }
      break;
      case 8:
      {
        Data value;
        std::cout << "Enter a value: ";
        std::cin >> value;
        std::cout << value <<  ((bst.Exists(value)==0) ? " doesn't": "") << " exists" << '\n';
      }
      break;
      case 9:
      {
        try{
          Data value;
          ulong sizeb = bst.Size();
          std::cout << "Insert a value to delete: ";
          std::cin >> value;
          bst.Remove(value);
          if(sizeb == bst.Size())
          {
            std::cout << "Value not found" << '\n';
          }
          else
          {
            std::cout << "Value = ("<< value <<") deleted." << '\n';
          }
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 10:
      {
        try{
          std::cout << "Min = "<< bst.Min()<< '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 11:
      {
        try{
          Data minDeleted = bst.MinNRemove();
          std::cout << "Min (value = "<< minDeleted << ") deleted."<< '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 12:
      {
        try{
          std::cout << "Max = "<< bst.Max()<< '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 13:
      {
        try{
          Data maxDeleted = bst.MaxNRemove();
          std::cout << "Max (value = "<< maxDeleted << ") deleted."<< '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 14:
      {
        try{
          Data value;
          std::cout << "Enter a value to print its predecessor: ";
          std::cin >>value;
          std::cout << "Predecessor of value "<< value << " is " << bst.Predecessor(value) << '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 15:
      {
        try{
          Data value;
          std::cout << "Enter a value to delete its predecessor: ";
          std::cin >>value;
          Data predecessorDeleted = bst.PredecessorNRemove(value);
          std::cout << "Predecessor ("<< predecessorDeleted << ") of value "<< value << " deleted."<< '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what()<< '\n';
        }
      }
      break;
      case 16:
      {
        try{
          Data value;
          std::cout << "Enter a value to print its successor: ";
          std::cin >>value;
          std::cout << "Successor of value "<< value << " is " << bst.Successor(value) << '\n';
        }
        catch (const std::exception &exc)
        {
            std::cerr << exc.what() << '\n';
        }
      }
      break;
      case 17:
      {
        try{
          Data value;
          std::cout << "Enter a value to delete its successor: ";
          std::cin >>value;
          Data successorDeleted = bst.SuccessorNRemove(value);
          std::cout << "Successor ("<< successorDeleted << ") of value "<< value << " deleted."<< '\n';
        }

        catch (const std::exception &exc)
        {
            std::cerr << exc.what();
        }
      }
      break;
      case 18:
      bst.Clear();
      std::cout << "Test is terminated." << '\n';
      choice = 19;
      break;
    }
  }
}

void CreateBinarySearchTree(const unsigned int& type, const unsigned int& size)
{
  if(type == 1)
  {
    lasd::BST<int> bst;
    uint sizeb = size;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0,size);
    while(sizeb != bst.Size())
    {
        bst.Insert(dist(gen));
    }
    MenuBinarySearchTree(bst, type);
  }
  if(type==2)
  {
    lasd::BST<int> bst;
    uint sizeb = size;
    int range=size;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<float> dist((-range),range);
    while(sizeb != bst.Size())
    {
      float value = (int)(dist(gen) * 100 + .5);
      bst.Insert(value/100);
    }
    MenuBinarySearchTree(bst, type);
  }
  if(type==3)
  {
    lasd::BST<int> bst;
    uint sizeb = size;
    int range=size;
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<double> dist((-range),range);
    while(sizeb != bst.Size())
    {
      double value = (int)(dist(gen) * 10000 + .5);
      bst.Insert(value/1000);
    }
    MenuBinarySearchTree(bst, type);
  }
  if(type==4)
  {
    lasd::Vector<std::string> vec(size);
    std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0,62);
    for(int i=0; i<size; ++i)
    {
      int wordLength = dist(gen);
      while(wordLength > 0)
      {
        vec[i] += CHARACTERS[dist(gen)];
        wordLength--;
      }
    }
    lasd::BST<std::string> bst(vec);
    MenuBinarySearchTree(bst, type);
  }
}
