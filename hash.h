/*
* hash.h
*
* Author: Joe Cassidy
* Date: 21 November, 2017
* Class: CSCI 271
*/

#ifndef hash_H_
#define hash_H_
#include <list>
using std::cout;
using namespace std;

template <class T>
class hash;

template <class T>
class node;

template <class T>
class elem;

template <class T>
class hash{
public:
  hash<T>();
  int search(T toFind, int location);
  int hashIn(T insert, int location);
  node<T> * retrieve(int location);
private:
  node<T> * table[750];
};

template <class T>
hash<T>::hash(){
  for(int i = 0; i < 750; i++){
    table[i] = new node<T>;
  }
}

template <class T>
int hash<T>::search(T toFind, int location){
  int searchLocation = location % 750;
  while(table[searchLocation]->getFlag() != 0){
    if(table[searchLocation]->getData() == toFind){
      //found at searchLocation
      return searchLocation;
    }
    searchLocation += 31;
    searchLocation = searchLocation % 750;
  }
  //not found
  return -1;
}

template <class T>
int hash<T>::hashIn(T insert, int location){
  int insertLocation = location % 750;
  while(table[insertLocation]->getFlag() != 0){
    insertLocation += 31;
    insertLocation = insertLocation % 750;
  }
  table[insertLocation]->setFlag(1);
  table[insertLocation]->setData(insert);
  return insertLocation;
}

template <class T>
node<T> * hash<T>::retrieve(int location){
  return table[location];
}

template <class T>
class elem{
public:
  elem<T>(T value, int label);
  T getData();
  T setData(T value);
  int getNumber();
  int setNumber(int label);
private:
  T data;
  int number;
};

template <class T>
elem<T>::elem(T value, int label){
  data = value;
  number = label;
}

template <class T>
T elem<T>::getData(){
  return data;
}

template <class T>
T elem<T>::setData(T value){
  data = value;
}

template <class T>
int elem<T>::getNumber(){
  return number;
}

template <class T>
int elem<T>::setNumber(int label){
  number = label;
}

template <class T>
class node{
public:
  node<T>();
  node<T>(T value);
  T getData();
  void setData(T value);
  int getFlag();
  void setFlag(int newFlag);
  list<elem<T> > sublist;
private:
  T data;
  int flag; //flag will be 0 for empty, 1 for full
};

template <class T>
node<T>::node(){
  flag = 0;
}

template <class T>
node<T>::node(T value){
  data = value;
  flag = 1;
}

template <class T>
T node<T>::getData(){
  return data;
}

template <class T>
void node<T>::setData(T value){
  data = value;
}

template <class T>
int node<T>::getFlag(){
  return flag;
}

template <class T>
void node<T>::setFlag(int newFlag){
  flag = newFlag;
}

#endif /* hash_H_ */
