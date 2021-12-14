
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

void print_array(std::ostream& os, int* a, int n) {
    for (int i = 0; i < n; i++) {
        os <<'('<< a[i] <<", " << a << ')';
    }
    os << '\n';
}

void print_vector(std::ostream& os, const std::vector<int>& v) {
    for (int x : v)
        os << x << ' ';
    os << '\n';
}

int main() try {

    //1,2
    int* p1 = new int{7};
    print_array(std::cout, p1, 1);
    //delete p1;

    //3,4
    int* p2 = new int[7];
    for (int i = 0; i < 7; i++)
        p2[i] = pow(2,i);
    print_array(std::cout, p2, 7);
    //delete[] p2;

    int* p3 = p2; //5
    p2 = p1; //6
    p2 = p3; //7

    //8
    print_array(std::cout, p1, 1);
    print_array(std::cout, p2, 7);

    //9
    delete p1;
    delete[] p2;
    
    //10
    p1 = new int[10];
    for (int i = 0; i < 10; i++)
        p1[i] = pow(2, i);

    //11,12
    p2 = new int[10];
    for (int i = 0; i < 10; i++)
        p2[i] = p1[i];
    print_array(std::cout, p2, 10);

    delete[] p1;
    delete[] p2;

    std::cout << "-------------------------------------\n";

    //13 10
    std::vector<int> v1(10);
    for (int i = 0; i < 10; i++)
        v1[i] = pow(2, i);
    //13 11
    std::vector<int> v2(10);
    //13 12
    v2 = v1;

    print_vector(std::cout, v2);




}
catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    std::cerr << "Unknown exception\n";
    return 2;
}