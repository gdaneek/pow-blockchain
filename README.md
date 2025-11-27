# Proof-of-Work Blockchain

![Consensus](https://img.shields.io/badge/Consensus-PoW-7E57C2?style=flat&labelColor=333a41)
![C++20](https://img.shields.io/badge/Code-C++20-FF7043?style=flat&labelColor=333a41)
![Google Code Style](https://img.shields.io/badge/Style-Google-29B6F6?style=flat&labelColor=333a41)
[![Deploy Pages](https://github.com/gdaneek/pow-blockchain/actions/workflows/pages.yml/badge.svg?)](https://github.com/gdaneek/pow-blockchain/actions/workflows/pages.yml)
[![GitHub license](https://img.shields.io/badge/License-MIT-66BB6A?style=flat&labelColor=333a41)](https://github.com/gdaneek/pow-blockchain/blob/master/LICENSE)


This project is a modular demonstration of a blockchain consensus system using **Proof-of-Work (PoW)**, written entirely in modern **C++20**. It showcases how cryptographic primitives like hash functions, Merkle trees, and digital signatures come together to build a minimal blockchain from scratch.

You can use this project to:
- Understand the internals of PoW consensus
- Explore cryptographic building blocks like Streebog and Schnorr signatures
- Extend or repurpose modular C++20 components in your own cryptographic tools

---

## 🚀 Overview

This system is split into small, focused C++ modules (managed via Git submodules):

| Module             | Purpose |
|--------------------|---------|
| **external/streebog-hash/** | Implements the Streebog (GOST R 34.11-2018) hash function |
| **external/merkle-tree/** | Generic Merkle tree to hash transaction batches |
| **external/schnorr-sign/** | Schnorr digital signature system with key-prefixing |
| **blockchain/** | Core blockchain logic: blocks, transactions, mining |
| **examples/pow.cc** | CLI demo that ties it all together – generate txs, mine blocks |

Each module is a standalone, testable CMake library and can be reused independently.

---

## 🔐 Cryptographic Components

Here’s what powers the blockchain:

- **Streebog Hash Function**
  Secure Russian standard (GOST R 34.11-2018), supporting 256- and 512-bit output. Highly optimized with lookup tables and bitwise tricks.

- **Merkle Tree**
  Static-sized binary Merkle tree for fast inclusion proofs. Can be paired with any hashing algorithm using a generic Concatenator-Hasher interface.

- **Schnorr Signatures**
  A header-only signature library using GMP for big-integer math. Implements key-prefixed Schnorr to prevent rogue-key attacks.

- **PoW Blockchain Core**
  Manages block construction, mining, and transaction pools. Uses the hash module for PoW puzzles and Merkle trees to compress transaction batches into a single root hash.

---

## 🛠️ Building the Project

### 📋 Requirements
- C++20-compatible compiler (GCC 11.4+ recommended)
- [GMP library](https://gmplib.org/) (for Schnorr signatures)
- CMake ≥ 3.15
- Git

### 🧰 Setup
Clone the main repository **with submodules**:

```bash
git clone --recursive https://github.com/yourusername/pow-blockchain.git
cd pow-blockchain
```

Build it using CMake:

```bash
cmake -S . -B build
cmake --build build
```

---

## ▶️ Running the Example

Launch the interactive PoW demo:

```bash
build/examples/pow
```

What it does:
1. Generates a Schnorr wallet
2. Reads 5 sample transaction files (`t1.txn` through `t5.txn`)
3. Signs and submits each transaction
4. Mines a new block by solving a hash puzzle
5. Prints out the new blockchain state

Each mined block includes:
- Previous block hash
- Merkle root of included transactions
- Difficulty target and nonce
- Timestamp

You'll see console output confirming valid signatures, PoW progress, and successful mining.

---

## 📚 Full Documentation

To build Sphinx + Doxygen docs locally:

```bash
doxygen docs/Doxyfile
cd docs
make html
```

HTML documentation will appear in `docs/build/html`.

---


## ⚖️ License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
