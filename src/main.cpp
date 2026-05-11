#include "textgen.h"
int main()
{
	vector<string> allwords = ReadFromFile("training.txt");
	map<prefix, vector<string>> statetab = CreateTable(allwords, NPREF);
	Generate(statetab, MAXGEN);
}
