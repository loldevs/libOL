//
// Blowfish C++ implementation
//
// CC0 - PUBLIC DOMAIN
// This work is free of known copyright restrictions.
// http://creativecommons.org/publicdomain/zero/1.0/
//

#pragma once

#ifndef __blowfish__
#define __blowfish__

#include <vector>
#include <cstdint>
#include <cstring>

class Blowfish {
public:
    void SetKey(const std::vector<uint8_t> &key);
    void SetKey(const uint8_t *key, size_t byte_length);
    
    // Buffer will be padded with PKCS #5 automatically
    // "dst" and "src" must be different instance
    void Encrypt(std::vector<uint8_t> *dst, const std::vector<uint8_t> &src) const;
    void Decrypt(std::vector<uint8_t> *dst, const std::vector<uint8_t> &src) const;
    
    // Buffer length must be a multiple of the block length (64bit)
    void Encrypt(uint8_t *dst, const uint8_t *src, size_t byte_length) const;
    void Decrypt(uint8_t *dst, const uint8_t *src, size_t byte_length) const;

private:
    void EncryptBlock(uint32_t *left, uint32_t *right) const;
    void DecryptBlock(uint32_t *left, uint32_t *right) const;
    uint32_t Feistel(uint32_t value) const;
    
private:
    uint32_t pary_[18];
    uint32_t sbox_[4][256];
};

#endif /* defined(__blowfish__) */
