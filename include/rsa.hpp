#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

using cpp_int = boost::multiprecision::cpp_int;
class RSA {
public:
    RSA(unsigned int key_size = 64) 
    {
        cpp_int lower_bound{_power(cpp_int{"2"}, key_size / 2 - 1)};
        cpp_int upper_bound{_power(cpp_int{"2"}, key_size / 2)};
        p = _chooseRandom(lower_bound, upper_bound);
        q = _chooseRandom(lower_bound, upper_bound);
        while (p == q) // make sure two numbers aren't the same
        {
            p = _chooseRandom(lower_bound, upper_bound);
            q = _chooseRandom(lower_bound, upper_bound);
        }
        while (!_isPrime(p))
        {
            //std::cout << "p is " << p << '\n';
            //std::cout << "p is not prime\n";
            p = _chooseRandom(lower_bound, upper_bound);
        }
        while (!_isPrime(q))
        {
            //std::cout << "q is not prime\n";
            q = _chooseRandom(lower_bound, upper_bound);
        }
        modulus_n = p * q;
        phi_of_n = (p - 1) * (q - 1);
    }

    // get functions
    cpp_int getP() const { return p; }
    cpp_int getQ() const { return q; }
private:
    // two prime integers each with the size of key_size / 2
    cpp_int p{"0"};
    cpp_int q{"0"};

    // modulus n; part of encryption/decryption keys
    cpp_int modulus_n{"0"};

    // totient (phi of n) used in calculating encryption/decryption key values
    cpp_int phi_of_n{"0"};

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
    cpp_int _chooseRandom(cpp_int lower_bound, cpp_int upper_bound)
    {
        static boost::random::random_device rd;
        static boost::random::mt19937 eng(rd());
        boost::random::uniform_int_distribution<cpp_int> select(lower_bound,upper_bound);

        return select(eng);
    }

    // TODO
    // Add a primality test function that supports 128 bit and above
    bool _isPrime(cpp_int n)
    {
        bool is_prime{true};
        cpp_int n_sqrt{boost::multiprecision::sqrt(n)};
        for (cpp_int div{"2"}; div <= n_sqrt; ++div)
        {
            if (n % div == 0)
            {
                is_prime = false;
                break;
            }
        }
        return is_prime;
    }
};