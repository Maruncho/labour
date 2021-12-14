
#include <iostream>
#include <string>
#include <vector>

template<typename T> struct S{ 
	S(T v) : val{ v } {}
	T& get();
	const T& get() const;
	T& operator=(const T& value);
	std::istream& operator>>(std::istream& is);
private:
	T val;
};

template<typename T> T& S<T>::get() { return val; }
template<typename T> const T& S<T>::get() const { return val; }
template<typename T> T& S<T>::operator=(const T& value) { val = value; }
template<typename T> std::istream& S<T>::operator>>(std::istream& is) {
	is >> val;
	return is;
}

//not sure what's the purpose of the function
/*template<typename T> void read_val(T& v) {
	std::cin >> v;
}*/

int main()
{
	S<int> num = 1;
	S<char> ch = 'a';
	S<double> dpn = 1.5;
	S<std::string> str {"name"};
	S<std::vector<int>> vec{ std::vector<int>{1} };

	/*read_val(num);
	read_val(ch);
	read_val(dpn);
	read_val(str);*/

	std::cout << num.get() <<'\n';
	std::cout << ch.get()<<'\n';
	std::cout << dpn.get() <<'\n';
	std::cout << str.get() <<'\n';
	std::vector<int> v = vec.get();
	std::cout << v[0] <<'\n';
}		  		 