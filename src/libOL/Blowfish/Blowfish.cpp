// Copyright (c) 2014 Luke Granger-Brown.
// Distributed under the MIT License.

#include "Blowfish.h"

#include <memory>

extern "C" {
#include <openssl/blowfish.h>
}

#define BLOCK_SIZE 8

static std::vector<uint8_t> actuallyDoTheCrypto(std::vector<uint8_t> bytes, std::vector<uint8_t> key, bool amEncrypting) {
        // initialise the blowfish state
        //std::unique_ptr<BF_KEY> blowfish(new BF_KEY);
        auto blowfish = new BF_KEY;
        BF_set_key(blowfish, key.size(), &key[0]);

        // allocate the output buffer
        std::vector<uint8_t> out;
        out.resize(bytes.size());

        // loop through and do the crypto
        // XXX: this code should probably be rewritten
        auto size = bytes.size();
        auto encDecFlag = amEncrypting ? BF_ENCRYPT : BF_DECRYPT;
        for (std::vector<uint8_t>::size_type i = 0; i < size; i += BLOCK_SIZE) {
                BF_ecb_encrypt(&bytes[i], &out[i], blowfish, encDecFlag);
        }

        return out;
}

namespace libol {
    namespace Blowfish {
        std::vector<uint8_t> rawDecrypt(std::vector<uint8_t> bytes, std::vector<uint8_t> key) {
                return ::actuallyDoTheCrypto(bytes, key, false);
        }
        std::vector<uint8_t> decrypt(std::vector<uint8_t> bytes, std::vector<uint8_t> key) {
                auto data = rawDecrypt(bytes, key);

                if (data.size() == 0) {
                        // don't strip the padding from something with no length...
                        return data;
                }

                // how much padding do we need to remove?
                uint8_t paddingBytes = *(data.end() - 1);

                // erm, what?
                if (paddingBytes > data.size() || paddingBytes > BLOCK_SIZE || paddingBytes == 0) {
                        throw std::invalid_argument("The padding was invalid");
                }

                // remove it!
                data.erase(data.end() - paddingBytes, data.end());

                return data;
        }
        std::vector<uint8_t> rawEncrypt(std::vector<uint8_t> bytes, std::vector<uint8_t> key) {
                return ::actuallyDoTheCrypto(bytes, key, true);
        }
        std::vector<uint8_t> encrypt(std::vector<uint8_t> in_bytes, std::vector<uint8_t> key) {
                auto bytes = in_bytes;
                auto size = bytes.size();

                // this needs to be a multiple of BLOCK_SIZE
                auto paddingSize = BLOCK_SIZE - (size % BLOCK_SIZE);

                // there must be at least some padding
                if (paddingSize == 0) paddingSize = BLOCK_SIZE;

                // allocate the new size
                size += (BLOCK_SIZE - (size % BLOCK_SIZE));
                bytes.reserve(size);

                // now write the padding
                bytes.push_back(paddingSize);

                return rawEncrypt(bytes, key);
        }
    }
}
