Proof-of-Work Blockchain Module
===============================

Overview
--------

The *PoW blockchain* module is the heart of the project, integrating all other modules to simulate a working blockchain with a Proof-of-Work consensus algorithm. It provides a minimal yet functional blockchain that demonstrates how transactions are validated, blocks are mined, and the chain is extended over time.

This module also includes:
- A simple **pseudo-random number generator (PRNG)** using hash functions
- A configurable **Proof-of-Work (PoW)** implementation
- Modular architecture built around templated C++20 components

Key Components
--------------

- **Transaction**
  Encapsulated in a `Transaction` struct that includes raw byte data and a Schnorr signature. These are simplified for demonstration and don’t include fields like recipients or amounts.

- **Block**
  Represented by a `Block` structure with:
  - A vector of `Transaction`s
  - A header containing version, previous hash, Merkle root, timestamp, difficulty target, and nonce

- **Wallet**
  A class that generates a Schnorr key pair and creates signed transactions. Wallets feed signed data into the blockchain.

- **Miner**
  Attempts to solve the PoW puzzle by varying the nonce and hashing the block header until the hash meets a target difficulty. Once successful, it submits the mined block to the chain.

- **Transaction Pool**
  Maintains a list of submitted and verified transactions not yet included in a block. Simple `std::vector`-based implementation.

- **Blockchain (Chain)**
  Stores the full sequence of mined blocks. Implemented as a vector of blocks with linkage via each block’s `previous hash` field. It verifies transaction signatures, builds Merkle roots, and exposes interfaces to the wallet and miner.

Proof-of-Work and RNG
---------------------

- **Proof-of-Work**
  Target difficulty is defined by the number of leading zero bits required in a block hash. Mining is done by brute-force search over nonces, checking the hash of each header.

- **HashRNG**
  A generic, hash-based random number generator used for generating nonce values or Schnorr ephemeral keys. It hashes a seed and counter to derive new values.

Usage
-----

1. **Submitting Transactions**
   - A `Wallet` signs data to create a `Transaction`.
   - The blockchain verifies the signature.
   - If valid, the transaction is added to the pool.

2. **Mining a Block**
   - A `Miner` fetches pending transactions.
   - It constructs a block, computes the Merkle root, and fills the block header.
   - The nonce is varied until the hash meets the difficulty requirement.
   - Once successful, the block is submitted to the blockchain.

3. **Chain Verification**
   - Each block's header includes the hash of the previous block.
   - Blocks are validated and linked in sequence.
   - The integrity and continuity of the chain can be confirmed by tracing the `previous` fields.

Design Notes
------------

- Emphasizes modularity and composability
- Designed for learning and experimentation
- Lacks networking, persistent storage, or economic incentives
- Not suitable for production use

Dependencies
------------

This module directly or indirectly depends on:
- `streebog-hash` – for PoW and data hashing
- `merkle-tree` – to summarize transactions in each block
- `schnorr-sign` – to sign and validate transactions
- GMP – required by the Schnorr signature library

All modules are managed as Git submodules and connected via CMake.
