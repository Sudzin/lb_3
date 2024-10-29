#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <typeinfo>
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"\nkey = " << key << endl;
        wcout << L"Text = " << Text << endl;
        wcout << L"Encrypted text: " << cipherText << endl;
        wcout << L"Decrypted text: " << decryptedText << "\n" << endl;
    } catch (const cipher_error & e) {
        wcerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","0");
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","");
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","5");
    check("thequikbrownfoxjumpsovertherlazyDOG","5");
    check("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG","100");
}
