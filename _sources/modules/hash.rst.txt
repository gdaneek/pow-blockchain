Streebog Hash Module (GOST R 34.11-2018)
========================================

Overview
--------

The *Streebog hash* module implements the Russian cryptographic hash standard **GOST R 34.11-2018**, also known as *Streebog*. This algorithm supports both 512-bit and 256-bit hash output modes, with the 256-bit variant implemented via output truncation.

This module is used as the primary hash function throughout the blockchain system, powering:
- Transaction hashing
- Merkle tree node computations
- Proof-of-Work hash puzzles
- Random number generation (PRNG)

Usage
-----

To use the Streebog hash module, instantiate the hash object (or use it via the provided callable interface) and invoke it on a binary buffer or container. The hash function returns either a 512-bit or truncated 256-bit digest, depending on configuration.

The module is designed with flexibility in mind:
- It works smoothly with standard C++ containers (`std::vector`, `std::array`, `std::string`)
- It supports custom data structures via a generic *Concatenator* concept, which extracts bytes from structured inputs

Typical use cases in this project include:
- Creating unique transaction IDs by hashing message+signature content
- Building Merkle trees by hashing concatenated child nodes
- Generating block hashes for PoW mining

Features
--------

- Fully standards-compliant implementation of GOST R 34.11-2018
- Optimized for performance with precomputed tables and unrolled operations
- Supports both 512-bit and 256-bit modes
- Generic and composable API
- Integrates with other cryptographic modules in the project

Repository
----------

Source code and examples are available at:

https://github.com/gdaneek/streebog-hash
