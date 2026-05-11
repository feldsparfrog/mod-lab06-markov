#pragma once
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
using namespace std;
#include <locale>
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include<random>
typedef deque<string> prefix; //очередь префиксов
const int NPREF = 2; //количество слов в префиксе
const int MAXGEN = 1200; //объем текста на выходе
vector<string> ReadFromFile(string filename);
prefix CreatePrefix(vector<string> allwords, int npref, int i);
vector<string> CreateSuffix(vector<string> allwords, int npref, prefix newprefix);
map<prefix, vector<string>> CreateTable(vector<string> allwords, int npref);
int RandomNumber(int maxnumber);
prefix GeneratePrefix(map<prefix, vector<string>> statetab);
string ChooseSuffix(map<prefix, vector<string>> statetab, prefix nextprefix);
void Generate(map<prefix, vector<string>> statetab, int maxgen);
#endif
