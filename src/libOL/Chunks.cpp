// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Chunks.h"

extern "C" {
#include <zlib.h>
}

#include "Blowfish/Blowfish.h"

namespace libol {
    namespace Chunks {
        std::vector<uint8_t> decryptAndDecompress(std::vector<uint8_t> bytes, std::vector<uint8_t> key) {
            auto decrypted = Blowfish::decrypt(bytes, key);

            std::vector<uint8_t> decompressed;
            decompressed.resize(decrypted.size());

            z_stream stream;
            stream.next_in = (Bytef *)decrypted.data();
            stream.avail_in = decrypted.size();
            stream.total_out = 0;
            stream.zalloc = Z_NULL;
            stream.zfree = Z_NULL;  

            // TODO: handle errors better
            if (inflateInit2(&stream, (16 + MAX_WBITS)) != Z_OK) {
                return std::vector<uint8_t> {};
            }

            bool done = false;
            while (!done) {
                // If total_out has reached decompressed's capacity, make room for more
                if (stream.total_out >= decompressed.capacity()) {
                    // Resize output to 150% of previous size
                    decompressed.resize(decompressed.capacity() + (decompressed.capacity() << 1));
                }

                stream.next_out = (Bytef *)(&decompressed[0] + stream.total_out);
                stream.avail_out = decompressed.capacity() - stream.total_out;
                int err = inflate(&stream, Z_SYNC_FLUSH);
                if (err == Z_STREAM_END) {
                    done = true;
                } else if (err != Z_OK)  {
                    // TODO: handle errors better
                    break;
                }
            }

            if (inflateEnd(&stream) != Z_OK) {
                // TODO: handle errors better
                return std::vector<uint8_t> {};
            }  

            decompressed.resize(stream.total_out);
            return decompressed;
        }
    }
}
