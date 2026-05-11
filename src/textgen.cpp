#include "textgen.h"
vector<string> ReadFromFile(string filename)
{
	vector<string> allwords;
	setlocale(LC_ALL, "Russian");
	ifstream file;
	file.open(filename);
	string word;
	while (file >> word)
	{
		allwords.push_back(word);
	}
	file.close();
	return allwords;
}
prefix CreatePrefix(vector<string> allwords, int npref, int i)
{
	prefix newprefix;
	for (int j = i; j < i + npref; j++)
	{
		newprefix.push_back(allwords[j]);
	}
	return newprefix;
}
vector<string> CreateSuffix(vector<string> allwords, int npref, prefix newprefix)
{
	vector<string> newsuffix;
	for (int j = npref; j < allwords.size(); j++)
	{
		if (newprefix.back() == allwords[j - 1]) newsuffix.push_back(allwords[j]);
	}
	return newsuffix;
}
map<prefix, vector<string>> CreateTable(vector<string> allwords, int npref)
{
	map<prefix, vector<string>> statetab; //префикс-суффиксы
	for (int i = 0; i < allwords.size() - npref; i++)
	{
		prefix newprefix = CreatePrefix(allwords, npref, i);
		vector<string> newsuffix = CreateSuffix(allwords, npref, newprefix);
		statetab[newprefix] = newsuffix;
	}
	return statetab;
}
int RandomNumber(int maxnumber)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, maxnumber);
	return dis(gen);
}
prefix GeneratePrefix(map<prefix, vector<string>> statetab)
{
	prefix nextprefix;
	int startposition = RandomNumber(statetab.size() - 1);
	auto element = statetab.begin();
	advance(element, startposition);
	for (int i = 0; i < element->first.size(); i++)
	{
		nextprefix.push_back(element->first.at(i));
	}
	return nextprefix;
}
string ChooseSuffix(map<prefix, vector<string>> statetab, prefix nextprefix)
{
	int suffixindex = RandomNumber(statetab[nextprefix].size() - 1);
	string chosensuffix = statetab[nextprefix][suffixindex];
	return chosensuffix;
}
void Generate(map<prefix, vector<string>> statetab, int maxgen)
{
	ofstream file;
	file.open("gen.txt");
	int wordcount = 0;
	prefix nextprefix = GeneratePrefix(statetab);
	for (int i = 0; i < nextprefix.size(); i++)
	{
		if (wordcount < maxgen - 1)
		{
			cout << nextprefix.at(i) << " ";
			file << nextprefix.at(i) << " ";
			wordcount++;
		}
	}
	while (wordcount < maxgen)
	{
		while (statetab[nextprefix].size() == 0)
		{
			nextprefix.clear();
			nextprefix = GeneratePrefix(statetab);
			for (int i = 0; i < nextprefix.size(); i++)
			{
				if (wordcount < maxgen - 1)
				{
					cout << nextprefix.at(i) << " ";
					file << nextprefix.at(i) << " ";
					wordcount++;
				}
			}
		}
		string chosensuffix = ChooseSuffix(statetab, nextprefix);
		cout << chosensuffix << " ";
		file << chosensuffix << " ";
		wordcount++;
		nextprefix.pop_front();
		nextprefix.push_back(chosensuffix);
	}
	file.close();
}
