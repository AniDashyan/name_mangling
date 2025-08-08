#include <iostream>
#include <string>

class Foo {
    public:
        void bar(int x) { std::cout << "int: " << x << std::endl; }
        void bar(double x) { std::cout << "double: " << x << std::endl; }

        template<typename T>
        void baz(T val) { std::cout << "template: " << val << std::endl; 
    }
};

int main() {
    Foo f;
    f.bar(42);
    f.bar(3.14);
    f.baz<std::string>("hello");
    return 0;
}