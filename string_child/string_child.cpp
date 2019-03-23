//#define DO_OP

#include <iostream>
#include <string>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct Foo
{
    std::string str;
    char* buf;
    size_t sz;

    Foo()
    {
        std::cout << "ctor" << std::endl;
        str = "";
        buf = nullptr;
        sz = 0;
    }

    Foo(const char* s)
    {
        std::cout << "cp ctor" << std::endl;
        str = std::string(s);
        buf = nullptr;
        sz = 0;
    }

    ~Foo()
    {
        std::cout << "dtor" << std::endl;
        if (sz)
            delete[] buf;
        sz = 0;
    }

#ifdef DO_OP
    Foo& operator=(const char* s)
    {
        std::cout << "op=" << std::endl;
        str = std::string(s);
        return *this;
    }
#endif //DO_OP

    void copy_assign(const char* s)
    {
        Foo other(s);
        str = other.str;
        buf = other.buf;
        sz = other.sz;
    }

    char* bar(void)
    {
        size_t new_sz = str.size()+1;
        if (sz < new_sz) {
            delete[] buf;
            buf = new char[new_sz];
            sz = new_sz;
        }
        for (size_t i=0; i<sz-1; ++i) {
            buf[i] = str[i];
        }
        buf[sz-1] = 0;
        return buf;
    }
};


struct Thing
{
    Thing()
    {
        std::cout << "ctor" << std::endl;
    }

    Thing(const int& v)
    {
        std::cout << "cp ctor" << std::endl;
    }

#ifdef DO_OP
    Thing& operator=(const int& other)
    {
        std::cout << "cp assn" << std::endl;
        return *this;
    }
#endif //DO_OP

    ~Thing()
    {
        std::cout << "dtor" << std::endl;
    }
};


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

    /*
    Thing a;
    a = 1;
    */

    Foo foo;
    foo = "test";
    const char* foobar = foo.bar();
    std::cout << "--\n" << foobar << std::endl;
    //foo = "another test";
    foo.copy_assign("another test");
    foobar = foo.bar();
    std::cout << "--\n" << foobar << std::endl;

    return 0;
}
