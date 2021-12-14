#include <iostream>
#include <stdexcept>


void to_lower(char* s) {
    for (int i = 0; s[i] ; i++) 
    {
        if (s==nullptr) return;
        if (s[i] >= 65 && s[i] <= 90)
            s[i] += 32;
    }
}


int strsize(const char* s) {
    int n = 0;
    for (int i = 0; s[i]; i++)
        n++;
    return n;
}

char* cstrdup(const char* s) {
    if (s == nullptr) return nullptr;
    int size = strsize(s) + 1;
    char* c = new char[size];

    for (int i = 0; i < size; i++)
        c[i] = s[i];
    return c;
}

//return the starting index of the match in char* s
char* findx(char* s, const char* x) {
    if (!s || !x) return nullptr;
    int ss = strsize(s);
    int xs = strsize(x);
    bool is_succesful = 1;

    for (int i = 0; i < ss; i++) {
        if (s[i] == x[0]) {
            for (int j = 1; j < (xs); j++)
                if (s[i + j] != x[j]) {
                    is_succesful = 0;
                    break;
                }
            if (is_succesful) {
                char* pos = s;
                pos += i;
                return pos;
            }
            is_succesful = 1;
        }
    }
    return nullptr;
}


int main() try 
{
    //test to_lower() exercise 3
    char ex1[] = "Hello World!";
    to_lower(ex1);
    std::cout << ex1 << '\n';

    //test cstrdup() exercise 4
    char* ex2 = cstrdup(ex1);
    std::cout << ex2 << '\n';

    //test findx() exercise 5
    char* ex3 = findx(ex1, "o wor");
    if(ex3 != nullptr)
        std::cout << ex3 << '\n';
}
catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Unknown exception\n";
    return 2;
}