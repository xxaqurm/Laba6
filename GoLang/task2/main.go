package main

import (
	"crypto/rand"
	"errors"
	"fmt"
	"io/ioutil"
	"os"
)

// AES implementation
type AES struct {
	key      []byte
	roundKey [176]byte
}

var sBox = [256]byte{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
}

var rcon = [11]byte{0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36}

func NewAES(key []byte) (*AES, error) {
	if len(key) != 16 {
		return nil, errors.New("Key must be 16 bytes for AES-128")
	}
	aes := &AES{key: key}
	aes.keyExpansion()
	return aes, nil
}

func (a *AES) keyExpansion() {
	var i int
	var temp [4]byte

	// Первые 16 байт - это сам ключ
	copy(a.roundKey[:16], a.key)

	// Все остальные раундовые ключи
	for i = 16; i < 176; i += 4 {
		// Копируем предыдущее слово
		for j := 0; j < 4; j++ {
			temp[j] = a.roundKey[i-4+j]
		}

		// Применяем преобразования для каждого 16-го байта
		if i%16 == 0 {
			// Циклический сдвиг влево
			t := temp[0]
			temp[0] = temp[1]
			temp[1] = temp[2]
			temp[2] = temp[3]
			temp[3] = t

			// S-box замена
			for j := 0; j < 4; j++ {
				temp[j] = sBox[temp[j]]
			}

			// XOR с rcon
			temp[0] ^= rcon[i/16]
		}

		// XOR с предыдущим раундовым ключом
		for j := 0; j < 4; j++ {
			a.roundKey[i+j] = a.roundKey[i-16+j] ^ temp[j]
		}
	}
}

func (a *AES) addRoundKey(state []byte, round int) {
	for i := 0; i < 16; i++ {
		state[i] ^= a.roundKey[round*16+i]
	}
}

func (a *AES) subBytes(state []byte) {
	for i := 0; i < 16; i++ {
		state[i] = sBox[state[i]]
	}
}

func (a *AES) shiftRows(state []byte) {
	// Row 1 - циклический сдвиг на 1 влево
	temp := state[1]
	state[1] = state[5]
	state[5] = state[9]
	state[9] = state[13]
	state[13] = temp

	// Row 2 - циклический сдвиг на 2
	temp = state[2]
	state[2] = state[10]
	state[10] = temp
	temp = state[6]
	state[6] = state[14]
	state[14] = temp

	// Row 3 - циклический сдвиг на 3 (или 1 вправо)
	temp = state[15]
	state[15] = state[11]
	state[11] = state[7]
	state[7] = state[3]
	state[3] = temp
}

func gmul(a, b byte) byte {
	var p byte
	for i := 0; i < 8; i++ {
		if (b & 1) != 0 {
			p ^= a
		}
		hiBitSet := (a & 0x80) != 0
		a <<= 1
		if hiBitSet {
			a ^= 0x1b // x^8 + x^4 + x^3 + x + 1
		}
		b >>= 1
	}
	return p
}

func (a *AES) mixColumns(state []byte) {
	var temp [16]byte

	for i := 0; i < 4; i++ {
		temp[4*i+0] = gmul(0x02, state[4*i+0]) ^ gmul(0x03, state[4*i+1]) ^ state[4*i+2] ^ state[4*i+3]
		temp[4*i+1] = state[4*i+0] ^ gmul(0x02, state[4*i+1]) ^ gmul(0x03, state[4*i+2]) ^ state[4*i+3]
		temp[4*i+2] = state[4*i+0] ^ state[4*i+1] ^ gmul(0x02, state[4*i+2]) ^ gmul(0x03, state[4*i+3])
		temp[4*i+3] = gmul(0x03, state[4*i+0]) ^ state[4*i+1] ^ state[4*i+2] ^ gmul(0x02, state[4*i+3])
	}

	copy(state, temp[:])
}

func (a *AES) EncryptBlock(plaintext []byte) ([]byte, error) {
	if len(plaintext) != 16 {
		return nil, errors.New("Plaintext must be 16 bytes for AES")
	}

	state := make([]byte, 16)
	copy(state, plaintext)

	a.addRoundKey(state, 0)

	for round := 1; round < 10; round++ {
		a.subBytes(state)
		a.shiftRows(state)
		a.mixColumns(state)
		a.addRoundKey(state, round)
	}

	// Final round (без mixColumns)
	a.subBytes(state)
	a.shiftRows(state)
	a.addRoundKey(state, 10)

	return state, nil
}

// OFB implementation
type OFB struct {
	aes      *AES
	iv       []byte
	feedback []byte
}

func NewOFB(key, iv []byte) (*OFB, error) {
	aes, err := NewAES(key)
	if err != nil {
		return nil, err
	}

	if len(iv) != 16 {
		return nil, errors.New("IV must be 16 bytes for AES")
	}

	feedback := make([]byte, 16)
	copy(feedback, iv)

	return &OFB{
		aes:      aes,
		iv:       iv,
		feedback: feedback,
	}, nil
}

