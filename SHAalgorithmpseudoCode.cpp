// sha256.cpp
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <bitset>

class SHA256 {
public:
    static std::string hash(const std::string& data) {
        std::vector<unsigned int> K = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            // Add all other constants
        };
        
        std::array<unsigned int, 8> H = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            // Add all other initial hash values
        };
        
        std::vector<unsigned char> padded = pad(data);
        for (size_t i = 0; i < padded.size(); i += 64) {
            std::array<unsigned int, 64> W;
            for (int j = 0; j < 16; ++j) {
                W[j] = (padded[i + j*4] << 24) | (padded[i + j*4 + 1] << 16) | (padded[i + j*4 + 2] << 8) | (padded[i + j*4 + 3]);
            }
            
            // Extend the first 16 words into the remaining 48 words of the message schedule array
            for (int j = 16; j < 64; ++j) {
                unsigned int s0 = rightrotate(W[j-15], 7) ^ rightrotate(W[j-15], 18) ^ (W[j-15] >> 3);
                unsigned int s1 = rightrotate(W[j-2], 17) ^ rightrotate(W[j-2], 19) ^ (W[j-2] >> 10);
                W[j] = W[j-16] + s0 + W[j-7] + s1;
            }
            
            // Compression function main loop
            unsigned int a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
            
            for (int j = 0; j < 64; ++j) {
                unsigned int S1 = rightrotate(e, 6) ^ rightrotate(e, 11) ^ rightrotate(e, 25);
                unsigned int ch = (e & f) ^ ((~e) & g);
                unsigned int temp1 = h + S1 + ch + K[j] + W[j];
                unsigned int S0 = rightrotate(a, 2) ^ rightrotate(a, 13) ^ rightrotate(a, 22);
                unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
                unsigned int temp2 = S0 + maj;
                
                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }
            
            // Add the compressed chunk to the current hash value
            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
            H[5] += f;
            H[6] += g;
            H[7] += h;
        }
        
        // Produce the final hash value (big-endian)
        std::string digest;
        for (unsigned int i : H) {
            digest += intToHex(i);
        }
        return digest;
    }

private:
    static std::vector<unsigned char> pad(const std::string& data) {
        // Padding implementation
    }

    static unsigned int rightrotate(unsigned int value, unsigned int bits) {
        return (value >> bits) | (value << (32 - bits));
    }

    static std::string intToHex(unsigned int i) {
        // Convert integer to hex string
    }
};

int main() {
    std::string data = "Your data here";
    std::string hash = SHA256::hash(data);
    std::cout << "Hash: " << hash << std::endl;
    return 0;
}