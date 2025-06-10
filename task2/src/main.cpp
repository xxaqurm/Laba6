#include <iostream>
#include <string>
#include "aes.h"
#include "ofb.h"
#include "utils.h"

void printUsage() {
    std::cout << "Usage:\n"
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

        std::string mode = argv[1];

        if (mode == "-g") { // Генерация ключа
            if (argc != 3) {
                printUsage();
                return 1;
            }

            std::string keyFile = argv[2];
            auto key = generateRandomIV(); // 16 байт
            writeFile(keyFile, key);
            std::cout << "Key generated and saved to: " << keyFile << std::endl;

        } else if (mode == "-e") { // Шифрование
            if (argc != 6) {
                printUsage();
                return 1;
            }

            std::string inputFile = argv[2];
            std::string outputFile = argv[3];
            std::string ivFile = argv[4];
            std::string keyFile = argv[5];

            // Читаем ключ и входной файл
            auto key = readFile(keyFile);
            if (key.size() != 16) {
                throw std::runtime_error("Key must be 16 bytes (128 bits)");
            }

            auto plaintext = readFile(inputFile);
            auto iv = generateRandomIV();

            // Шифруем
            OFB ofb(key, iv);
            auto ciphertext = ofb.encrypt(plaintext);

            // Сохраняем IV и зашифрованные данные
            writeFile(ivFile, iv);
            appendToFile(outputFile, ciphertext);

            std::cout << "File encrypted successfully. IV + ciphertext saved to: " 
                      << outputFile << std::endl;

        } else if (mode == "-d") { // Дешифрование
            if (argc != 6) {
                printUsage();
                return 1;
            }

            std::string inputFile = argv[2];
            std::string outputFile = argv[3];
            std::string keyFile = argv[4];
            std::string ivFile = argv[5];

            // Читаем ключ, IV и зашифрованные данные
            auto key = readFile(keyFile);
            if (key.size() != 16) {
                throw std::runtime_error("Key must be 16 bytes (128 bits)");
            }

            auto iv = readFile(ivFile);
            if (iv.size() != 16) {
                throw std::runtime_error("IV must be 16 bytes");
            }

            auto ciphertext = readFile(inputFile);

            // Дешифруем
            OFB ofb(key, iv);
            auto plaintext = ofb.decrypt(ciphertext);

            // Сохраняем результат
            writeFile(outputFile, plaintext);

            std::cout << "File decrypted successfully. Saved to: " 
                      << outputFile << std::endl;

        } else {
            printUsage();
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}