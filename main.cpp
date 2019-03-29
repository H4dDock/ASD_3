#include <iostream>
#include "MyList.h"
#include "MyMap.h"

int main() {
    string inputString;
    cin>>inputString;

    MyMap<char,int> frequencyChar;

    for(int i = 0; i < inputString.size(); i++){
        char key = inputString[i];
        if(frequencyChar.Find(key)){
            frequencyChar.IncreamentValueByKey(key);
        }else{
            frequencyChar.Insert(key,1);
        }
    }

    frequencyChar.ShowAsList();
}