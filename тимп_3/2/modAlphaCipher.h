#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <UnitTest++/UnitTest++.h>
using namespace std;

class modAlphaCipher
{
private:
    int newkey;
    string getValidOpenText(const string & s);
public:
    modAlphaCipher()=delete;
    modAlphaCipher(const int& key) :newkey(key) {};
    //modAlphaCipher(const string& skey);
    //modAlphaCipher(const int k) 
    string encrypt(const string& open_st);   
    string decrypt(const string& cipher_st);
    //static int getValidKey(const std::string & s);
};
class cipher_error: public invalid_argument {
public:
	explicit cipher_error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		invalid_argument(what_arg) {}
};
