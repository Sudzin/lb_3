#include "modAlphaCipher.h"
using namespace std;
void check(const string& Text, const string& key)
{
	try {
		string cipherText;
		string decryptedText;
		if (key.empty())
            throw cipher_error("Empty key");
        if (stoi(key) > 1) {
            modAlphaCipher cipher(stoi(key));
            cipherText = cipher.encrypt(Text);
            decryptedText = cipher.decrypt(cipherText);
			cout<<"key="<<key<<endl;
			cout<<cipherText<<endl;
			cout<<decryptedText<<endl;
		}else
			throw cipher_error(std::string("Invalid key ")+key);

	
 	} catch (const cipher_error & e) {
 		cerr<<"Error: "<<e.what()<<endl;
 }
}
int main()
{
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","0");
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","");
    check("THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG","5");
    check("thequikbrownfoxjumpsovertherlazyDOG","5");
    check("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG","100");
}
