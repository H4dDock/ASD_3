#include "EncodeStuff.h"

void HelpEncrypt(MyMap<int, char> &encryptThis, MyMap<char, string> &encryptToThis) {
    if(!encryptThis.isEmpty()){
        if(encryptThis.GetValue().GetSize() != 1){
            bool flagNoOrderDelim = false;
            MyList<int> keysEncryptThis = encryptThis.GetKeys();
            MyList<char> valuesEncryptThis = encryptThis.GetValue();
            int sum = 0;
            for(int i = 0; i < keysEncryptThis.GetSize(); i++){
                if(i == keysEncryptThis.GetSize()-1){
                    if(keysEncryptThis.At(i) > sum){
                        flagNoOrderDelim = true;
                    }
                }
                sum += keysEncryptThis.At(i);
            }

            MyMap<int, char> trueGroup;
            MyMap<int, char> falseGroup;
            if(flagNoOrderDelim){
                for(int i = 0; i < keysEncryptThis.GetSize()-1; i++){
                    trueGroup.Insert(keysEncryptThis.At(i), valuesEncryptThis.At(i));
                    encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(i), "1");
                }
                HelpEncrypt(trueGroup, encryptToThis);

                falseGroup.Insert(keysEncryptThis.At(keysEncryptThis.GetSize()-1), valuesEncryptThis.At(keysEncryptThis.GetSize()-1));
                encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(keysEncryptThis.GetSize()-1), "0");
                HelpEncrypt(falseGroup, encryptToThis);
            }else {
                int trueSum = 0;
                int calcCount = 0;
                while (trueSum < sum / 2) {
                    trueGroup.Insert(keysEncryptThis.At(calcCount), valuesEncryptThis.At(calcCount));
                    trueSum += keysEncryptThis.At(calcCount);
                    encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount), "1");
                    calcCount++;
                }
                HelpEncrypt(trueGroup, encryptToThis);

                while (calcCount < keysEncryptThis.GetSize()) {
                    falseGroup.Insert(keysEncryptThis.At(calcCount), valuesEncryptThis.At(calcCount));
                    encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount), "0");
                    calcCount++;
                }
                HelpEncrypt(falseGroup, encryptToThis);
            }
            trueGroup.~MyMap();
            falseGroup.~MyMap();
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

/*MyMap<char, string> GetEncryptSymbols(MyMap<char, int> &frequencyChar){
    MyMap<int, char> sortedFrequencyChar;
    MyList<int> values = frequencyChar.GetValue();
    MyList<char> keys = frequencyChar.GetKeys();

    for(int i = 0; i < values.GetSize(); i++) {
        sortedFrequencyChar.Insert(values.At(i), keys.At(i));
    }

    MyMap<char, string> encryptSymbols = Encrypt(sortedFrequencyChar);
    return encryptSymbols;
}*/

MyMap<char, string> GetEncryptSymbols(string inputString){
    MyMap<char, int> frequencyChar;

    for (int i = 0; i < inputString.size(); i++) {
        char key = inputString[i];
        if (frequencyChar.Find(key)) {
            frequencyChar.IncreamentValueByKey(key);
        } else {
            frequencyChar.Insert(key, 1);
        }
    }

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

string EncodeThis(string input){
    MyMap<char, string> encryptSymbols = GetEncryptSymbols(input);

    MyList<string> valuesEncrypt = encryptSymbols.GetValue();
    MyList<char> keysEncrypt = encryptSymbols.GetKeys();

    return GetEncodeString(input,keysEncrypt,valuesEncrypt);
}

string DecodeThis(string encodeInput, MyMap<char, string> &encryptSymbols){
    MyList<string> valuesEncrypt = encryptSymbols.GetValue();
    MyList<char> keysEncrypt = encryptSymbols.GetKeys();

    return GetDecodedString(encodeInput,valuesEncrypt,keysEncrypt);
}