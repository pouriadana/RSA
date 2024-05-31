#include <array>
#include <format>
#include <iostream>
#include <vector>


bool isPrime(int n);

int main()
{
    std::cout << "Enter a prime number for p: ";
    unsigned int p; // must use a bigger type
    std::cin >> p;

    std::cout << "Enter a prime number for q: ";
    unsigned int q; // must use a bigger type
    std::cin >> q;

    unsigned int modulus_n{p * q};
    std::cout << std::format("n is {}\n", modulus_n);

    unsigned int phi_of_n{(p-1) * (q-1)};
    std::cout << std::format("totient is {}\n", phi_of_n);
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