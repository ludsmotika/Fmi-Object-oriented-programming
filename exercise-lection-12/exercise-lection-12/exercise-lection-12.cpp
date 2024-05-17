#include <iostream>
#include "Queue.h"
#include "MyString.h"

int main()
{
    Queue<int> q;
    q.push(1);
    q.push(3);
    q.push(5);

    std::cout << q.peek() << std::endl;
    q.pop();

    std::cout << q.peek() << std::endl;
    q.pop();

    std::cout << q.peek() << std::endl;
    q.pop();

    std::cout << q.isEmpty() << std::endl;
}