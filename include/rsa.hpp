#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using cpp_int = boost::multiprecision::cpp_int;
constexpr unsigned int key_length{1024};
class RSA {
public:
    RSA() 
    {
        
    }
private:
    // two prime integers each with the size of key_length / 2
    cpp_int p{"0"};
    cpp_int q{"0"};

    // auxilary functions
    //
    // exponentiation function
    cpp_int _power(cpp_int n, int exponent)
    {
        if (exponent == 0)
        {
            return cpp_int{"1"};
        }
        return n * _power(n, exponent - 1);
    }

    // random number selection function
    cpp_int _chooseRandom(unsigned int lower_bound, unsigned int upper_bound)
    {
        boost::random::random_device rd;
        boost::random::mt19937 eng(rd());
        boost::random::uniform_int_distribution<cpp_int> select(lower_bound,upper_bound);

        return select(eng);
    }
};