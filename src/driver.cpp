#include <iostream>
#include "../include/rsa.hpp"

int main()
{
    RSA rsa;
    std::cout << rsa.decrypt(rsa.encrypt("Goodbye!"));
}