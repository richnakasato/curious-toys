//#define DO_OP

#include <iostream>
#include <string>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

class String : public std::string
{
    char* s;
    size_t sz;

public:
    String() : std::string()
    {
        std::cout << "ctor" << std::endl;
        s = nullptr;
        sz = 0;
    }

    String(const char* str) : std::string(str)
    {
        std::cout << "cp ctor" << std::endl;
        s = nullptr;
        sz = 0;
    }

#ifdef DO_OP
    std::string& operator=(const char* str)
    {
        std::cout << "op=" << std::endl;
        return std::string::operator=(str);
    }
#endif //DO_OP

    ~String()
    {
        std::cout << "dtor" << std::endl;
        delete[] s;
        s = nullptr;
        sz = 0;
    }

    char* foo()
    {
        size_t new_size = this->size()+1;
        if (sz < new_size) {
            delete[] s;
            sz = new_size;
            s = new char[new_size];
        }
        for (size_t i=0; i<new_size-1; ++i) {
            s[i] = (*this)[i];
        }
        s[new_size-1] = 0;
        return s;
    }
};

int main()
{
    const char* ccp;
    String a;
    a = "short";
    ccp = a.foo();
    a = "this string should be long";
    ccp = a.foo();

    std::cout << "--\n" << ccp << std::endl;
    return 0;
}
