#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int option;
	setlocale(LC_ALL, "Russian");
	cout << "Введите номер опции: 1 - шифрование, 2 - расшифровка" << endl;
	cin >> option;

	if (option == 1)//encrypt
	{
		string text_enc;
		ifstream openText("text.txt");

		if (!openText.is_open())
			cout << "Error! Файл не найден!";
		else
		{
			getline(openText, text_enc, '\0');//переводим файл в строку

			//cout << text_enc << endl;//здесь выводит почему-то пустую строку

			openText.close();

			string cipher_enc;
			string key;
			cout << "Введите ключ" << endl;
			cin >> key;

			ofstream cipherText("cipher.txt");

			if (key.length() != text_enc.length())
				cout << "Введенный ключ отличается от длины кодируемого сообщения" << endl;
			else
			{
				for (int i = 0; i < text_enc.length(); i++)
				{
					cipher_enc += (char)(text_enc[i] ^ key[i]);//используем исключающее ИЛИ
				}

				cout << "Полученный шифр" << ": " << cipher_enc;

				cipherText.close();
			}
		}
	}

	if (option == 2)//decrypt
	{
		string text_dec;
		ifstream cipherText("cipher.txt");
		getline(cipherText, text_dec, '\0');
		//cout << text_dec;// здесь почему-то выводит пустую строку
		cipherText.close();

		string cipher_dec;
		//string cipher;
		//cout << "Введите шифр...";
		//cin >> cipher;//можно конечно подставить шифр, но как реализовать
		//подставление полученной строки из файла?
		cout << text_dec;

		ofstream openText("text.txt");

		for (int i = 0; i < text_dec.length(); i++)
		{
			cipher_dec += (char)(text_dec[i] ^ text_dec[i]);
		}
		cout << "обрабатывается шифр" << endl;
		cout << "расшифрованное сообщение" << " " << cipher_dec;

		openText.close();
	}
	return 0;
}
