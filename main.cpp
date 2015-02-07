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

CsvIO io;   // 1) instantiate class

int main(){
  io.readCsvFile("sym.csv");  // 2) parse 'sym.csv' file

  auto grid = io.getGrid();   // 3) get grid containing the parsed results

  // Example A: printing out resulting grid
  cout << grid << endl; //

  // Example B: print out specified grid element
  int row = 3;
  int col = 0; // zero based indexing

  cout << "grid[" << row << "][" << col << "] = " << grid[row][col] << endlDebug;
  //}

  cout << "The End ;D" << endl;
  return 0;
}
