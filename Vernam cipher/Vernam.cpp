#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	srand(time(0));
	int option;
	string key;
	int const SIZE = 10;

	cout << "Enter the option number: 1 - encryption, 2 - decryption" << endl;
	cin >> option;

	if (option == 1)//encrypt
	{
		for (int i = 0; i < SIZE; i++)
		{
			key += (char)(65 + rand() % 26 + (rand() % 2) * 32);//сгенерированный ключ
		}
		cout << "Generated key: " << key << endl;

		ofstream KeyText("key.txt");//создаем файл для записи полученного ключа
		KeyText << key;
		KeyText.close();

		string text_enc;
		ifstream openText("text.txt");//считываем файл, который хотим зашифровать

		if (!openText.is_open())
		{
			cout << "Error! File not found!You need to create a text.txt file in the source folder!";
			return 1;
		}

		else
		{
			getline(openText, text_enc, '\0');//переводим файл в строку
			openText.close();

			int len_text = text_enc.length();//длина сообщения из текста
			int len_key = key.length();//длина ключа

			string cipher_enc;
			ofstream cipherText("cipher.txt");//создаем файл для записи шифра

			for (int i = 0; i < len_text; i++)
			{
				cipher_enc += (text_enc[i] ^ key[i % len_key]);//используем исключающее ИЛИ

			}

			cipherText << cipher_enc;//добовляем полученный шифр в файл
			cipherText.close();

			cout << "Received cipher: " << cipher_enc << endl;
		}
	}

	if (option == 2)//decrypt
	{
		string text_key;
		ifstream KeyText("key.txt");//считываем  файл с сохраненным ключом
		getline(KeyText, text_key, '\0');
		KeyText.close();

		int len_key = text_key.length();
		string text_dec;
		ifstream cipherText("cipher.txt");//считываем шифр из файла
		getline(cipherText, text_dec, '\0');
		cipherText.close();


		string cipher_dec;
		ofstream openText("text.txt");//открываем файл для записи расшифрованого текста

		for (int i = 0; i < text_dec.length(); i++)
		{
			cipher_dec += (text_dec[i] ^ text_key[i % len_key]);

		}
		openText << cipher_dec;
		openText.close();

		cout << "Decrypted text: " << " " << cipher_dec;

	}
	return 0;
}
