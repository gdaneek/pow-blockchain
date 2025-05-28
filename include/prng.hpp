/**
 *  @file    prng.hpp
 *  @brief   pseudorandom number generator based on a hash function
 *  @author  https://github.com/gdaneek
 *  @date    30.05.2025
 *  @version 1.0
 */

#pragma once

#include "bytes_concat.hpp"


/**
 * @brief pseudorandom number generator based on a hash function impl
 * @tparam Hasher class that implements hash function
 * @tparam Hash Hasher return value type
 * @tparam Concatenator class that implements bytes concatenation
 */
template<typename Hasher, typename Hash = Hasher::value_type, typename Concatenator = bconcat::TrivialConcatenator>
class HashRNG {

    Hasher m_hash;          ///< Hasher object
    Concatenator m_concat;  ///< Concatenator object

    Hash m_state;           ///< current hash of the generator (internal state)
    uint64_t m_counter;     ///< iteration counter

public:

    HashRNG() = default;


    /**
     * @brief constructor that allows to explicitly set the initial state (seed)
     * @param seed initial state
     */
    explicit HashRNG(const std::string& seed, Hasher _hash = Hasher{}, Concatenator _c = Concatenator{})
    : m_hash{_hash}, m_concat{_c}, m_counter{} {
        m_state = m_hash(seed);
    }



    /**
     * @brief renerate next pseudorandom value
     * @return Hash object
     */
    Hash next() {
        return (m_state = m_hash(m_concat(m_state, ++m_counter)));
    }


    /**
     * @brief next() method alias
     */
    auto operator()() {
        return this->next();
    }

};
