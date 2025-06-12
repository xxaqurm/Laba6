#pragma once

#include <vector>
#include <cstdint>
#include "aes.h"

class OFB {
public:
    OFB(const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv);
    
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext);
    
private:
    AES aes;
    std::vector<uint8_t> iv;
    std::vector<uint8_t> feedback;
};
