# RSA in C++

## Overview
This project provides a header-only C++ implementation of the RSA public-key cryptography algorithm, utilizing the Boost library for high-precision integer calculations that involve large prime numbers.

## Features
- **Encryption and Decryption**: Encrypts messages using a public key and decrypts them with the corresponding private key.
- **Arbitrary Key Size**: Default key size is 512 bits and perfroms fast. Any larger key size can be set by the constructor.
- **Large Integer Support**: Leverages Boost.Multiprecision for robust handling of large integers crucial for RSA security.
- **Basic Error Handling**: Includes some error handling to improve user experience.

## Dependencies
- A C++ compiler with support for C++20 support or later (I used the GNU C++ compiler)
- The Boost [Library](https://www.boost.org/users/download/)

## Installation
1. Download the Boost library from the release page
2. Extract the compressed file to a directory which will be the installation directory eventually
3. In the root folder of the extracted file, open Terminal (Windows 11) or Command Line and run,
```
C:\boost_1_52_0> bootstrap.bat mingw
C:\boost_1_52_0> b2 toolset=gcc
```
4. Add its location to `C/C++: Edit Configurations (JSON)` file in VSCode like so:
```
"includePath": ["${workspaceFolder}/**",
                "D:/boost-extracted/boost_1_85_0/**"
]
```
5. Compile it using the following command:
```
g++ driver.cpp -std=c++20 -I D:\boost-extracted\boost_1_85_0 -L D:\boost-extracted\boost_1_85_0\stage\lib -lboost_random-mgw13-mt-x64-1_85
```

## Overcome Challenges
- Primality test function used to fail to work with key sizes larger than 64 bits. It now works with any arbitrary key size.
- Modular exponentiation function used to fail to work with key sizes larger than 16 bits. It now works with any arbitrary key size.

## Disclaimer for RSA Implementation

The RSA encryption algorithm implementation provided in this repository is for educational and research purposes only. It is not recommended to use this implementation in production environments or in any situation where strong security is required.

While every effort has been made to follow cryptographic best practices, the author of this repository does not guarantee the security of the implementation. Cryptography is a complex and nuanced field, and the security of cryptographic implementations can be compromised by subtle issues that are not apparent at the time of writing.

Users are advised to use well-established libraries and implementations that have been thoroughly vetted by the cryptographic community for any applications requiring high security.

By using or referencing the code in this repository, you acknowledge that you do so at your own risk, and you are responsible for understanding the risks involved in cryptographic implementations.

The author of this repository accepts no liability for any damage or loss arising from the direct or indirect use of the provided code.
