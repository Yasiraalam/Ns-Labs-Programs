#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate the Playfair cipher key matrix
vector<vector<char>> generateKeyMatrix(const string& key) {
    vector<vector<char>> keyMatrix(5, vector<char>(5, ' '));
    string keyWithoutDuplicates;

    // Remove duplicates from the key and append non-'J' characters
    for (char c : key) {
        if (isalpha(c) && c != 'J' && keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    // Append remaining alphabet characters (excluding 'J') to the key
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c != 'J' && keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    // Fill the key matrix with the key
    for (int i = 0, k = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            keyMatrix[i][j] = keyWithoutDuplicates[k++];
        }
    }

    return keyMatrix;
}

// Function to find the position of a character in the key matrix
pair<int, int> findPosition(const vector<vector<char>>& keyMatrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keyMatrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Not found
}

// Function to encrypt plaintext using Playfair cipher
string encrypt(const string& plaintext, const string& key) {
    // Generate the key matrix
    vector<vector<char>> keyMatrix = generateKeyMatrix(key);

    // Remove spaces and non-alphabetic
