//////////////////////////////////////////
//		         Мочалин				//
//				 					    //
//				  Антон				    //
//										//
//			  Александрович				//
//////////////////////////////////////////
#include "modAlphaCipher.h"

using namespace std;
//Функции для более удобного написания

string enc (int k, string str)			//////////////////////////////////////////
{										//		         Функция				//
										//										//
    modAlphaCipher ex(k);				//				  для			        //
    string stroka = ex.encrypt(str); 	//										//
    return stroka;						//			  зашифрования				//
    									//							            //
}										//////////////////////////////////////////

string dec (int k, string str)			//////////////////////////////////////////
{										//		          Функция				//
										//										//
    modAlphaCipher ex(k);				//					для		            //
    string stroka = ex.decrypt(str); 	//										//
    return stroka;						//			   расшифрования			//
    									//										//
}										//////////////////////////////////////////


//Тесты ключей
SUITE (KeyTest)
{
    string test = "THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
    int k;
    TEST (ValidKey) {
        CHECK_EQUAL(enc(5,test),"UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ");
    }
    TEST(NegativeKey) {
        CHECK_THROW(enc(-8,test), cipher_error);
    }
    TEST(LargeKey) {
        CHECK_THROW(enc(100,test), cipher_error);
    }
}
//Тесты encrypt
SUITE(EncryptTest)
{
    TEST(ValidText) {
        CHECK_EQUAL(enc(5,"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG"),"UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ");
    }
    TEST(LowText) {
        CHECK_EQUAL(enc(5,"thequikbrownfoxjumpsovertherlazyDOG"),"uoxstaGqroprlOebfmerDhknuveytiwjohz");
    }
    TEST(SpaceText) {
        CHECK_THROW(enc(5,"THEQUICKBROWNFOX JUMPSOVERTHELAZYDOG"), cipher_error);
    }
    TEST(EmptyText) {
        CHECK_THROW(enc(5," "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(enc(5,"!*><?/,.123"),cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_THROW(enc(5,"THEQUICKBROWNFOXJUMP2024SOVERTHELAZYDOG"),cipher_error);
    }

}
//Тесты decrypt
SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(dec(5,"UROPRAGQBFMELOEKNUVEDHCWJOHYTIOXSTZ"),"THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG");
    }
    TEST(LowTEXT) {
        CHECK_EQUAL(dec(5,"uoxstaGqroprlOebfmerDhknuveytiwjohz"),"thequikbrownfoxjumpsovertherlazyDOG");
    }
    TEST(SpaceTEXT) {
        CHECK_THROW(dec(5,"UROPRAGQBFMELOEKN UVEDHCWJOHYTIOXSTZ"),cipher_error);
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(dec(5," "),cipher_error);
    }
    TEST(TextNumberText) {
        CHECK_THROW(dec(5,"QWER777TY"),cipher_error);
    }
    TEST(TextSymbolText) {
        CHECK_THROW(dec(5,"QWER???TY"),cipher_error);
    }

}

int main()
{
    return UnitTest::RunAllTests();
}
