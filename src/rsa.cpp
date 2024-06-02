#include <boost/multiprecision/cpp_int.hpp>
#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using cpp_int = boost::multiprecision::cpp_int;

cpp_int modularPow(cpp_int message, cpp_int encryption_exponent, cpp_int modulus_n);
cpp_int encrypt(cpp_int plaintext, cpp_int e, cpp_int mod);
cpp_int decrypt(cpp_int cipher, cpp_int d, cpp_int mod);
void encrypt_string(std::string_view plaintext, std::vector<cpp_int>& ciphertext, cpp_int e, cpp_int m);
std::string decrypt_string(const std::vector<cpp_int>& ciphertext, cpp_int d, cpp_int m);

bool isPrime(int n);
int gcd(int a, int b);

int main()
{
    std::cout << "Enter a prime number for p: ";
    int p; // must use a bigger type
    std::cin >> p;
    while (!isPrime(p))
    {
        std::cout << "Please select a prime number: ";
        std::cin >> p;
    }

    std::cout << "Enter a prime number for q: ";
    int q; // must use a bigger type
    std::cin >> q;
    while (!isPrime(q))
    {
        std::cout << "Please select a prime number: ";
        std::cin >> q;
    }

    cpp_int modulus_n{p * q};
    // std::cout << std::format("n is {}\n", modulus_n);
    std::cout << "n is " << modulus_n << '\n';

    cpp_int phi_of_n{(p-1) * (q-1)}; // totient
    // std::cout << std::format("totient is {}\n", phi_of_n);
    std::cout << "totient is " << phi_of_n << '\n';

    // create a vector of candidates for e (encryption exponent)
    std::vector<cpp_int> e_candidates{};
    for (int counter{2}; counter < phi_of_n; ++counter)
    {
        if (gcd(counter, phi_of_n) == 1)
        {
            e_candidates.push_back(counter);
        }
    }
    std::cout << "Candidates for e: ";
    for (const auto item : e_candidates)
    {
        std::cout << item << ' ';
    }

    std::cout << "\nSelect a value for e from the preceding list of values: ";
    cpp_int encryption_exponent;
    std::cin >> encryption_exponent;
    bool valid_choice{false};
    for (const auto item : e_candidates)
    {
        if (item == encryption_exponent)
        {
            valid_choice = true;
        }
    }
    while (!valid_choice)
    {
        std::cout << "Selected value is not from the list.\nPlese select a value from the list:\n";
        std::cout << "Candidates for e: ";
        for (const auto item : e_candidates)
        {
            std::cout << item << ' ';
        }
        std::cin >> encryption_exponent;
        for (const auto item : e_candidates)
        {
            if (item == encryption_exponent)
            {
                valid_choice = true;
            }
        }
    }
    std::cout << "Public key is (" << encryption_exponent << ", " << modulus_n << ")\n";

    // select decryption exponenet such that (d*e) mod phi_of_n == 1
    cpp_int d;
    bool sentinel{true}; // controls if a candidate for d is found
    for (int counter{2} ; sentinel; ++counter)
    {
        if ((counter * encryption_exponent % phi_of_n) == 1)
        {
            d = counter;
            sentinel = false;
        }
    }
    
    std::cout << "Candidate for d: " << d << '\n';
    std::cout << "Select a value for d--either the d candidate above or d plus a multiple of the totient: ";
    for (int count{1}; count <= 5; ++count)
    {
        std::cout << d + (count * phi_of_n) << ' ';
    }
    std::cout << "...\n-->";
    std::cin >> d;
    std::cout << "Private key is (" << d << ", " << modulus_n << ")\n";

    std::cout << "Enter a non-negative number less than " << modulus_n << " to encrypt: ";
    cpp_int plain_text;
    std::cin >> plain_text; // check for validity
    while (plain_text < 0 || plain_text >= modulus_n)
    {
        std::cout << "Please enter a positive numner less than " << modulus_n << ": ";
        std::cin >> plain_text;
    }

    cpp_int cipher_text{encrypt(plain_text, encryption_exponent, modulus_n)};
    std::cout << "The cipher text is: " << cipher_text << '\n';

    cpp_int decrypted{decrypt(cipher_text, d, modulus_n)};
    std::cout << "The decrypted text is: " << decrypted << '\n';

    std::cout << "Enter a string to encrypt: ";
    std::cin.ignore();
    std::string string_plaintext;
    std::getline(std::cin, string_plaintext);

    std::vector<cpp_int> string_ciphertext{};
    encrypt_string(string_plaintext, string_ciphertext, encryption_exponent, modulus_n);
    std::string encrypted_string{};
    for (const auto character : string_ciphertext)
    {
        encrypted_string += static_cast<int>(character);
    }
    std::cout << encrypted_string << '\n';

    std::cout << decrypt_string(string_ciphertext, d, modulus_n) << '\n';
}

bool isPrime(int n)
{
    std::vector<bool> primes{};
    for (int counter{0}; counter <= n; ++counter)
    {
        primes.push_back(true);
    }

    for (int i{2}; i <= n; ++i)
    {
        if (primes[i] == true)
        {
        for (int j{2}; j <= n; ++j)
            {
                int z{i * j};
                if (z <= n)
                {
                    primes[z] = false;
                }
            }
        }
    }
    return primes[n];
}

int gcd(int a, int b)
{
    int r{a % b};
    while (r)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

cpp_int modularPow(cpp_int message, cpp_int encryption_exponent, cpp_int modulus_n)
{
    boost::multiprecision::cpp_int c{1};
    for (int e{0}; e < encryption_exponent; ++e)
    {
        c = message * c % modulus_n;
    }
    return c;
}

cpp_int encrypt(cpp_int plaintext, cpp_int e, cpp_int mod)
{
    return modularPow(plaintext, e, mod);
}

cpp_int decrypt(cpp_int cipher, cpp_int d, cpp_int mod)
{
    return modularPow(cipher, d, mod);
}

void encrypt_string(std::string_view plaintext, std::vector<cpp_int>& ciphertext, cpp_int e, cpp_int m)
{
    for (const auto& character : plaintext)
    {
        ciphertext.push_back(encrypt(character, e, m));
    }
}
std::string decrypt_string(const std::vector<cpp_int>& ciphertext, cpp_int d, cpp_int m)
{
    std::string s{};
    for (const auto& ascii : ciphertext)
    {
        s += static_cast<int>(decrypt(ascii, d, m));
    }
    return s;
}