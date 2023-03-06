# HMAC-SHA1 in C
This repository contains an implementation of the HMAC-SHA1 algorithm in C. HMAC-SHA1 is a cryptographic hash function that uses a secret key to produce a message authentication code (MAC) for verifying the integrity and authenticity of a message.

## Getting Started

To use this implementation, clone this repository to your local machine and compile the `hmac_sha1.c` file:

```bash
git clone https://github.com/your-username/hmac-sha1-c.git
cd hmac-sha1-c
gcc hmac_sha1.c -o hmac_sha1 
```

## Usage
To calculate the HMAC-SHA1 message authentication code for a given message and key, run the hmac_sha1 executable with the message and key as arguments:

```bash
./hmac_sha1 "Hello, world!" "secret"
```

This will output the HMAC-SHA1 message authentication code in hexadecimal format.


## Implementation Details
The implementation uses the OpenSSL library to access the HMAC-SHA1 function. The hmac_sha1 function takes two arguments, message and key, and returns a pointer to the HMAC-SHA1 message authentication code. The hmac_sha1 function uses the EVP_sha1() function to specify the SHA-1 hash function to be used.

The main function in hmac_sha1.c demonstrates how to use the hmac_sha1 function to calculate the HMAC-SHA1 message authentication code for a given message and key.


The implementation uses the OpenSSL library to access the HMAC-SHA1 function. The hmac_sha1 function takes two arguments, message and key, and returns a pointer to the HMAC-SHA1 message authentication code. The hmac_sha1 function uses the EVP_sha1() function to specify the SHA-1 hash function to be used.

The main function in hmac_sha1.c demonstrates how to use the hmac_sha1 function to calculate the HMAC-SHA1 message authentication code for a given message and key.

## License
This implementation of the HMAC-SHA1 algorithm is provided under the MIT License. Feel free to use it in your own projects or modify it to suit your needs.



### Reference: (FIPS-198):
1. http://csrc.nist.gov/publications/fips/fips198/fips-198a.pdf
2. http://csrc.nist.gov/publications/fips/fips198-1/FIPS-198-1_final.pdf
