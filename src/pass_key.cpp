// PassKey Idiom
// Alternative to friend.

// SOURCES:
// http://arne-mertz.de/2016/10/passkey-idiom/
// http://stackoverflow.com/questions/3217390/clean-c-granular-friend-equivalent-answer-attorney-client-idiom

#include <iostream>

template <typename T>
class PassKey
{
    // friendship is not transitive
    friend T;

private:
    // default constructor has to be manualy defined otherwise = default
    // would allow aggregate initialization to bypass default constructor

    // both, default and copy constructors have to be user-defined
    // otherwise are public by default
    PassKey()
    {
        std::cout << "PassKey default constructor call" << std::endl;
    }

    // copy constructor can be deleted entirely, it just allows delegation
    PassKey(const PassKey &)
    {
        std::cout << "PassKey copy constructor call" << std::endl;
    }
};

class Caller;

class Callee
{
public:

    // this method can be called only by someone who can construct the passkey
    void call(int argument, PassKey<Caller>)
    {
        std::cout << "Only Caller can call this method" << std::endl;
    }

    // this method can be called by someone who has access to the passkey
    void delegated_call(int argument, const PassKey<Caller> &)
    {
        std::cout << "Someone with an instance of PassKey<Caller> can call"
                  << std::endl;
    }
};

// only Caller can make an instance or copy of PassKey<Caller>
class Caller
{
public:
    void run()
    {
        // C++11 allows us to call short initializer
        // in order to create the passkey
        callee.call(0, {});
    }

    auto provide_passkey()
    {
        return PassKey<Caller>();
    }

private:
    Callee callee;
};

auto main() -> int
{
    Caller caller;
    caller.run();

    // not allowed
    // Callee callee;
    // callee.call(0, {});

    // passkey delegation
    Callee callee;
    callee.delegated_call(0, caller.provide_passkey());

    return 0;
}
