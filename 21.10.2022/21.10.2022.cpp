#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int main()
{
	string path;
	fstream fileR;

	while (true)
	{
		cout << "Enter path: ";
		cin >> path;

		if (cin.good())
		{
			fileR.open(path, ios::in);
			if (fileR.is_open()) break;
		}

		cin.clear();
		cin.ignore(32767, '\n');
	}

	map<string, int> dictionary;
	string buffer;

	while (!fileR.eof()) 
	{
		fileR >> buffer;
		auto it = dictionary.find(buffer);

		if (it == dictionary.end()) dictionary.emplace(buffer, 1);
		else it->second++;
	}

	fileR.close();
	
	multimap<int, string> sorted_result;
	for (auto it = dictionary.begin(); it != dictionary.end(); it++)
		if (it->second > 2) sorted_result.emplace(it->second, it->first);

	fstream fileW("result.txt", ios::out);

	if (fileW.is_open())
		for (auto it = sorted_result.rbegin(); it != sorted_result.rend(); it++)
		{
			cout << it->first << "\t\t" << it->second << endl;
			fileW << it->first << "\t\t" << it->second << endl;
		}

	fileW.close();
}