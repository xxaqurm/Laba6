#include <iostream>
#include <string>
#include "aes.h"
#include "ofb.h"
#include "utils.h"

using namespace std;

void printUsage() {
    cout << "Usage:\n"
              << "  Encrypt: aes_ofb -e input_file_path output_file_path iv_file_path key_file_path\n"
              << "  Decrypt: aes_ofb -d input_file_path output_file_path key_file_path iv_file_path\n"
              << "  Generate key: aes_ofb -g key_file\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            printUsage();
            return 1;
        }

        string mode = argv[1];

        if (mode == "-g") { // Генерация ключа
            if (argc != 3) {
                printUsage();
                return 1;
            }

            string keyFile = argv[2];
            vector<uint8_t> key = generateRandomIV();
            writeFile(keyFile, key);
            cout << "Key generated and saved to: " << keyFile << endl;

        } else if (mode == "-e") { // Шифрование
            if (argc != 6) {
                printUsage();
                return 1;
            }

            string inputFile = argv[2];
            string outputFile = argv[3];
            string ivFile = argv[4];
            string keyFile = argv[5];

            vector<uint8_t> key = readFile(keyFile);
            if (key.size() != 16) {
                throw runtime_error("Key must be 16 bytes (128 bits)");
            }

            vector<uint8_t> plaintext = readFile(inputFile);
            vector<uint8_t> iv = generateRandomIV();

            OFB ofb(key, iv);
            vector<uint8_t> ciphertext = ofb.encrypt(plaintext);

            writeFile(ivFile, iv);
            appendToFile(outputFile, ciphertext);

            cout << "File encrypted successfully. IV + ciphertext saved to: " 
                      << outputFile << endl;

        } else if (mode == "-d") { // Дешифрование
            if (argc != 6) {
                printUsage();
                return 1;
            }

            string inputFile = argv[2];
            string outputFile = argv[3];
            string ivFile = argv[4];
            string keyFile = argv[5];

            vector<uint8_t> key = readFile(keyFile);
            if (key.size() != 16) {
                throw runtime_error("Key must be 16 bytes (128 bits)");
            }

            vector<uint8_t> iv = readFile(ivFile);
            if (iv.size() != 16) {
                throw runtime_error("IV must be 16 bytes");
            }

            vector<uint8_t> ciphertext = readFile(inputFile);

            OFB ofb(key, iv);
            vector<uint8_t> plaintext = ofb.decrypt(ciphertext);

            writeFile(outputFile, plaintext);

            cout << "File decrypted successfully. Saved to: " 
                      << outputFile << endl;

        } else {
            printUsage();
            return 1;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}