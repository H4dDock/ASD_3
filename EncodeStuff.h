//
// Created by max on 03.04.19.
//

#ifndef ASD_3_ENCODESTUFF_H
#define ASD_3_ENCODESTUFF_H

#include "MyMap.h"

void HelpEncrypt(MyMap<int, char> &encryptThis, MyMap<char, string> &encryptToThis);

MyMap<char, string> Encrypt(MyMap<int, char> &myMap);

MyMap<char, int> CompleteFrequency(string inputString);

MyMap<char, string> GetEncryptSymbols(string inputString);

int GetSumOfBite(MyList<string> &valuesEncrypt, MyList<int> &values);

string GetEncodeString(string inputString, MyList<char> &keys, MyList<string> &valuesEncrypt);

string GetDecodedString(string encryptedString,MyList<string> &valuesEncrypt, MyList<char> &keysEncrypt);

string EncodeThis(string input);

string DecodeThis(string encodeInput, MyMap<char, string> &encryptSymbols);
#endif //ASD_3_ENCODESTUFF_H
