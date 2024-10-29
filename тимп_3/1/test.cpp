#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <cctype>
#include <UnitTest++/TestReporterStdout.h>
#include "modAlphaCipher.h"
using namespace std;

auto RunSuite (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

SUITE(KeyTest){
    
    TEST(test1) {
        CHECK(modAlphaCipher(L"КЛЮЧ").encrypt(L"ИБСТ")==L"УМПЙ");
    }
    TEST(test2) {
        CHECK(modAlphaCipher(L"ПЫЛЕВОДОНЕПРОНИЦАЕМЫЙ").encrypt(L"МАЙ")==L"ЬЫХ");
    }
    TEST(test3) {
        CHECK(modAlphaCipher(L"ключ").encrypt(L"ИБСТ")==L"УМПЙ");
    }
    TEST(test4) {
        CHECK_THROW(modAlphaCipher(L"ДОТЕР1"), cipher_error);
    }
    TEST(test5) {
        CHECK_THROW(modAlphaCipher(L"ДО,ЕР1"), cipher_error);
    }
    TEST(test6) {
        CHECK_THROW(modAlphaCipher(L"ДО ЕР1"), cipher_error);
    }
    TEST(test7) {
        CHECK_THROW(modAlphaCipher(L""), cipher_error);
    }
};
struct KeyB_fixture {
modAlphaCipher * p;
KeyB_fixture()
{ p = new modAlphaCipher(L"В");
}
~KeyB_fixture()
{ delete p;
}
};
SUITE(EncryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"));
        }
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБ ВГДЕЁЖЗИЙ КЛМНОПРСТУФХ ЦЧШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, Numbers) {
        CHECK(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ" == p->encrypt(L"АБВГ777ДЕЁЖЗИЙКЛМНО2024ПРСТУФХЦЧ777ШЩЪЫЬЭЮЯ"));
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->encrypt(L"777,7777?777"), cipher_error);
        }
    TEST(MaxShiftKey) {
        CHECK(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ" == modAlphaCipher(L"Я").encrypt(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"));
        }
};
SUITE(DecryptTest)
    {TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == p->decrypt(L"ВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯАБ"));
        }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, WhitSpace) {
        CHECK_THROW(p->decrypt(L"АБВГД ЕЁЖЗИЙК ЛМНОПРСТ УФХЦЧШЩЪЫЬЭЮ Я"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Digit) {
        CHECK_THROW(p->decrypt(L"В004КО58"), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Punct) {
        CHECK_THROW(p->decrypt(L"ВАДИМ+#* "), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, Empty) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
        }
    TEST_FIXTURE(KeyB_fixture, NoAlpha) {
        CHECK_THROW(p->decrypt(L"34845/'/'/'"), cipher_error);
        }
    TEST(MaxShiftKey) {
        CHECK(L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" == modAlphaCipher(L"Я").decrypt(L"ЯАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮ"));
        }
};

int main() {
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    return UnitTest::RunAllTests();
}
