#include <iostream>
#include "CsvIO.h"
using namespace std;



CsvIO io;

int main(){
  io.readCvsFile("sym.csv");
    //for(int i = 0; i < 1000; i++){
  std::cout << io.getGrid();
    //}

    //cout << "The End :D" << endl;
    //return 0;
}
