#include <bits/stdc++.h>
using namespace std;

// Convert hex string to binary string
string hexToBinary(const string &hex)
{
    string binary = "";
    for (char c : hex)
    {
        int value;
        if (c >= '0' && c <= '9')
        {
            value = c - '0';
        }
        else if (c >= 'a' && c <= 'f')
        {
            value = c - 'a' + 10;
        }
        else if (c >= 'A' && c <= 'F')
        {
            value = c - 'A' + 10;
        }
        else
        {
            continue; // Skip non-hex characters
        }

        // Convert to 4-bit binary
        for (int i = 3; i >= 0; i--)
        {
            binary += ((value >> i) & 1) ? '1' : '0';
        }
    }
    return binary;
}

// Count same bits between two binary strings
int countSameBits(const string &bin1, const string &bin2)
{
    int sameBits = 0;
    int minLength = min(bin1.length(), bin2.length());

    for (int i = 0; i < minLength; i++)
    {
        if (bin1[i] == bin2[i])
        {
            sameBits++;
        }
    }
    return sameBits;
}

// Calculate Hamming distance (different bits)
int hammingDistance(const string &bin1, const string &bin2)
{
    int diffBits = 0;
    int minLength = min(bin1.length(), bin2.length());

    for (int i = 0; i < minLength; i++)
    {
        if (bin1[i] != bin2[i])
        {
            diffBits++;
        }
    }
    return diffBits;
}

int main()
{
    // Original hash values (H1)
    string md5_h1 = "d05a9d071a556f5179847c89e9a4d791";
    string sha256_h1 = "cc6ed5ca06bb85101dd3ad653a880d02980d6c1a820cccb037f6e9cea6005ff5";

    // Modified hash values (H2)
    string md5_h2 = "b65ef3f75111e0d6e701378a21ff38f0";
    string sha256_h2 = "791581338b928ac8352e753d18ceb651a460453a25f4fd8890df531a1346eb63";

    cout << "=== Hash Comparison Analysis ===" << endl
         << endl;

    cout << "Original Hash Values (H1):" << endl;
    cout << "MD5:    " << md5_h1 << endl;
    cout << "SHA256: " << sha256_h1 << endl
         << endl;

    cout << "Modified Hash Values (H2):" << endl;
    cout << "MD5:    " << md5_h2 << endl;
    cout << "SHA256: " << sha256_h2 << endl
         << endl;

    // MD5 Analysis
    string md5_bin1 = hexToBinary(md5_h1);
    string md5_bin2 = hexToBinary(md5_h2);
    int md5_same = countSameBits(md5_bin1, md5_bin2);
    int md5_total = md5_bin1.length();
    int md5_diff = hammingDistance(md5_bin1, md5_bin2);

    cout << "=== MD5 Analysis ===" << endl;
    cout << "Total bits: " << md5_total << endl;
    cout << "Same bits: " << md5_same << endl;
    cout << "Different bits: " << md5_diff << endl;
    cout << "Similarity percentage: " << fixed << setprecision(2)
         << (double)md5_same / md5_total * 100 << "%" << endl;
    cout << "Difference percentage: " << fixed << setprecision(2)
         << (double)md5_diff / md5_total * 100 << "%" << endl
         << endl;

    // SHA256 Analysis
    string sha256_bin1 = hexToBinary(sha256_h1);
    string sha256_bin2 = hexToBinary(sha256_h2);
    int sha256_same = countSameBits(sha256_bin1, sha256_bin2);
    int sha256_total = sha256_bin1.length();
    int sha256_diff = hammingDistance(sha256_bin1, sha256_bin2);

    cout << "=== SHA256 Analysis ===" << endl;
    cout << "Total bits: " << sha256_total << endl;
    cout << "Same bits: " << sha256_same << endl;
    cout << "Different bits: " << sha256_diff << endl;
    cout << "Similarity percentage: " << fixed << setprecision(2)
         << (double)sha256_same / sha256_total * 100 << "%" << endl;
    cout << "Difference percentage: " << fixed << setprecision(2)
         << (double)sha256_diff / sha256_total * 100 << "%" << endl
         << endl;

    cout << "=== Avalanche Effect Analysis ===" << endl;
    cout << "A good cryptographic hash function should show the avalanche effect:" << endl;
    cout << "- Changing 1 bit in input should change ~50% of output bits" << endl;
    cout << "- MD5 changed " << md5_diff << "/" << md5_total << " bits ("
         << (double)md5_diff / md5_total * 100 << "%)" << endl;
    cout << "- SHA256 changed " << sha256_diff << "/" << sha256_total << " bits ("
         << (double)sha256_diff / sha256_total * 100 << "%)" << endl;

    return 0;
}