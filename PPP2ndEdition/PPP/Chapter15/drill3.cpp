#include "../std_lib_facilities.h"

struct Person
{
	Person() {}
	Person(string f, string s, int a);
	string get_first_name() const { return first_name; }
	string get_second_name() const { return second_name; }
	int get_age() const { return age; }
	void add_restricted(string s) { restricted += s; }
private:
	string first_name;
	string second_name;
	int age;
	string restricted = ";:\"\'[]*&^%$#@!";
};

Person::Person(string f, string s, int a)
	:first_name{ f }, second_name{ s }, age{ a }
{
	if (age < 0 || age>150)
		error("Age over the limit: " + age);

	for (char c : first_name) {
		for (char h : restricted) {
			if (c == h)
				error("Inappropriate character in first name: " + first_name);
		}
	}
	for (char c : second_name) {
		for (char h : restricted) {
			if (c == h)
				error("Inappropriate character in second name: " + second_name);
		}
	}
}

ostream& operator<<(ostream& os, const Person& me) {
	return os << me.get_first_name() << ' ' << me.get_second_name() << '\t' << me.get_age();
}

istream& operator>>(istream& is, Person& me) {
	char c1;
	char c2;
	char c3;
	char c4;
	string f;
	string s;
	int a;

	if (is >> c1 >> f >> c2 >> s >> c3 >> a >> c4) {
		if (c1 != '(' || c2 != ',' || c3 != ',' || c4 !=')') {
			is.clear(ios_base::failbit);
			return is;
		}
		Person p{ f,s,a };
		me = p;
		return is;
	}
	return is;
}

int main()
{
	try {
		cout << "Type in your data. Format: (firstName ,secondName ,age)\n SPACES ARE IMPORTANT" << endl;;

		Person me;
		cin >> me;
		cout << me;
	}
	catch (std::exception & e) {
		std::cerr << "Exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown error!\n";
		return 2;
	}
}