#include <iostream>
#include "MultiSet.h"
#include "NumberSeries.h"


int doubleUpFunc(int n) 
{
    return n*3;
}

int main()
{
    NumberSeries num(1, doubleUpFunc);
    num.generateNumberByIndex(110);
    /*MultiSet s(10);
    s.add(1);
    s.add(1);
    s.add(2);
    s.add(3);
    s.add(3);
    s.add(6);
    s.add(6);
    s.add(6);
    s.print();


    MultiSet p(5);
    p.add(1);
    p.add(1);
    p.add(2);
    p.print();

    MultiSet result = unionOfMultisets(s, p);
    result.print();

    MultiSet intersec = intersection(s, p);
    intersec.print();*/
}