#include <algorithm>
#include <vector>
#include <iostream>
#include <ostream>



class Test
{
    double a_;
    int b_;

public:
    Test(double a, int b) : a_{a}, b_{b} { }
    double getA() const { return a_; }
    int getB() const { return b_; }
    int possibleSelect() const { return a_ + b_; }
};
std::ostream& operator<<(std::ostream& o, const Test& t)
{
    return o << "Test(" << t.getA() << ", " << t.getB() << ")";
}


int main()
{
    std::vector<Test> v{
        {12.2,2}, {20.4,43}, {3.1,64}, {210.32,6}, {0.11,3}
    };

    std::sort(v.begin(), v.end(), [](const Test& t1, const Test& t2) {
        return t1.getA() < t2.getA();
    });

    for (const Test& t : v) { std::cout << t << "\n"; }

    std::cout << "---\n";

    std::sort(v.begin(), v.end(), [](const Test& t1, const Test& t2) {
        return t1.getB() < t2.getB();
    });

    for (const Test& t : v) { std::cout << t << "\n"; }
}
