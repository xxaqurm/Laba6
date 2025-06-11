#include "ofb.h"
#include <stdexcept>

using namespace std;

OFB::OFB(const vector<uint8_t>& key, const vector<uint8_t>& iv) 
    : aes(key), iv(iv), feedback(iv) {
    if (iv.size() != 16) {
        throw runtime_error("IV must be 16 bytes for AES");
    }
}

vector<uint8_t> OFB::encrypt(const vector<uint8_t>& plaintext) {
    vector<uint8_t> ciphertext;
    ciphertext.reserve(plaintext.size());
    
    for (size_t i = 0; i < plaintext.size(); i += 16) {
        feedback = aes.encrypt(feedback);
        
        size_t blockSize = min<size_t>(16, plaintext.size() - i);
        
        for (size_t j = 0; j < blockSize; j++) {
            ciphertext.push_back(plaintext[i + j] ^ feedback[j]);
        }
    }
    
    return ciphertext;
}

vector<uint8_t> OFB::decrypt(const vector<uint8_t>& ciphertext) {
    // OFB дешифрование работает также, как и шифрование
    return encrypt(ciphertext);
}
