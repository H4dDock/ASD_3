//
// Created by max on 03.04.19.
//

#ifndef ASD_3_ENCODESTUFF_H
#define ASD_3_ENCODESTUFF_H

#include "MyMap.h"

void HelpEncrypt(MyMap<int, char> &encryptThis, MyMap<char, string> &encryptToThis) {
    if(!encryptThis.isEmpty()){
        if(encryptThis.GetValue().GetSize() == 1){

        }else{
            MyList<int> keysEncryptThis = encryptThis.GetKeys();
            MyList<char> valuesEncryptThis = encryptThis.GetValue();
            int sum = 0;
            for(int i = 0; i < keysEncryptThis.GetSize(); i++){
                sum += keysEncryptThis.At(i);
            }

            MyMap<int, char> trueGroup;
            int trueSum = 0;
            int calcCount = 0;
            while(trueSum < sum/2){
                trueGroup.Insert(keysEncryptThis.At(calcCount),valuesEncryptThis.At(calcCount));
                trueSum += keysEncryptThis.At(calcCount);
                encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount),"1");
                calcCount++;
            }
            HelpEncrypt(trueGroup, encryptToThis);

            MyMap<int, char> falseGroup;
            while(calcCount < keysEncryptThis.GetSize()){
                falseGroup.Insert(keysEncryptThis.At(calcCount),valuesEncryptThis.At(calcCount));
                encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount),"0");
                calcCount++;
            }
            HelpEncrypt(falseGroup,encryptToThis);
        }
    }
}

MyMap<char, string> Encrypt(MyMap<int, char> &myMap) {
    MyMap<char, string> encrypted;

    MyList<char> symbols = myMap.GetValue();
    for(int i = 0; i < symbols.GetSize(); i++){
        encrypted.Insert(symbols.At(i),"");
    }

    HelpEncrypt(myMap,encrypted);


    return encrypted;
}

MyMap<char, int> CompleteFrequency(string inputString){
    MyMap<char, int> frequencyChar;

    for (int i = 0; i < inputString.size(); i++) {
        char key = inputString[i];
        if (frequencyChar.Find(key)) {
            frequencyChar.IncreamentValueByKey(key);
        } else {
            frequencyChar.Insert(key, 1);
        }
    }
    return frequencyChar;
}

MyMap<char, string> GetEncryptSymbols(MyMap<char, int> &frequencyChar){
    MyMap<int, char> sortedFrequencyChar;
    MyList<int> values = frequencyChar.GetValue();
    MyList<char> keys = frequencyChar.GetKeys();

    for(int i = 0; i < values.GetSize(); i++) {
        sortedFrequencyChar.Insert(values.At(i), keys.At(i));
    }

    MyMap<char, string> encryptSymbols = Encrypt(sortedFrequencyChar);
    return encryptSymbols;
}

int GetSumOfBite(MyList<string> &valuesEncrypt, MyList<int> &values){
    int sum = 0;
    for(int i = 0; i < values.GetSize(); i++) {
        sum += values.At(i)*valuesEncrypt.At(i).size();
    }
    return sum;
}

string GetEncodeString(string inputString, MyList<char> &keys, MyList<string> &valuesEncrypt){
    string encryptedString;
    for (int i = 0; i < inputString.size(); i++) {
        for(int j = 0; j < keys.GetSize(); j++){
            if(keys.At(j) == inputString[i]){
                encryptedString += valuesEncrypt.At(j);
                break;
            }
        }
    }
    return encryptedString;
}

string GetDecodedString(string encryptedString,MyList<string> &valuesEncrypt, MyList<char> &keysEncrypt){
    string buffer, decodedString;
    for(int i = 0; i < encryptedString.size(); i++){
        buffer += encryptedString[i];
        for(int j = 0; j < valuesEncrypt.GetSize(); j++){
            if(buffer == valuesEncrypt.At(j)){
                decodedString += keysEncrypt.At(j);
                buffer = "";
                break;
            }
        }
    }
    return decodedString;
}

#endif //ASD_3_ENCODESTUFF_H
