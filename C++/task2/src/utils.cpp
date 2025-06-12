#include "utils.h"
#include <random>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <iostream>

#include <fstream>
#include <iterator>

using namespace std;

vector<uint8_t> stringToBytes(const string& str) {
    return vector<uint8_t>(str.begin(), str.end());
}

string bytesToString(const vector<uint8_t>& bytes) {
    return string(bytes.begin(), bytes.end());
}

vector<uint8_t> generateRandomIV() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 255);
    
    vector<uint8_t> iv(16);
    for (auto& byte : iv) {
        byte = static_cast<uint8_t>(dis(gen));
    }
    
    return iv;
}

void printHex(const vector<uint8_t>& bytes) {
    cout << hex << setfill('0');
    for (const auto& byte : bytes) {
        cout << setw(2) << static_cast<int>(byte) << ' ';
    }
    cout << dec << endl;
}

vector<uint8_t> readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open file: " + filename);
    }
    
    // Читаем весь файл в вектор
    return vector<uint8_t>(
        istreambuf_iterator<char>(file),  // итератор, который начинает чтение с первого символа потока file
        istreambuf_iterator<char>()
    );
}

void writeFile(const string& filename, const vector<uint8_t>& data) {
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot create file: " + filename);
    }
    
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void appendToFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary | std::ios::app); // открываем файл в режиме добавления (append)
    if (!file) {
        throw std::runtime_error("Cannot open file for appending: " + filename);
    }
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}
