#include<bits/stdc++.h>
#define ll long long
using namespace std;

string encrypt(string plaintext, string key) {
    string ciphertext = "";
    int keyLength = key.length();
    for (int i = 0, j = 0; i < plaintext.length(); ++i) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ciphertext += (char)(((c + key[j] - 2 * base) % 26) + base);
            j = (j + 1) % keyLength;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

int main() {
    string plaintext, key;

    
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter key: ";
    cin >> key;

    string ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}