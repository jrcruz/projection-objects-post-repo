#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <ostream>
#include <cmath>
#include <utility>



class Test
{
    double a_;
    int b_;

public:
    Test(double a, int b) : a_{a}, b_{b} { }
    double getA() const { return a_; }
    int getB() const { return b_; }
};
std::ostream& operator<<(std::ostream& o, const Test& t)
{
    return o << "Test(" << t.getA() << ", " << t.getB() << ")";
}


double distance(const Test& t1, const Test& t2) {
    return std::hypot(t2.getA() - t1.getA(), t2.getB() - t1.getB());
}


template <auto Projection, typename Comparator = std::less<>, typename ... ProjArgs>
auto projection(ProjArgs&& ... args)
{
    return [... args = std::forward<decltype(args)>(args)](const auto& x1, const auto& x2) {
        return Comparator{}(
            std::invoke(Projection, x1, std::forward<decltype(args)>(args) ...),
            std::invoke(Projection, x2, std::forward<decltype(args)>(args) ...));
    };
}


int main()
{
    std::vector<Test> v{
        {12.2,2}, {20.4,43}, {3.1,64}, {210.32,6}, {0.11,3}
    };
    Test tx{1.0,1};

    std::sort(v.begin(), v.end(), projection<&Test::getA>());
    for (const Test& t : v) { std::cout << t << " " << distance(tx, t) << "\n"; }
    std::cout << "\n";

    auto m1 = std::max_element(v.cbegin(), v.cend(), projection<&Test::getB>());
    std::cout << "max getB: " << *m1 << "\n";
    std::cout << "\n";

    auto m2 = std::min_element(v.cbegin(), v.cend(), projection<distance>(tx));
    std::cout << "min distance to tx: " << *m2 << "\n";
    std::cout << "\n";

    std::sort(v.begin(), v.end(), projection<distance, std::greater<>>(tx));
    for (const Test& t : v) { std::cout << t << " " << distance(tx, t) << "\n"; }
    std::cout << "\n";
}
