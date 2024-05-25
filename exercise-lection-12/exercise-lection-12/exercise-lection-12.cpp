#include <iostream>
#include "Queue.h"
#include "MyString.h"

int main()
{
    Queue<int> q;
    Queue<double> q2;
    q.push(1);
    q.push(1);
    q2.push(1);
    q2.push(1);
    q2.push(3);
    q.push(5);

    std::cout << q.peek() << std::endl;
    q.pop();

    std::cout << q.peek() << std::endl;
    q.pop();

    std::cout << q.peek() << std::endl;
    q.pop();


    std::cout << q2.peek() << std::endl;
    q2.pop();

    std::cout << q.isEmpty() << std::endl;
}