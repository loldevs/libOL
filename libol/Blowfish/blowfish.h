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

#include <stdint.h>
#include <cstddef>
#include <string>

class Blowfish {
public:
    void SetKey(const std::string& key);
    void SetKey(const char* key, size_t byte_length);
    
    // Buffer will be padded with PKCS #5 automatically
    // "dst" and "src" must be different instance
    void Encrypt(std::string* dst, const std::string& src) const;
    void Decrypt(std::string* dst, const std::string& src) const;
    
    // Buffer length must be a multiple of the block length (64bit)
    void Encrypt(char* dst, const char* src, size_t byte_length) const;
    void Decrypt(char* dst, const char* src, size_t byte_length) const;
    
private:
    void EncryptBlock(uint32_t *left, uint32_t *right) const;
    void DecryptBlock(uint32_t *left, uint32_t *right) const;
    uint32_t Feistel(uint32_t value) const;
    
private:
    uint32_t pary_[18];
    uint32_t sbox_[4][256];
};

#endif /* defined(__blowfish__) */
