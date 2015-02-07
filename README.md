# ParseCsv
A C++ header only, rfc4180 compliant, CSV file parser, using some field parsing code from the freeware "sqlite" project. 

This project is currently only tested on Linux (64bit Ubuntu 14.04 LTS), but should work under most C++ 11 compatable development environments (windows, mac) with little if any modification. 

The project's main deliverable class, CsvIO (found and completely implemented in CvsIO.h) currently access a csv compliant file and parses it into a 'grid', e.g. a vector of row (field) string vectors, defined in C++ as follows:

typedef std::vector<std::string> VStr;

typedef std::vector<VStr> VVStr; // vector of string (field) vectors (grid)

There is also an overloaded ostream operator for displaying the grid's content.

# Three steps are required to parse a csv file:

1) include "CsvIO.h" and instantiate an instance of that class:

  e.g. CsvIO io;

2) call the readCsvFile method of your CsvIO instance, passing in the path to the csv file to be parsed:

  e.g. io.readCsvFile("sy.csv");

3) access the grid containing the parsed results with the getGrid() method:

  e.g. const VVStr& grid = io.getGrid();
  
From the grid reference, you can access any field/column value using standard vector container methods. 
	e.g. string value = grid[row][col];

See main.cpp for a minimal working example of CsvIO. a sample CSV test file (sym.csv) has been included in this project for testing purposes.


NOTE: this is a first commit to Github,and the code utilized from the SQLite source has been left intact as much as possible. The major chance has been in the substitution of a C++ std::string buffer for the SQLite 'C' buffer management code.

Future versions will implement the Grid - to - CSV format string/file output, which is rarely utilized in my work (mostly it's a one-way street transformation from csv to SQLite or Redis) -- but will be done to live up to the 'IO' in CsvIO and add functional symmetry to the class :)
 
