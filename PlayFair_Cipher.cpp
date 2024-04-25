#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate the Playfair cipher key matrix
vector<vector<char>> generateKeyMatrix(string key) {
    vector<vector<char>> keyMatrix(5, vector<char>(5, ' '));
    string keyWithoutDuplicates = "";

    // Remove duplicates from the key
    for (char c : key) {
        if (c != ' ' && keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    // Fill the key matrix with the key
    int row = 0, col = 0;
    for (char c : keyWithoutDuplicates) {
        keyMatrix[row][col] = c;
        col++;
        if (col == 5) {
            col = 0;
            row++;
        }
    }

    // Fill the remaining cells with the alphabet
    char currentLetter = 'A';
    for (int i = row; i < 5; ++i) {
        for (int j = col; j < 5; ++j) {
            while (keyWithoutDuplicates.find(currentLetter) != string::npos) {
                currentLetter++;
            }
            keyMatrix[i][j] = currentLetter;
            currentLetter++;
        }
        col = 0;
    }

    return keyMatrix;
}

// Function to find the position of a character in the key matrix
pair<int, int> findPosition(vector<vector<char>>& keyMatrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (keyMatrix[i][j] == c) {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1); // Not found
}


string encrypt(string plaintext, string key) {

    vector<vector<char>> keyMatrix = generateKeyMatrix(key);

    // Remove spaces and non-alphabetic characters from plaintext
    plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace), plaintext.end());
    plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::ispunct), plaintext.end());

    // Replace any 'J' with 'I' in the plaintext
    replace(plaintext.begin(), plaintext.end(), 'J', 'I');

    // Make sure plaintext length is even by adding an 'X' if necessary
    if (plaintext.length() % 2 != 0) {
        plaintext += 'X';
    }

  
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i += 2) {
        char first = plaintext[i];
        char second = plaintext[i + 1];
        pair<int, int> posFirst = findPosition(keyMatrix, first);
        pair<int, int> posSecond = findPosition(keyMatrix, second);
        if (posFirst.first == posSecond.first) { // Same row
            ciphertext += keyMatrix[posFirst.first][(posFirst.second + 1) % 5];
            ciphertext += keyMatrix[posSecond.first][(posSecond.second + 1) % 5];
        } else if (posFirst.second == posSecond.second) { // Same column
            ciphertext += keyMatrix[(posFirst.first + 1) % 5][posFirst.second];
            ciphertext += keyMatrix[(posSecond.first + 1) % 5][posSecond.second];
        } else { // Form a rectangle
            ciphertext += keyMatrix[posFirst.first][posSecond.second];
            ciphertext += keyMatrix[posSecond.first][posFirst.second];
        }
    }

    return ciphertext;
}

int main() {
    string plaintext, key;

    // Input plaintext and key
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter key: ";
    getline(cin, key);

    // Encrypt plaintext
    string ciphertext = encrypt(plaintext, key);

    // Output ciphertext
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
