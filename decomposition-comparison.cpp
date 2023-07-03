#include <tuple>

struct Test { int getA() const { return 1; } };

template <typename>
struct DecompSFINAE {};

template <typename Return_, typename Class_, typename ... Args_>
struct DecompSFINAE<Return_ (Class_::*) (Args_ ...)> {
    using Return = Return_;
    using Class  = Class_;
    using Arguments = std::tuple<Args_ ...>;
};

template <typename Return_, typename Class_, typename ... Args_>
struct DecompSFINAE<Return_ (Class_::*) (Args_ ...) const> {
    using Return = Return_;
    using Class  = Class_;
    using Arguments = std::tuple<Args_ ...>;
};


template <auto ptr>
struct DecompSFINAEv2 : DecompSFINAE<decltype(ptr)> {};


template <typename Return_, typename Class_, typename ... Args_>
struct DecompCTAD
{
    using Return = Return_;
    using Class  = Class_;
    using Arguments = std::tuple<Args_ ...>;

    template <typename R, typename C, typename ... A>
    explicit DecompCTAD(R (C::*) (A ...)) {}

    template <typename R, typename C, typename ... A>
    explicit DecompCTAD(R (C::*) (A ...) const) {}
};


template <typename Return, typename Class, typename ... Arguments>
DecompCTAD(Return (Class::*) (Arguments ...) ) -> DecompCTAD<Return, Class, Arguments ...>;

template <typename Return, typename Class, typename ... Arguments>
DecompCTAD(Return (Class::*) (Arguments ...) const) -> DecompCTAD<Return, Class, Arguments ...>;



int main()
{
    using ctad_ver = decltype(DecompCTAD(&Test::getA))::Return;
    using sfinae_ver = DecompSFINAE<decltype(&Test::getA)>::Return;
    using sfinae_ver2 = DecompSFINAEv2<&Test::getA>::Return;

    ctad_ver x = 1;
    sfinae_ver y = 1;
    sfinae_ver2 z = 1;
}
