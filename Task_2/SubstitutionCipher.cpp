#include <bits/stdc++.h>
using namespace std;

string breakSubstitutionCipher(string cipher)
{
    // Count frequency of each letter
    map<char, int> frequency;

    // Convert to lowercase and count frequencies
    for (char ch : cipher)
    {
        char lowerCh = tolower(ch);
        if (lowerCh >= 'a' && lowerCh <= 'z')
        {
            frequency[lowerCh]++;
        }
    }

    // Create vector of pairs (character, frequency) and sort by frequency
    vector<pair<char, int>> sortedFrequency;
    for (auto &entry : frequency)
    {
        sortedFrequency.push_back({entry.first, entry.second});
    }

    // Sort by frequency (descending order)
    sort(sortedFrequency.begin(), sortedFrequency.end(),
         [](const pair<char, int> &a, const pair<char, int> &b)
         {
             return a.second > b.second;
         });

    // Extract common letters from sorted frequency
    vector<char> commonLetters;
    for (auto &entry : sortedFrequency)
    {
        commonLetters.push_back(entry.first);
    }

    // English letter frequency (most common to least common)
    string englishFrequency = "eotainshrdlcufwmpygbkqvjxz";

    // Create mapping from cipher letters to English letters
    map<char, char> mapping;
    for (int i = 0; i < commonLetters.size() && i < englishFrequency.length(); i++)
    {
        mapping[commonLetters[i]] = englishFrequency[i];
    }

    // Decrypt the cipher text
    string decrypted = "";
    for (char ch : cipher)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            // Lowercase letter
            if (mapping.find(ch) != mapping.end())
            {
                decrypted += mapping[ch];
            }
            else
            {
                decrypted += ch;
            }
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            // Uppercase letter
            char lowerCh = tolower(ch);
            if (mapping.find(lowerCh) != mapping.end())
            {
                decrypted += toupper(mapping[lowerCh]);
            }
            else
            {
                decrypted += ch;
            }
        }
        else
        {
            // Non-alphabetic character
            decrypted += ch;
        }
    }

    return decrypted;
}

int main()
{
    string cipher1 = "af p xpkcaqvnpk pfg, af ipqe qpri, gauuikifc tpw, ceiri udvk tiki afgarxifrphni cd eaowvmd popkwn, hiqpvri du ear jvaql vfgikrcpfgafm du cei xkafqaxnir du xrwqedearcdkw pfg du ear aopmafpcasi xkdhafmr afcd fit pkipr. ac tpr qdoudkcafm cd lfdt cepc au pfwceafm epxxifig cd ringdf eaorinu hiudki cei opceiopcaqr du cei uaing qdvng hi qdoxnicinw tdklig dvcpfg edt rndtnw ac xkdqiigig, pfg edt odvfcpafdvr cei dhrcpqnir--ceiki tdvng pc niprc kiopaf dfi mddg oafg cepc tdvng qdfcafvi cei kiripkqe";

    cout << "Original Cipher Text:" << endl;
    cout << cipher1 << endl
         << endl;

    string decryptedText = breakSubstitutionCipher(cipher1);

    cout << "Decryption for Cipher 1:" << endl;
    cout << decryptedText << endl;

    return 0;
}

/*
Expected Output:
Decryption for Cipher 1:
in a particular and, in each case, different way, these four were indispensable to himyugo amaryl, because of his quick understanding of the principles of psychohistory and of his imaginative probings into new areas. it was comforting to know that if anything happened to seldon himself before the mathematics of the field could be completely worked outand how slowly it proceeded, and how mountainous the obstacles--there would at least remain one good mind that would continue the research

Note: This is a frequency analysis attack on substitution cipher.
The algorithm maps the most frequent letters in the cipher to the most frequent letters in English.
*/
