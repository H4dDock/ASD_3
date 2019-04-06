//
// Created by max on 09.03.19.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../MyMap.h"
#include "../EncodeStuff.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test{
    public:
        ClassDeclaration(){
        }
    };
}

TEST_F(ClassDeclaration, Encrypt_Test){
    MyMap<int, char> input;

    input.Insert(1,'a');
    input.Insert(2,'b');
    input.Insert(3,'c');

    MyMap<char, string> expect;

    expect.Insert('a',"11");
    expect.Insert('b',"10");
    expect.Insert('c',"0");

    MyMap<char, string> real = Encrypt(input);

    ASSERT_EQ(real.Find('a')->GetValue(),expect.Find('a')->GetValue());
    ASSERT_EQ(real.Find('b')->GetValue(),expect.Find('b')->GetValue());
    ASSERT_EQ(real.Find('c')->GetValue(),expect.Find('c')->GetValue());
}

TEST_F(ClassDeclaration, Encrypt_Test_Critical1){
    MyMap<int, char> input;

    input.Insert(1,'a');
    input.Insert(1,'b');
    input.Insert(5,'c');

    MyMap<char, string> expect;

    expect.Insert('a',"11");
    expect.Insert('b',"10");
    expect.Insert('c',"0");

    MyMap<char, string> real = Encrypt(input);

    ASSERT_EQ(real.Find('a')->GetValue(),expect.Find('a')->GetValue());
    ASSERT_EQ(real.Find('b')->GetValue(),expect.Find('b')->GetValue());
    ASSERT_EQ(real.Find('c')->GetValue(),expect.Find('c')->GetValue());
}

TEST_F(ClassDeclaration, Encrypt_Test_Critical2){
    MyMap<int, char> input;

    input.Insert(1,'a');
    input.Insert(1,'b');
    input.Insert(1,'c');

    MyMap<char, string> expect;

    expect.Insert('a',"1");
    expect.Insert('b',"01");
    expect.Insert('c',"00");

    MyMap<char, string> real = Encrypt(input);

    ASSERT_EQ(real.Find('a')->GetValue(),expect.Find('a')->GetValue());
    ASSERT_EQ(real.Find('b')->GetValue(),expect.Find('b')->GetValue());
    ASSERT_EQ(real.Find('c')->GetValue(),expect.Find('c')->GetValue());
}

TEST_F(ClassDeclaration, CompleteFrequency_Test){
    string input = "qwweeerrrr";

    MyMap<char, int> expect;
    expect.Insert('q',1);
    expect.Insert('w',2);
    expect.Insert('e',3);
    expect.Insert('r',4);

    MyMap<char, int> real = CompleteFrequency(input);
    ASSERT_EQ(real.Find('q')->GetValue(),expect.Find('q')->GetValue());
    ASSERT_EQ(real.Find('w')->GetValue(),expect.Find('w')->GetValue());
    ASSERT_EQ(real.Find('e')->GetValue(),expect.Find('e')->GetValue());
    ASSERT_EQ(real.Find('r')->GetValue(),expect.Find('r')->GetValue());
}

TEST_F(ClassDeclaration, CompleteFrequency_Test_Critical){
    string input = "";

    MyMap<char, int> expect;

    MyMap<char, int> real = CompleteFrequency(input);
    ASSERT_EQ(expect.GetValue().GetSize(),real.GetValue().GetSize());
}

TEST_F(ClassDeclaration, GetEncryptSymbols_Test){
    string input = "qwweeerrrr";

    MyMap<char, string> expect;

    expect.Insert('q',"111");
    expect.Insert('w',"110");
    expect.Insert('e',"10");
    expect.Insert('r',"0");

    MyMap<char, string> real = GetEncryptSymbols(input);
    ASSERT_EQ(real.Find('q')->GetValue(),expect.Find('q')->GetValue());
    ASSERT_EQ(real.Find('w')->GetValue(),expect.Find('w')->GetValue());
    ASSERT_EQ(real.Find('e')->GetValue(),expect.Find('e')->GetValue());
    ASSERT_EQ(real.Find('r')->GetValue(),expect.Find('r')->GetValue());
}

TEST_F(ClassDeclaration, GetSumOfBite_Test){
    MyList<string> code;
    code.PushFront("11");
    code.PushFront("10");
    code.PushFront("0");

    MyList<int> referCode;
    referCode.PushFront(5);
    referCode.PushFront(2);
    referCode.PushFront(1);

    ASSERT_EQ(15,GetSumOfBite(code, referCode));
}

TEST_F(ClassDeclaration, GetEncodeString_Test){
    string input = "qwe";

    MyList<char> keys;
    keys.PushFront('q');
    keys.PushFront('w');
    keys.PushFront('e');

    MyList<string> valuesEncrypt;
    valuesEncrypt.PushFront("01");
    valuesEncrypt.PushFront("00");
    valuesEncrypt.PushFront("1");

    ASSERT_EQ("01001",GetEncodeString(input,keys,valuesEncrypt));
}

TEST_F(ClassDeclaration, GetDecodedString_Test){
    string input = "01001";

    MyList<char> keys;
    keys.PushFront('q');
    keys.PushFront('w');
    keys.PushFront('e');

    MyList<string> valuesEncrypt;
    valuesEncrypt.PushFront("01");
    valuesEncrypt.PushFront("00");
    valuesEncrypt.PushFront("1");

    ASSERT_EQ("qwe",GetDecodedString(input, valuesEncrypt, keys));
}

TEST_F(ClassDeclaration, EncodeThis_Test){
    string input = "qwe";

    ASSERT_EQ("01001",EncodeThis(input));
}

TEST_F(ClassDeclaration, DecodeThis_Test){
    string input = "01001";

    MyMap<char, string> encryptSymbols;
    encryptSymbols.Insert('q',"01");
    encryptSymbols.Insert('w',"00");
    encryptSymbols.Insert('e',"1");

    ASSERT_EQ("qwe",DecodeThis(input,encryptSymbols));
}



