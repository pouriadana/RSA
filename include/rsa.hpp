#include <array>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <string>
#include <string_view>
#include <vector>

using cpp_int = boost::multiprecision::cpp_int;
class RSA {
public:
    RSA(unsigned int key_size = 16) 
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
        totient = (p - 1) * (q - 1);
        _setEncryptionExponent();
        _setDecryptionExponent();
    }

    // get functions
    cpp_int getP() const { return p; }
    cpp_int getQ() const { return q; }
    const std::array<cpp_int, 2> getPublicKey() const 
    {
        std::array public_key {encryption_exponent, totient};
        return public_key;
    }

    const std::vector<cpp_int> encrypt(std::string_view plaintext)
    {
        std::vector<cpp_int> ciphertext{}; 
        for (const auto& item : plaintext)
        {
            ciphertext.push_back(_modularPow(item, encryption_exponent, modulus_n));
        }
        return ciphertext;
    }

    std::string decrypt(std::vector<cpp_int> cipher)
    {
        std::string deciphered{""};
        for (const auto& item : cipher)
        {
            deciphered += static_cast<int>(_modularPow(item, decryption_exponent, modulus_n));
        }
        return deciphered;
    }

private:
    cpp_int p{"0"};                     // two prime integers each with the size of key_size / 2
    cpp_int q{"0"};
    cpp_int modulus_n{"0"};             // modulus n; part of encryption/decryption keys
    cpp_int totient{"0"};               // totient (phi of n) used in calculating encryption/decryption key values
    cpp_int encryption_exponent{"0"};   // encryption exponent used to encrypt plaintext messages
    cpp_int decryption_exponent{"0"};   // decryption exponent used to decrypt ciphertext

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
    cpp_int _chooseRandom(const cpp_int& lower_bound, const cpp_int& upper_bound)
    {
        static boost::random::random_device rd;
        static boost::random::mt19937 eng(rd());
        boost::random::uniform_int_distribution<cpp_int> select(lower_bound,upper_bound);

        return select(eng);
    }

    // TODO
    // Add a primality test function that supports 128 bit and above
    bool _isPrime(const cpp_int& n)
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

    // greatest common divisor function
    cpp_int _gcd(cpp_int a, cpp_int b)
    {
        cpp_int r{a % b};
        while (r)
        {
            a = b;
            b = r;
            r = a % b;
        }
        return b;
    }

    // encryption exponent function
    void _setEncryptionExponent()
    {
        encryption_exponent = _chooseRandom(cpp_int{"2"}, totient - 1);
        while (_gcd(encryption_exponent, totient) != 1)
        {
            encryption_exponent = _chooseRandom(cpp_int{"2"}, totient);
        }
    }

    // decryption exponent function
    void _setDecryptionExponent()
    {
        cpp_int multiplier{"2"};
        while ((multiplier * encryption_exponent % totient) != 1)
        {
            ++multiplier;
        }
        decryption_exponent = multiplier;
    }

    // modular exponentiation; key part of encryption/decryption calculations
    cpp_int _modularPow(cpp_int message, cpp_int exponent, cpp_int modulus_n)
    {
        boost::multiprecision::cpp_int c{"1"};
        for (cpp_int e{0}; e < exponent; ++e)
        {
            c = message * c % modulus_n;
        }
        return c;
    }
};