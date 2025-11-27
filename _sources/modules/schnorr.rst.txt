Schnorr Signature Module
========================

Overview
--------

The *Schnorr Signature* module provides a digital signature scheme for authenticating messages (in this project, for signing transactions). Schnorr signatures allow a user (such as a wallet) to sign a message with a private key such that anyone with the corresponding public key can verify the signature.

This implementation uses the **key-prefixed Schnorr variant**, which includes the public key in the hash computation of the signature. This design enhances security and helps prevent specific attacks (such as rogue key substitution).

In the blockchain context, every transaction is signed with a Schnorr signature: the sender's wallet signs the transaction data, and the blockchain verifies the signature before accepting it into the pending pool.

Usage
-----

To use this module, developers follow a simple workflow:

1. **Key Generation**
   Call the key generation function to produce a private key `x` and corresponding public key `P`.

2. **Signing a Message**
   When creating a transaction, the wallet signs the message using the private key. The function returns a signature object containing components `R` and `s`.

3. **Verifying a Signature**
   The blockchain uses the verification function with the public key `P`, the message, and the signature. If the result is `true`, the transaction is considered valid.

The module internally performs all mathematical operations using the GMP library for big integer arithmetic, but the API is clean and simple: developers interact with high-level C++ interfaces.

Features
--------

- Key-prefixed Schnorr signatures (public key included in the challenge hash)
- Secure digital signing and verification for blockchain transactions
- C++20 headers-only implementation
- Uses GMP for arbitrary-precision integer operations
- Modular, reusable design

Repository
----------

Source code and documentation are available at:

https://github.com/gdaneek/schnorr-sign
