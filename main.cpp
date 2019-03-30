#include <iostream>
#include "MyList.h"
#include "MyMap.h"

void HelpEncrypt(MyMap<int, char> &encryptThis, MyMap<char, MyList<bool>> &encryptToThis) {
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
                encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount),true);
                calcCount++;
            }
            HelpEncrypt(trueGroup, encryptToThis);

            MyMap<int, char> falseGroup;
            while(calcCount < keysEncryptThis.GetSize()){
                falseGroup.Insert(keysEncryptThis.At(calcCount),valuesEncryptThis.At(calcCount));
                encryptToThis.IncreamentValueByKey(valuesEncryptThis.At(calcCount),false);
                calcCount++;
            }
            HelpEncrypt(falseGroup,encryptToThis);
        }
    }
}

MyMap<char, MyList<bool>> Encrypt(MyMap<int, char> &myMap) {
    MyMap<char, MyList<bool>> encrypted;

    MyList<char> symbols = myMap.GetValue();
    for(int i = 0; i < symbols.GetSize(); i++){
        encrypted.Insert(symbols.At(i),MyList<bool>());
    }

    HelpEncrypt(myMap,encrypted);


    return encrypted;
}

int main() {
    string inputString;
    cin >> inputString;

    MyMap<char, int> frequencyChar;

    for (int i = 0; i < inputString.size(); i++) {
        char key = inputString[i];
        if (frequencyChar.Find(key)) {
            frequencyChar.IncreamentValueByKey(key);
        } else {
            frequencyChar.Insert(key, 1);
        }
    }

    frequencyChar.ShowAsList();

    MyMap<int, char> sortedFrequencyChar;
    MyList<int> values = frequencyChar.GetValue();
    MyList<char> keys = frequencyChar.GetKeys();

    for(int i = 0; i < values.GetSize(); i++) {
        sortedFrequencyChar.Insert(values.At(i), keys.At(i));
    }

    MyMap<char, MyList<bool>> encryptSymbols = Encrypt(sortedFrequencyChar);

    encryptSymbols.ShowAsList();
    sortedFrequencyChar.ShowAsList();
}

