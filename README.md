# RSA in C++

## Overview
This project provides a C++ implementation of the RSA public-key cryptography algorithm, utilizing the Boost.Multiprecision library's `cpp_int` class for high-precision integer calculations that involve large prime numbers.

## Features
- **Encryption and Decryption**: Encrypts messages using a public key and decrypts them with the corresponding private key.
- **Large Integer Support**: Leverages Boost.Multiprecision for robust handling of large integers crucial for RSA security.
- **Basic Error Handling**: Includes some error handling to improve user experience.

## Dependencies
- A C++ compiler with support for C++11 or later (I used the GNU C++ compiler)
- The Boost.Multiprecision [library](https://github.com/boostorg/multiprecision)

## Installation
1. Download the Boost.Multiprecision library from the release page
2. Add its location to `C/C++: Edit Configurations (JSON)` file in VSCode like so:
```
"includePath": ["${workspaceFolder}/**",
                "C:\\Users\\YOURNAME\\Downloads\\Compressed\\multiprecision-Boost_1_85_0\\include\\**"
]
```
3. Compile it using the following command:
```
g++ -std=c++20 rsa.cpp -I C:\Users\YOURNAME\Downloads\Compressed\multiprecision-Boost_1_85_0\include
```
