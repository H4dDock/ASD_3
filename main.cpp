#include <iostream>
#include "MyList.h"
#include "MyMap.h"
#include "EncodeStuff.h"

int main() {
    string inputString, encryptedString, decodedString;
    cin >> inputString;
    cout << inputString.size()*8 << "\n";

    MyMap<char, int> frequencyChar = CompleteFrequency(inputString);
    MyMap<char, string> encryptSymbols = GetEncryptSymbols(frequencyChar);

    frequencyChar.ShowAsList();
    encryptSymbols.ShowAsList();

    MyList<char> keysEncrypt = encryptSymbols.GetKeys();
    MyList<string> valuesEncrypt = encryptSymbols.GetValue();
    MyList<int> values = frequencyChar.GetValue();
    MyList<char> keys = frequencyChar.GetKeys();

    int sum = GetSumOfBite(valuesEncrypt,values);
    cout << "\n" << sum << "\n";

    encryptedString = GetEncodeString(inputString,keys,valuesEncrypt);
    cout << "encrypted: "<< encryptedString << endl;


    decodedString = GetDecodedString(encryptedString,valuesEncrypt,keysEncrypt);
    cout << "decoded: " << decodedString;
}

