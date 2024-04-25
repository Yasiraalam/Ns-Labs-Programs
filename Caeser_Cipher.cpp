#include<bits/stdc++.h>
#define ll long long
using namespace std;


string encrypt(string plaintext, int shift) {
    string ciphertext = "";
    for (char& c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = ((c - base + shift) % 26) + base;
        }
        ciphertext += c;
    }
    return ciphertext;
}

int main() {
    string plaintext;
    int shift;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter shift value: ";
    cin >> shift;

    string ciphertext = encrypt(plaintext, shift);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
