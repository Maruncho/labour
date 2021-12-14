
#include <iostream>

char* stringdup(const char* str) {
	int count = 0;
	while (*str) { count++; str++; }
	str -= count;
	char* ret = new char[count + 1];
    while (*ret++ = *str++);
    return ret -= (count+1);
}

int strsize(const char* str) {
    int count = 0;
    while (*str) { count++; str++; }
    str -= count;
    return count;
}

char* findx(char* s, const char* x) {
    if (!s || !x) return nullptr;
    int ss = strsize(s);
    int xs = strsize(x);
    bool is_succesful = 1;

    char* sBegin = s;
    int countj = 0;

    for (int i = 0; i < ss; i++) {
        s += i;
        if (*s == *x) {
            for (int j = 1; j < xs; j++) {
                countj = j;
                s++;
                x++;
                if (*s != *x) {
                    is_succesful = 0;
                    break;
                }
            }
            s = sBegin;
            x -= countj;
            if (is_succesful) {
                char* pos = s;
                pos += i;
                return pos;
            }
            is_succesful = 1;
        }
        s = sBegin;
    }
    return nullptr;
}

int main()
{
    char ex1[] = "Hello World!";

    //test stringdup() exercise 1
    char* ex2 = stringdup(ex1);
    std::cout << ex2 << '\n';

    //test findx() exercise 2
    char* ex3 = findx(ex1, "o Wor");
    if (ex3 != nullptr)
        std::cout << ex3 << '\n';
}