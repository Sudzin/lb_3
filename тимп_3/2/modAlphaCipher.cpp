//////////////////////////////////////////
//		         Мочалин				//
//				 					    //
//				  Антон				    //
//										//
//			  Александрович				//
//////////////////////////////////////////
#include "modAlphaCipher.h"
string modAlphaCipher::decrypt(const string& cipher_text) 
{
	string open_text = getValidOpenText(cipher_text);
    string decrypted_text = open_text;
    int text_length, position, line, i; 
    text_length = cipher_text.size(); 
    line = (text_length - 1) / newkey + 1; 
    i = 0;
    for (int column = newkey; column > 0; column--) { 
        for (int row = 0; row < line; row++) { 
            position = newkey * row + column; 
            if (position - 1 < text_length) {
                decrypted_text[position - 1] = cipher_text[i];
                i++;
            }
        }
    }
    return decrypted_text;
}
string modAlphaCipher::encrypt(const string& open_text) 
{
	string valid_open_text = getValidOpenText(open_text);
    string encrypted_text = valid_open_text;
    int text_length, line, position, i; 
    text_length = open_text.size(); 
    line = (text_length - 1) / newkey + 1; 
    i = 0;
    for (int column = newkey; column > 0; column--) { 
        for (int row = 0; row < line; row++) { 
            position = column + newkey * row;
            if (position - 1 < text_length) {
                encrypted_text[i] = open_text[position - 1];
                i++;
            }
        }
    }
    return encrypted_text;
}
inline string modAlphaCipher::getValidOpenText(const string & text)
{
	if (text.empty()) {
        throw cipher_error("Input text cannot be empty");
    }
    // Проверка длины ключа
    if (static_cast<std::string::size_type>(newkey) > text.length()) {
        throw cipher_error("Invalid key");
    }
    // Проверка на недопустимые символы
    for (char c : text) {
        if (!isalpha(c)) {
            throw cipher_error("Invalid characters");
        }
    }
    // Возвращаем длину строки, если все проверки пройдены
    return text;
}