func (o *OFB) Crypt(data []byte) ([]byte, error) {
	ciphertext := make([]byte, len(data))

	for i := 0; i < len(data); {
		var err error
		o.feedback, err = o.aes.EncryptBlock(o.feedback)
		if err != nil {
			return nil, err
		}

		blockSize := 16
		if len(data)-i < blockSize {
			blockSize = len(data) - i
		}

		for j := 0; j < blockSize; j++ {
			ciphertext[i+j] = data[i+j] ^ o.feedback[j]
		}

		i += blockSize
	}

	return ciphertext, nil
}

// Utility functions
func generateRandomIV() ([]byte, error) {
	iv := make([]byte, 16)
	_, err := rand.Read(iv)
	return iv, err
}

func readFile(filename string) ([]byte, error) {
	return ioutil.ReadFile(filename)
}

func writeFile(filename string, data []byte) error {
	return ioutil.WriteFile(filename, data, 0644)
}

func appendToFile(filename string, data []byte) error {
	f, err := os.OpenFile(filename, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
	if err != nil {
		return err
	}
	defer f.Close()

	_, err = f.Write(data)
	return err
}

func printUsage() {
	fmt.Println("Usage:")
	fmt.Println("  Encrypt: aes_ofb -e input_file_path output_file_path iv_file_path key_file_path")
	fmt.Println("  Decrypt: aes_ofb -d input_file_path output_file_path key_file_path iv_file_path")
	fmt.Println("  Generate key: aes_ofb -g key_file")
}

func main() {
	if len(os.Args) < 2 {
		printUsage()
		os.Exit(1)
	}

	mode := os.Args[1]

	switch mode {
	case "-g":
		if len(os.Args) != 3 {
			printUsage()
			os.Exit(1)
		}

		keyFile := os.Args[2]
		key, err := generateRandomIV()
		if err != nil {
			fmt.Println("Error generating key:", err)
			os.Exit(1)
		}

		if err := writeFile(keyFile, key); err != nil {
			fmt.Println("Error saving key:", err)
			os.Exit(1)
		}

		fmt.Println("Key generated and saved to:", keyFile)

	case "-e":
		if len(os.Args) != 6 {
			printUsage()
			os.Exit(1)
		}

		inputFile := os.Args[2]
		outputFile := os.Args[3]
		ivFile := os.Args[4]
		keyFile := os.Args[5]

		key, err := readFile(keyFile)
		if err != nil {
			fmt.Println("Error reading key:", err)
			os.Exit(1)
		}

		if len(key) != 16 {
			fmt.Println("Error: Key must be 16 bytes (128 bits)")
			os.Exit(1)
		}

		plaintext, err := readFile(inputFile)
		if err != nil {
			fmt.Println("Error reading input file:", err)
			os.Exit(1)
		}

		iv, err := generateRandomIV()
		if err != nil {
			fmt.Println("Error generating IV:", err)
			os.Exit(1)
		}

		ofb, err := NewOFB(key, iv)
		if err != nil {
			fmt.Println("Error creating OFB:", err)
			os.Exit(1)
		}

		ciphertext, err := ofb.Crypt(plaintext)
		if err != nil {
			fmt.Println("Error encrypting:", err)
			os.Exit(1)
		}

		if err := writeFile(ivFile, iv); err != nil {
			fmt.Println("Error saving IV:", err)
			os.Exit(1)
		}

		if err := writeFile(outputFile, ciphertext); err != nil {
			fmt.Println("Error saving ciphertext:", err)
			os.Exit(1)
		}

		fmt.Println("File encrypted successfully. IV + ciphertext saved to:", outputFile)

	case "-d":
		if len(os.Args) != 6 {
			printUsage()
			os.Exit(1)
		}

		inputFile := os.Args[2]
		outputFile := os.Args[3]
		keyFile := os.Args[4]
		ivFile := os.Args[5]

		key, err := readFile(keyFile)
		if err != nil {
			fmt.Println("Error reading key:", err)
			os.Exit(1)
		}

		if len(key) != 16 {
			fmt.Println("Error: Key must be 16 bytes (128 bits)")
			os.Exit(1)
		}

		iv, err := readFile(ivFile)
		if err != nil {
			fmt.Println("Error reading IV:", err)
			os.Exit(1)
		}

		if len(iv) != 16 {
			fmt.Println("Error: IV must be 16 bytes")
			os.Exit(1)
		}

		ciphertext, err := readFile(inputFile)
		if err != nil {
			fmt.Println("Error reading input file:", err)
			os.Exit(1)
		}

		ofb, err := NewOFB(key, iv)
		if err != nil {
			fmt.Println("Error creating OFB:", err)
			os.Exit(1)
		}

		plaintext, err := ofb.Crypt(ciphertext)
		if err != nil {
			fmt.Println("Error decrypting:", err)
			os.Exit(1)
		}

		if err := writeFile(outputFile, plaintext); err != nil {
			fmt.Println("Error saving plaintext:", err)
			os.Exit(1)
		}

		fmt.Println("File decrypted successfully. Saved to:", outputFile)

	default:
		printUsage()
		os.Exit(1)
	}
}
