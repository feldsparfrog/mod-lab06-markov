// Copyright 2021 GHA Test Team
#pragma once
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_
#include <locale>
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include<random>
typedef std::deque<std::string> prefix;
const int NPREF = 2;
const int MAXGEN = 1200;
std::vector<std::string> ReadFromFile(std::string filename);
prefix CreatePrefix(std::vector<std::string> allwords, int npref, int i);
std::vector<std::string> CreateSuffix(
    std::vector<std::string> allwords,int npref, prefix newprefix);
std::map<prefix, std::vector<std::string>> CreateTable(
    std::vector<std::string> allwords, int npref);
int RandomNumber(int maxnumber);
prefix GeneratePrefix(std::map<prefix, std::vector<std::string>> statetab);
std::string ChooseSuffix(
    std::map<prefix, std::vector<std::string>> statetab, prefix nextprefix);
void Generate(std::map<prefix, std::vector<std::string>> statetab, int maxgen);
#endif
