#define STREEBOG_ENABLE_WRAPPERS
#include <string>

#include "blockchain.hpp"
#include "streebog.hh"

struct Hasher {
    using value_type = typename std::array<uint64_t, 4>;
    auto operator()(auto&& x) const -> value_type {
        return streebog256(x.data(), x.size() * sizeof(*x.data()));
    }
};

int main() {
    TestBlockchain<Hasher> bchain;

    auto wallet = bchain.create_wallet();
    std::cout << "blockchain: new wallet 0x" << std::hex << wallet->address() << std::dec
              << " | gdaneek" << std::endl;

    std::vector<std::string> files = {"t1.txn", "t2.txn", "t3.txn", "t4.txn", "t5.txn"};

    for (auto&& x : files) {
        std::cout << "wallet gdaneek: try send " << x << std::endl;
        std::cout << "blockchain: " << (wallet->send(x) ? "accepted\n" : "rejected\n");
    }

    auto miner = bchain.create_miner();
    std::cout << "blockchain: created new miner object at " << miner << std::endl;

    auto status = miner->mine();
    std::cout << "miner " << miner << ": mine " << (status ? "successful\n" : "failed\n");

    std::cout << "blockchain: current chain\n";
    for (auto&& x : bchain.m_chain) std::cout << x << std::endl;

    std::cout << "genesis block hash: " << Hasher{}(bchain.m_chain.front().header) << std::endl;
    std::cout << "last block header hash: " << Hasher{}(bchain.m_chain.back().header) << std::endl;

    delete miner;
    delete wallet;

    return 0;
}
