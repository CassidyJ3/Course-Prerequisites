/*
* main.cpp
*
* Author: Joe Cassidy
* Purpose: To determine a possible order in which a given list of courses and
*          their prerequisites may be taken.
* Date: 13 December, 2017
* Class: CSCI 271
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <list>
#include "hash.h"
using namespace std;

int hashFunction(string toHash){
  int hashValue = 0;
  for(int i = 0; i < toHash.size(); i++){
    hashValue += (i+1) * (int)(toHash.at(i));
  }
  return hashValue;
}

int main(){
  string filename;
  ifstream input;
  hash<string> courseTable;
  while(!input.is_open()){
    cout << "Please enter the file name:" << endl;
    cin >> filename;
    input.open(filename.c_str());
    if(!input.is_open()){
      cout << "Error: invalid file name." << endl;
    }
  }

  bool firstInLine = true;
  string baseCourse;
  string course;
  int totals[750];
  for(int i = 0; i < 750; i++){
    totals[i] = -1; //acts as a flag so that unused addresses are ignored
  }
  int baseCourseHash;
  while(!input.eof()){
    input >> course;
    if(course == "#"){
      firstInLine = true;
    }
    else{
      int courseHash = courseTable.search(course, hashFunction(course));
      if(courseHash < 0){
        courseHash = courseTable.hashIn(course, hashFunction(course));
        totals[courseHash] = 0;
      }
      if(firstInLine){
        baseCourse = course;
        baseCourseHash = courseHash;
        firstInLine = false;
      }
      else{
        elem<string> append = elem<string>(baseCourse, baseCourseHash);
        courseTable.retrieve(courseHash)->sublist.push_front(append);
        totals[baseCourseHash] += 1;
      }
    }
  }

  //output
  list<int> zeroes;
  for(int i = 0; i < 750; i++){
    if(totals[i] == 0){
      zeroes.push_back(i);
    }
  }
  while(!zeroes.empty()){
    int next = zeroes.front();
    string nextCourse = courseTable.retrieve(next)->getData();
    cout << nextCourse << endl;
    while(!courseTable.retrieve(next)->sublist.empty()){
      int finder = courseTable.retrieve(next)->sublist.front().getNumber();
      totals[finder] -= 1;
      if(totals[finder] == 0){
        zeroes.push_back(finder);
      }
      courseTable.retrieve(next)->sublist.pop_front();
    }
    zeroes.pop_front();
  }
}
