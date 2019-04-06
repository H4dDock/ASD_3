#include <iostream>
#include "MyList.h"
#include "MyMap.h"
#include "EncodeStuff.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    string inputString, encryptedString, decodedString;
    getline(cin, inputString);

    encryptedString = EncodeThis(inputString);
    cout << "encrypted: "<< encryptedString << endl;

    MyMap<char, string> encryptSymbols = GetEncryptSymbols(inputString);

    decodedString = DecodeThis(encryptedString, encryptSymbols);
    cout << "decoded: " << decodedString << endl;

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

