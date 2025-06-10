#pragma once

#include <vector>
#include <string>
#include <cstdint>

std::vector<uint8_t> stringToBytes(const std::string& str);
std::string bytesToString(const std::vector<uint8_t>& bytes);
std::vector<uint8_t> generateRandomIV();
void printHex(const std::vector<uint8_t>& bytes);
std::vector<uint8_t> readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::vector<uint8_t>& data);
void appendToFile(const std::string& filename, const std::vector<uint8_t>& data);
