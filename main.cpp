/*
** 2015 February 5
**
** The author, John Soprych, disclaims copyright to this source code.
** In place of a legal notice, here is an also borrowed blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains a C++ wrapper around some cvs field parsing code
** from the freeware "sqlite" command line utility for database access.
*/
#include <iostream>
#include "CsvIO.h"
using namespace std;

CsvIO io;

int main(){
  io.readCsvFile("sym.csv");

  //for(int i = 0; i < 1000; i++){
  std::cout << io.getGrid();
  //}

  cout << "The End :D" << endl;
  return 0;
}
