Merkle Tree Module
==================

Overview
--------

The *Merkle Tree* module implements a binary Merkle tree structure used to aggregate and hash a collection of data entries (such as transactions). A Merkle tree computes a single **root hash** that authenticates all the entries (leaves) in the tree. This module is utilized in the blockchain to produce a Merkle root for the transactions included in each block (the root is stored in the block header). By using a Merkle tree, the blockchain can efficiently verify that a given transaction is included in a block without storing all transaction data in the header.

Usage
-----

To use the Merkle tree module, a developer provides a collection of data items or pre-hashed values to the tree constructor or builder function. The module will then calculate the Merkle root for those items.

In this project’s context, the blockchain passes the list of transactions (or their hashes) from the pending transaction pool into the Merkle tree when creating a new block. The resulting root hash is accessible via the module’s interface (for example, via a function call or a member variable after construction) and is inserted into the block header.

The module can be configured to use:
- the default hash algorithm (**Streebog**, GOST R 34.11-2018)
- a default concatenation strategy (simple byte-wise concatenation of child hashes)

Advanced users may substitute alternative hashing algorithms or concatenation functions, provided they meet the required interface contracts. The Merkle tree implementation is templated and designed for maximum flexibility.

Features
--------

- Static-size binary Merkle tree
- Configurable hashing and concatenation
- Designed for use with cryptographic data (e.g., transactions, signatures)
- C++20 with template-based generic interfaces

Repository
----------

Source code and examples are available at:

https://github.com/gdaneek/merkle-tree
