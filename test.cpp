#include "test.h"
#include <iostream>

using namespace ComplexLib;

int main()
{
    Square square = Square(Point(), 5.0);
    std::cout << square.area() << std::endl;
}