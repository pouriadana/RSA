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
    RSA(unsigned int key_size = 512) 
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
            p = _chooseRandom(lower_bound, upper_bound);
        }
        while (!_isPrime(q))
        {
            q = _chooseRandom(lower_bound, upper_bound);
        }
        modulus_n = p * q;
        totient = _lcm(p - 1, q - 1);
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
        // Miller-Rabin
        // First rewrite n-1 as 2^s * d;
        if (n % 2 == 0)
        {
            return false;
        }

        unsigned long long s{_log2(n - 1) - 1};
        while (s > 0)
        {
            if ((n - 1) % _power(cpp_int{"2"}, s) == 0)
            {
                break;
            }
            --s;
        }
        cpp_int d{(n - 1) / _power(cpp_int{"2"}, s)};

        int precision{40}; // the number of times a number "a" is selected such that 2 <= a <= n - 2 and is tested for compositeness
        while (precision--)
        {
            cpp_int a{_chooseRandom(cpp_int{"2"}, n - 2)};
            bool possible{false};
            for (unsigned long long count{0}; count < s; ++count)
            {
                cpp_int z{_modularPow(a, _power(cpp_int{"2"}, count) * d, n)};
                if (z == n - 1 || z == 1)
                {
                    possible = true;
                }
            }
            if (!possible)
            {
                return false;
            }
        }
        return true;
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
        // Extended Euclidean algorithm
        cpp_int old_r{encryption_exponent};
        cpp_int r{totient};
        cpp_int old_s{"1"}, s{"0"};
        cpp_int old_t{"0"}, t{"1"};

        while (r)
        {
            cpp_int q{old_r / r};

            cpp_int temp{r};
            r = old_r - q * temp;
            old_r = temp;

            temp = s;
            s = old_s - q * temp;
            old_s = temp;

            temp = t;
            t = old_t - q * t;
            old_t = temp;
        }
        decryption_exponent = old_s;

        while (decryption_exponent < 0)
        {
            decryption_exponent += totient;
        }
    }

    // modular exponentiation; key part of encryption/decryption calculations
    cpp_int _modularPow(cpp_int message, cpp_int exponent, cpp_int modulus_n)
    {
        cpp_int result{"1"};
        message = message % modulus_n;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                result = (result * message) % modulus_n;
            }
            exponent = exponent / 2;
            message = (message * message) % modulus_n;
        }
        return result;
    }

    // least common multiplier calculator function for Carmichael's totient function
    cpp_int _lcm(cpp_int n, cpp_int m)
    {
        return (n * m) / _gcd(n, m);
    }

    // Takes the log base 2 of a number e.g _log2(8) -> 3
    unsigned long long _log2(cpp_int n)
    {
        unsigned long long result{0};
        while (n > 1)
        {
            n >>= 1; // same as dividing by 2
            ++result; 
        }
        return result;
    }
};