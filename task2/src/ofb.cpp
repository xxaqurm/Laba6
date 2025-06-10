#include "ofb.h"
#include <stdexcept>

OFB::OFB(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) 
    : aes(key), iv(iv), feedback(iv) {
    if (iv.size() != 16) {
        throw std::runtime_error("IV must be 16 bytes for AES");
    }
}

std::vector<uint8_t> OFB::encrypt(const std::vector<uint8_t>& plaintext) {
    std::vector<uint8_t> ciphertext;
    ciphertext.reserve(plaintext.size());
    
    for (size_t i = 0; i < plaintext.size(); i += 16) {
        // Encrypt the feedback to get the next keystream block
        feedback = aes.encrypt(feedback);
        
        // Determine the block size (last block might be smaller)
        size_t blockSize = std::min<size_t>(16, plaintext.size() - i);
        
        // XOR plaintext block with keystream block
        for (size_t j = 0; j < blockSize; ++j) {
            ciphertext.push_back(plaintext[i + j] ^ feedback[j]);
        }
    }
    
    return ciphertext;
}

std::vector<uint8_t> OFB::decrypt(const std::vector<uint8_t>& ciphertext) {
    // OFB mode decryption is the same as encryption
    return encrypt(ciphertext);
}
