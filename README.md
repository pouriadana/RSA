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

## Disclaimer for RSA Implementation

The RSA encryption algorithm implementation provided in this repository is for educational and research purposes only. It is not recommended to use this implementation in production environments or in any situation where strong security is required.

While every effort has been made to follow cryptographic best practices, the author of this repository does not guarantee the security of the implementation. Cryptography is a complex and nuanced field, and the security of cryptographic implementations can be compromised by subtle issues that are not apparent at the time of writing.

Users are advised to use well-established libraries and implementations that have been thoroughly vetted by the cryptographic community for any applications requiring high security.

By using or referencing the code in this repository, you acknowledge that you do so at your own risk, and you are responsible for understanding the risks involved in cryptographic implementations.

The author of this repository accepts no liability for any damage or loss arising from the direct or indirect use of the provided code.
