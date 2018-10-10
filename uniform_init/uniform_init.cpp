#include <iostream>

int main()
{
    int a = 10;
    int b{10};
    std::string c = "hello";
    std::string d{"hello"};
    if (a == b && c == d) {
        std::cout << "uniform init works!\n";
    }
    return 0;
}
