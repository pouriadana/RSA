#include <array>
#include <format>
#include <iostream>
#include <vector>


bool isPrime(int n);
int gcd(int a, int b);

int main()
{
    std::cout << "Enter a prime number for p: ";
    int p; // must use a bigger type
    std::cin >> p;

    std::cout << "Enter a prime number for q: ";
    int q; // must use a bigger type
    std::cin >> q;

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