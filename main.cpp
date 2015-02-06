#include <iostream>
#include "CsvIO.h"
using namespace std;



CsvIO io;

int main()
{

    for(int i = 0; i < 1000; i++){
      std::cout << io.readCvsFile("sym.csv");
    }


    cout << io.test() << endl;
    cout << "Hello world!" << endl;
    return 0;
}
