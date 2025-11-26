/**
 *  @file    txn_gen.cc
 *  @brief   random transaction generator for TestBlockchain
 *  @author  https://github.com/gdaneek
 *  @date    30.05.2025
 *  @version 1.0
 */
#define STREEBOG_ENABLE_WRAPPERS
#include <array>
#include <fstream>

#include "prng.hpp"
#include "streebog.hh"

struct Hasher {
    using value_type = typename std::array<uint64_t, 4>;
    auto operator()(auto&& x) const -> value_type {
        return streebog256(x.data(), x.size() * sizeof(*x.data()));
    }
};

int main(int argc, char* argv[]) {
    auto bytes_n = std::stoll(argv[argc - 1]);
    auto seed = "danila gubazov";

    HashRNG<Hasher> rng(seed);

    for (size_t i{}; i < argc - 2; i++) {
        std::ofstream fout(argv[i + 1], std::ios::binary);
        auto x = rng.next();

        for (size_t bw{}; bw + sizeof(x) < bytes_n; bw += sizeof(x)) {
            fout.write((const char*)x.data(), sizeof(x));
            x = rng.next();
        }
    }

    return 0;
}
