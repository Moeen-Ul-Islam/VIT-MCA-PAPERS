#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> convertToBinary(string message)
{
	vector<string> stringInBinary;

	for (int i = 0; i < message.length(); i++)
	{
		int ascii = int(message[i]);

		string binary;

		while (ascii > 0)
		{
			if (ascii % 2)
				binary.push_back('1');
			else
				binary.push_back('0');

			ascii /= 2;
		}

		reverse(binary.begin(), binary.end());

		stringInBinary.push_back(binary);
	}

	return stringInBinary;
}

string sender(string message, vector<string> messageInBinary)
{
	string sum, checkSum;

	for (int i = 0; i < messageInBinary.size() - 1; i++)
	{
		string a = (i == 0) ? messageInBinary[i] : sum;
		string b = messageInBinary[i + 1];

		int carryOver = '0';

		sum = "";

		for (int j = a.length() - 1; j >= 0; j--)
		{

			int firstBit = a[j] - '0';
			int secondBit = b[j] - '0';

			int addition = (firstBit ^ secondBit ^ carryOver) + '0';

			sum += char(addition);

			carryOver = (firstBit & secondBit) | (secondBit & carryOver) | (firstBit & carryOver);
		}

		if (carryOver == '1')
			sum = '1' + sum;
	}

	for (char &c : sum)
	{
		if (c == '1')
			checkSum.push_back('0');
		else
			checkSum.push_back('1');
	}

	cout << checkSum << " : CheckSum\n";

	return checkSum;
}

bool receiver(string checkSum, vector<string> messageInBinary)
{
	string sum;

	char carryOver = '0';

	for (int i = 0; i < messageInBinary.size(); i++)
	{
		sum = "";

		if (i == messageInBinary.size() - 1)
		{
			string a = sum;
			string b = checkSum;

			for (int j = a.length() - 1; j >= 0; j--)
			{

				int firstBit = a[j] - '0';
				int secondBit = b[j] - '0';

				int addition = (firstBit ^ secondBit ^ carryOver) + '0';

				sum += char(addition);
			}

			if (carryOver)
				sum = '1' + sum;
		}
		else
		{
			string a = (i == 0) ? messageInBinary[i] : sum;
			string b = messageInBinary[i + 1];

			for (int j = a.length() - 1; j >= 0; j--)
			{

				int firstBit = a[j] - '0';
				int secondBit = b[j] - '0';

				int addition = (firstBit ^ secondBit ^ carryOver) + '0';

				sum += char(addition);
			}

			if (carryOver)
				sum = '1' + sum;
		}
	}

	for (char &c : sum)
	{
		if (c == '1')
			c = '0';
		else
			c = '1';
	}

	for (char &c : sum)
		if (c == '1')
			return false;

	return true;
}

void checkSum(string message)
{
	vector<string> messageInBinary = convertToBinary(message);

	string checkSum = sender(message, messageInBinary);
	bool isSame = receiver(checkSum, messageInBinary);

	if (isSame)
		cout << "Hurray... The message is sent to the receiver without any errors!\n";
	else
		cout << "Ahh... It looks like the message is corrupted!\n";

	return;
}

int main()
{
	string message;

	cout << "Enter the message: ";
	cin >> message;

	checkSum(message);

	return 0;
}