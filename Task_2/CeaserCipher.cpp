#include <bits/stdc++.h>
using namespace std;

string caesarCipherDecrypt(string text, int shift) {
    string decrypted = "";
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            int base = (ch >= 'A' && ch <= 'Z') ? 65 : 97;
            ch = ((ch - base - shift + 26) % 26) + base;
        }
        decrypted += ch;
    }
    return decrypted;
}

int main() {
    string encryptedText = "odroboewscdrolocdcwkbdmyxdbkmdzvkdpybwyeddrobo";
    
    cout << "Caesar Cipher Decryption - All Possible Shifts:\n\n";
    
    for (int shift = 1; shift < 26; shift++) {
        string decryptedText = caesarCipherDecrypt(encryptedText, shift);
        cout << "Shift " << shift << ": " << decryptedText << endl;
    }
    
    return 0;
}

/*
Expected Output:
Shift 1: ncqnandvrbcqnknbcbvjaclxwcajlcyujcoxavxdccqnan
Shift 2: mbpmzmcuqabpmjmabauizbkwvbzikbxtibnwzuwcbbpmzm
Shift 3: laolylbtpzaolilzazthyajvuayhjawshamvytvbaaolyl
Shift 4: kznkxkasoyznkhkyzysgxziutzxgizvrgzluxsuazznkxk
Shift 5: jymjwjzrnxymjgjxyxrfwyhtsywfhyuqfyktwrtzyymjwj
Shift 6: ixliviyqmwxlifiwxwqevxgsrxvegxtpexjsvqsyxxlivi
Shift 7: hwkhuhxplvwkhehvwvpduwfrqwudfwsodwiruprxwwkhuh
Shift 8: gvjgtgwokuvjgdguvuoctveqpvtcevrncvhqtoqwvvjgtg
Shift 9: fuifsfvnjtuifcftutnbsudpousbduqmbugpsnpvuuifsf
Shift 10: ethereumisthebestsmartcontractplatformoutthere
Shift 11: dsgdqdtlhrsgdadrsrlzqsbnmsqzbsokzsenqlntssgdqd
Shift 12: crfcpcskgqrfczcqrqkypramlrpyarnjyrdmpkmsrrfcpc
Shift 13: bqebobrjfpqebybpqpjxoqzlkqoxzqmixqclojlrqqebob
Shift 14: apdanaqieopdaxaopoiwnpykjpnwyplhwpbknikqppdana
Shift 15: zoczmzphdnoczwznonhvmoxjiomvxokgvoajmhjpooczmz
Shift 16: ynbylyogcmnbyvymnmgulnwihnluwnjfunzilgionnbyly
Shift 17: xmaxkxnfblmaxuxlmlftkmvhgmktvmietmyhkfhnmmaxkx
Shift 18: wlzwjwmeaklzwtwklkesjlugfljsulhdslxgjegmllzwjw
Shift 19: vkyvivldzjkyvsvjkjdriktfekirtkgcrkwfidflkkyviv
Shift 20: ujxuhukcyijxuruijicqhjsedjhqsjfbqjvehcekjjxuhu
Shift 21: tiwtgtjbxhiwtqthihbpgirdcigprieapiudgbdjiiwtgt
Shift 22: shvsfsiawghvspsghgaofhqcbhfoqhdzohtcfacihhvsfs
Shift 23: rgurerhzvfgurorfgfznegpbagenpgcyngsbezbhggurer
Shift 24: qftqdqgyueftqnqefeymdfoazfdmofbxmfradyagfftqdq
Shift 25: pespcpfxtdespmpdedxlcenzyeclneawleqzcxzfeespcp

Note: Shift 10 reveals "ethereumisthebestsmartcontractplatformoutthere"
*/