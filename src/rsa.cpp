#include <format>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int modularPow(int message, int encryption_exponent, int modulus_n);
int encrypt(int plaintext, int e, int mod);
int decrypt(int cipher, int d, int mod);
void encrypt_string(std::string_view plaintext, std::vector<int>& ciphertext, int e, int m);
std::string decrypt_string(const std::vector<int>& ciphertext, int d, int m);

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

    int modulus_n{p * q};
    std::cout << std::format("n is {}\n", modulus_n);

    int phi_of_n{(p-1) * (q-1)};
    std::cout << std::format("totient is {}\n", phi_of_n);

    // create a vector of candidates for e (encryption exponent)
    std::vector<int> e_candidates{};
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
    int encryption_exponent;
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
    // select a value d such that (d*e) mod phi_of_n == 1
    int d;
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
    std::cin >> d;

    std::cout << "Enter a non-negative number less than " << modulus_n << " to encrypt: ";
    int plain_text;
    std::cin >> plain_text; // check for validity
    while (plain_text < 0 || plain_text >= modulus_n)
    {
        std::cout << "Please enter a positive numner less than " << modulus_n << ": ";
        std::cin >> plain_text;
    }

    int cipher_text{encrypt(plain_text, encryption_exponent, modulus_n)};
    std::cout << "The cipher text is: " << cipher_text << '\n';

    int decrypted{decrypt(cipher_text, d, modulus_n)};
    std::cout << "The decrypted text is: " << decrypted << '\n';

    std::cout << "Enter a string to encrypt: ";
    std::cin.ignore();
    std::string string_plaintext;
    std::getline(std::cin, string_plaintext);

    std::vector<int> string_ciphertext{};
    encrypt_string(string_plaintext, string_ciphertext, encryption_exponent, modulus_n);
    std::string encrypted_string{};
    for (const auto character : string_ciphertext)
    {
        encrypted_string += character;
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

int modularPow(int message, int encryption_exponent, int modulus_n)
{
    int c{1};
    for (int e{0}; e < encryption_exponent; ++e)
    {
        c = message * c % modulus_n;
    }
    return c;
}

int encrypt(int m, int e, int mod)
{
    return modularPow(m, e, mod);
}

int decrypt(int cipher, int d, int mod)
{
    return modularPow(cipher, d, mod);
}

void encrypt_string(std::string_view plaintext, std::vector<int>& ciphertext, int e, int m)
{
    for (const auto& character : plaintext)
    {
        ciphertext.push_back(encrypt(character, e, m));
    }
}
std::string decrypt_string(const std::vector<int>& ciphertext, int d, int m)
{
    std::string s{};
    for (const auto& ascii : ciphertext)
    {
        s += decrypt(ascii, d, m);
    }
    return s;
}