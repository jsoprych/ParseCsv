# ParseCsv
A C++ header only, rfc4180 compliant, CSV file parser, using some field parsing code from the freeware "sqlite" project. 

This project is currently only tested on Linux (64bit Ubuntu 14.04 LTS), but should work under most C++ 11 compatable development environments (windows, mac) with little if any modification. 

The project's main deliverable class, CsvIO (found and completely implemented in CvsIO.h) currently access a csv compliant file and parses it into a 'grid', e.g. a vector of row (field) string vectors, defined in C++ as follows:

``` C++
typedef std::vector<std::string> VStr;

typedef std::vector<VStr> VVStr; // vector of string (field) vectors (grid)
```

There is also an overloaded ostream operator for displaying the grid's content.

# Three steps are required to parse a csv file:

1) include "CsvIO.h" and instantiate an instance of that class:


2) call the readCsvFile method of your CsvIO instance, passing in the path to the csv file to be parsed:


3) access the grid containing the parsed results with the getGrid() method:

  
From the grid variable, you can access any field/column value using standard vector container methods. 
	e.g. string value = grid[row][col];
	
```C++
#include <iostream>
#include "CsvIO.h"  // 1.a) include CsvIO.h file
using namespace std;

CsvIO io;   // 1.b) instantiate CvsIO class

int main(){
  io.readCsvFile("sym.csv");  // 2) parse 'sym.csv' file

  auto grid = io.getGrid();   // 3) get grid containing the parsed results

  // Example A: printing out resulting grid
  cout << grid << endl; // 
  
  // Example B: print out specified grid element
  int row = 3;
  int col = 0; // zero based indexing
  
  cout << "grid[" << row << "][" << col << "] = " << grid[row][col] << endl; 
  //}

  cout << "The End ;D" << endl;
  return 0;
}
```
The tail end of the resulting output of the above should look like this:

```
1962-01-12|564.00|568.00|564.00|564.00|435200|2.41
1962-01-11|558.50|563.00|558.50|563.00|315200|2.40
1962-01-10|557.00|559.50|557.00|557.00|299200|2.38
1962-01-09|552.00|563.00|552.00|556.00|491200|2.37
1962-01-08|559.50|559.50|545.00|549.50|544000|2.34
1962-01-05|570.50|570.50|559.00|560.00|363200|2.39
1962-01-04|577.00|577.00|571.00|571.25|256000|2.44
1962-01-03|572.00|577.00|572.00|577.00|288000|2.46
1962-01-02|578.50|578.50|572.00|572.00|387200|2.44

grid[3][0] = 2014-10-29
The End ;D
```


See main.cpp for a minimal working example of CsvIO. A sample CSV test file (sym.csv) has been included in this project for testing purposes.


NOTE: this is a first commit to Github,and the code utilized from the SQLite source has been left intact as much as possible. The major chance has been in the substitution of a C++ std::string buffer for the SQLite 'C' buffer and it's memory management code.

Future versions will implement the Grid - to - CSV format string/file output, which is rarely utilized in my work (mostly it's a one-way street transformation from csv to SQLite or Redis) -- but will be done to live up to the 'IO' in CsvIO and add functional symmetry to the class :)
 
