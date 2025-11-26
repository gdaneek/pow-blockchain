/**
 *  @file    blockchain.hpp
 *  @brief   implementation of PoW-based blockchain
 *  @author  https://github.com/gdaneek
 *  @date    30.05.2025
 *  @version 1.0
 */

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "merkle.hpp"
#include "prng.hpp"
#include "schnorr.hpp"

/**
 * @brief test blockchain version to study PoW mining
 */
template <typename Hasher, typename Hash = Hasher::value_type>
struct TestBlockchain {
    using RNG = HashRNG<Hasher>;  ///< use HashRNG as default RNG
    using Signer =
        schnorr::SchnorrKPS<RNG, Hasher>;  ///< use Schnorr key-prefixed as default signer

    Hasher m_hash;  ///< hash function object

    /**
     * @brief TestBlockchain transaction impl
     * @details signed vector of bytes
     */
    class Transaction {
        schnorr::signature_t m_sign;  ///< transaction signature
        std::vector<char> m_data;     ///< transaction data (bytes)
       public:
        template <typename... Args>
        Transaction(schnorr::signature_t sign, Args&&... args)
            : m_sign{sign}, m_data{std::forward<Args>(args)...} {
        }

        schnorr::signature_t get_sign() const {
            return m_sign;
        }

        auto& bytes() {
            return m_data;
        }
        const auto& bytes() const {
            return m_data;
        }

        auto begin() {
            return m_data.begin();
        }
        auto end() {
            return m_data.end();
        }
    };

    /**
     * @brief TestBlockchain block impl
     * @details raw struct with 80 bytes header + transactions vector
     */
    struct Block {
        struct Header {
            uint32_t m_version;
            Hash m_prev;
            Hash m_txn_root;
            uint32_t m_timestamp;
            uint32_t m_target;
            uint32_t m_nonce;
            const char* data() const {
                return (const char*)this;
            }
            static size_t size() {
                return sizeof(Header);
            }
        } __attribute__((packed)) header;
        std::vector<Transaction> m_data;
    };

    /**
     * @brief TestBlockchain wallet impl
     * @details only signs and sends transactions represented by files to the blockchain
     */
    class Wallet {
        TestBlockchain<Hasher, Hash>* blockchain;
        Signer signer;

       public:
        explicit Wallet(TestBlockchain<Hasher, Hash>* _b, Signer _s = Signer{})
            : blockchain{_b}, signer{_s} {
        }

        auto address() const {
            return signer.public_key();
        }

        auto send(const std::string& filename) {
            std::ifstream file(filename, std::ios::binary | std::ios::ate);
            auto file_size = file.tellg();
            file.seekg(0);
            std::vector<char> data(file_size);
            file.read(data.data(), file_size);

            return blockchain->append(address(), Transaction{signer.sign(data), std::move(data)});
        }
    };

    /**
     * @brief TestBlockchain miner impl
     * @details only build blocks for the blockchain using PoW algorithm
     */
    class Miner {
        inline static constexpr auto tnxs_per_block = 5;  ///< according to the task

        TestBlockchain<Hasher, Hash>* m_blockchain;
        merkle::FixedSizeTree<Hasher, tnxs_per_block> m_merke;

       public:
        explicit Miner(TestBlockchain<Hasher, Hash>* _b) : m_blockchain{_b} {
        }

        /**
         * @brief PoW mining implementation
         */
        bool mine() {
            auto tnxs = m_blockchain->get_pool();
            Block block{};
            block.m_data.insert(block.m_data.end(), tnxs.begin(), tnxs.begin() + tnxs_per_block);
            block.header = typename Block::Header{0,
                                                  m_blockchain->m_hash(m_blockchain->last().header),
                                                  m_merke.build(block.m_data).root(),
                                                  1748453809,
                                                  m_blockchain->get_current_target(),
                                                  0};

            if (tnxs.size() < tnxs_per_block) return false;

            auto hhash = m_blockchain->m_hash(block.header);

            while (__builtin_clzll(hhash[0]) != block.header.m_target) {
                ++block.header.m_nonce;
                hhash = m_blockchain->m_hash(block.header);
            }

            m_blockchain->append(block);

            return true;
        }
    };

    std::vector<Transaction> m_tpool;
    std::vector<Block> m_chain;

    // rng_seed according to the task
    // g, q according to GOST 34.10—94
    inline static std::string rng_seed = "danila gubazov";
    inline static auto g = mpz_class(
                           "9E96031500C8774A869582D4AFDE2127AFAD2538B4B6270A6F7C8837B50D50F20675598"
                           "4A49E509304D648BE2AB5AAB18EBE2CD46AC3D8495B142AA6CE23E21C",
                           16),
                       q = mpz_class(
                           "98915E7EC8265EDFCDA31E88F24809DDB064BDC7285DD50D7289F0AC6F49DD2D", 16);

    TestBlockchain() {
        m_chain.push_back(Block{});
    }

    const Block& genesis() {
        return m_chain.front();
    }

    const Block& last() {
        return m_chain.back();
    }

    uint32_t get_current_target() const {
        // uint32_t to simplify the work in mining
        return 5;
    }

    auto get_pool() const {
        return m_tpool;
    }

    bool append(const Block& block) {
        m_chain.push_back(block);
        return true;
    }

    bool append(auto&& sender, const Transaction& txn) {
        auto s = txn.get_sign();
        auto is_valid_txn = Signer::verify(m_hash, schnorr::DefaultSchnorrConcatenator{},
                                           txn.bytes(), s, sender, q, g);
        if (is_valid_txn) m_tpool.push_back(txn);

        return is_valid_txn;
    }

    Wallet* create_wallet() {
        return new Wallet{this, Signer{q, g, RNG{rng_seed}}};
        ;
    }

    Miner* create_miner() {
        return new Miner{this};
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const typename TestBlockchain<Hasher, Hash>::Block& block) {
        os << "Block (\n" << std::hex;
        std::cout << "  version: " << block.header.m_version << std::endl;
        std::cout << "  previous: " << block.header.m_prev << std::endl;
        std::cout << "  merkle root: " << block.header.m_txn_root << std::endl;
        std::cout << "  timestamp: " << block.header.m_timestamp << std::endl;
        std::cout << "  target: " << block.header.m_target << std::endl;
        std::cout << "  nonce: " << block.header.m_nonce << std::endl;
        os << ");" << std::dec;

        return os;
    }
};

#include <inttypes.h>

#include <iostream>

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    if (N == 0) return os;
    std::for_each(arr.begin(), arr.end(), [&](const T& elem) { printf("%016" PRIx64 "", elem); });
    return os;
}
