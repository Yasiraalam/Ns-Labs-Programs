#include<bits/stdc++.h>
#define ll long long
using namespace std;


int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}


string encrypt(string plaintext, vector<vector<int>> key) {
    string ciphertext = "";
    int n = key.size();
    int blockSize = n;

    // Padding if necessary
    if (plaintext.size() % blockSize != 0) {
        plaintext.append(blockSize - (plaintext.size() % blockSize), 'X');
    }

    for (int i = 0; i < plaintext.size(); i += blockSize) {
        vector<int> block(n, 0);
        for (int j = 0; j < blockSize; j++) {
            block[j] = plaintext[i + j] - 'A';
        }

        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += key[j][k] * block[k];
            }
            ciphertext += (sum % 26) + 'A';
        }
    }

    return ciphertext;
}

int main() {
    string plaintext, key_str;
    cout << "Enter plaintext: ";
    cin >> plaintext;
    cout << "Enter key matrix (e.g., 3x3 matrix as '1 2 3 4 5 6 7 8 9'): ";
    cin.ignore(); // Ignore newline character
    getline(cin, key_str);

    // Convert key string into a matrix
    vector<vector<int>> key;
    stringstream ss(key_str);
    int num;
    while (ss >> num) {
        vector<int> row;
        row.push_back(num);
        for (int i = 1; i < 3; ++i) {
            ss >> num;
            row.push_back(num);
        }
        key.push_back(row);
    }

 
    string ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
