#pragma once

#include <vector>
#include <cstdint>

class AES {
public:
    AES(const std::vector<uint8_t>& key);
    
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext);
    
private:
    void keyExpansion();
    void addRoundKey(int round);
    void subBytes();
    void invSubBytes();
    void shiftRows();
    void invShiftRows();
    void mixColumns();
    void invMixColumns();
    
    std::vector<uint8_t> state;
    std::vector<uint8_t> roundKey;
    std::vector<uint8_t> key;
    
    static const uint8_t sBox[256];
    static const uint8_t invSBox[256];
    static const uint8_t rcon[11];
};
