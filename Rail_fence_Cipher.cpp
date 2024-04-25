#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to encrypt plaintext using Rail Fence cipher
string encryptRailFence(const string& plaintext, int rails) {
    vector<string> fence(rails, "");
    int rail = 0;
    bool down = false;

    // Fill the fence
    for (char c : plaintext) {
        fence[rail] += c;
        if (rail == 0 || rail == rails - 1) {
            down = !down;
        }
        rail += down ? 1 : -1;
    }

    // Concatenate rows to form ciphertext
    string ciphertext;
    for (const string& row : fence) {
        ciphertext += row;
    }
    return ciphertext;
}

int main() {
    string plaintext;
    int rails;

    // Input plaintext and number of rails
    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter number of rails: ";
    cin >> rails;

    // Encrypt plaintext
    string ciphertext = encryptRailFence(plaintext, rails);

    // Output ciphertext
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
