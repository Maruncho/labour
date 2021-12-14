
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <string>

template<class Iter, class T>

unsigned int my_count(Iter first, Iter last, T val)
{
	unsigned int count = 0;
	while (first != last) {
		if (*first == val) count++;
		first++;
	}
	return count;
}

template<class Iter, class Pred>

unsigned int my_count_if(Iter first, Iter last, Pred p)
{
	unsigned int count = 0;
	while (first != last) {
		if (p(*first)) count++;
		first++;
	}
	return count;
}

struct Actor {
        std::string name;
        char sex;               // m or f
    };

class Check_sex {
        char sex;
    public:
        Check_sex(char s) : sex{ s }
        {
            if (s != 'm' && s != 'f')
                throw std::runtime_error("unrecognized sex!");
        }

        bool operator()(const Actor& a) { return a.sex == sex; }
    };

struct Fruit {
    std::string name;
    int quantity;
    double unit_price;

    explicit Fruit(const std::string& n, int q = 0, double p = 0.0)
        : name{ n }, quantity{ q }, unit_price{ p } { }
};

struct Fruit_ptr_cmp {
    bool operator()(const Fruit* a, const Fruit* b) const
    {
        return a->name < b->name;
    }
};

int main()
{
    //---------------Exercise 3-----------------
    std::cout << "Exercise 3:\n\n";

    std::vector<char> vc{ 'a', 'b', 'c', 'd', 'e' };
    std::list<int> li{ 1, 2, 3, 1, 4, 5, 1 };

    std::cout << "a's in vc: " << my_count(vc.begin(), vc.end(), 'a') << '\n'
        << "g's in vc: " << my_count(vc.begin(), vc.end(), 'g') << '\n'
        << "1's in li: " << my_count(li.begin(), li.end(), 1) << '\n'
        << "6's in li: " << my_count(li.begin(), li.end(), 6) << '\n';

    //---------------Exercise 4-----------------
    std::cout << "\nExercise 4:\n\n";

      std::vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

                auto threes = my_count_if(vi.begin(), vi.end(),
                    [](int v) { return v % 3 == 0; });

                std::cout << "There are " << threes << " multiples of 3 in vi\n";

                std::list<Actor> la{
                    { "Whitney Houston", 'f' },
                    { "Bruce Willis", 'm' },
                    { "Kurt Russel", 'm' },
                    { "Markie Post", 'f' },
                    { "Winona Ryder", 'f' }
                };

                auto women = my_count_if(la.begin(), la.end(), Check_sex('f'));

                std::cout << "There are " << women << " ladies in la\n";

    //---------------Exercise 6-----------------
    std::cout << "\nExercise 6:\n\n";

    std::vector<Fruit> vf{
        Fruit{ "Plum", 3 },
        Fruit{ "Grape", 53 },
        Fruit{ "Banana", 6 },
        Fruit{ "Apple", 4 },
        Fruit{ "Orange", 5 },
        Fruit{ "Cherry", 37 },
        Fruit{ "Kiwi", 0 }
    };

    std::set<Fruit*, Fruit_ptr_cmp> produce;

    // 'copy' vector to set - set elements must be inserted
    for (auto& f : vf)
        produce.insert(&f);

    // print vector for reference
    std::cout << "Vector of fruits:\n"
        << "=================\n";
    for (const auto& f : vf)
        std::cout << f.name << '\n';
    std::cout << '\n';

    // should be same as vector but in lexicographic order
    std::cout << "Set of fruits:\n"
        << "==============\n";
    for (const auto& f : produce)
        std::cout << f->name << '\n';
    std::cout << '\n';
    

}