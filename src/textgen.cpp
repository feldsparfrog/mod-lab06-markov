// Copyright 2021 GHA Test Team
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "textgen.h"
std::vector<std::string> ReadFromFile(std::string filename) {
    std::vector<std::string> allwords;
    setlocale(LC_ALL, "Russian");
    std::ifstream file;
    file.open(filename);
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (ch == '\r')
            continue;
        if (ch == '\n') {
            word += ch;
            allwords.push_back(word);
            word.clear();
        } else if (isspace(static_cast<unsigned char>(ch))) {
            if (!word.empty()) {
                allwords.push_back(word);
                word.clear();
            }
        } else {
            word += ch;
        }
    }
    if (!word.empty()) {
        allwords.push_back(word);
    }
    file.close();
    return allwords;
}
prefix CreatePrefix(std::vector<std::string> allwords, int npref, int i) {
    prefix newprefix;
    for (int j = i; j < i + npref; j++)
        newprefix.push_back(allwords[j]);
    return newprefix;
}
std::vector<std::string> CreateSuffix(
    std::vector<std::string> allwords, int npref, prefix newprefix) {
    std::vector<std::string> newsuffix;
    for (int j = npref; j < allwords.size(); j++) {
        bool isValidSuffix = true;
        for (int k = 0; k < npref; k++) {
            if (newprefix[k] != allwords[j + k - npref])
                isValidSuffix = false;
        }
        if (isValidSuffix) newsuffix.push_back(allwords[j]);
    }
    return newsuffix;
}
std::map<prefix, std::vector<std::string>> CreateTable(
    std::vector<std::string> allwords, int npref) {
    std::map<prefix, std::vector<std::string>> statetab;
    for (int i = 0; i < allwords.size() - npref; i++) {
        prefix newprefix = CreatePrefix(allwords, npref, i);
        std::vector<std::string> newsuffix = CreateSuffix(
            allwords, npref, newprefix);
        statetab[newprefix] = newsuffix;
    }
    return statetab;
}
int RandomNumber(int maxnumber) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxnumber);
    return dis(gen);
}
prefix GeneratePrefix(std::map<prefix, std::vector<std::string>> statetab) {
    prefix nextprefix;
    int startposition = RandomNumber(statetab.size() - 1);
    auto element = statetab.begin();
    advance(element, startposition);
    for (int i = 0; i < element->first.size(); i++)
        nextprefix.push_back(element->first.at(i));
    return nextprefix;
}
std::string ChooseSuffix(
    std::map<prefix, std::vector<std::string>> statetab, prefix nextprefix) {
    int suffixindex = RandomNumber(statetab[nextprefix].size() - 1);
    std::string chosensuffix = statetab[nextprefix][suffixindex];
    return chosensuffix;
}
void Generate(
    std::map<prefix, std::vector<std::string>> statetab, int maxgen) {
    std::ofstream file;
    file.open("gen.txt");
    int wordcount = 0;
    prefix nextprefix = GeneratePrefix(statetab);
    for (int i = 0; i < nextprefix.size(); i++) {
        if (wordcount < maxgen - 1) {
            std::cout << nextprefix.at(i) << " ";
            file << nextprefix.at(i) << " ";
            wordcount++;
        }
    }
    while (wordcount < maxgen) {
        while (statetab[nextprefix].size() == 0) {
            nextprefix.clear();
            nextprefix = GeneratePrefix(statetab);
            for (int i = 0; i < nextprefix.size(); i++) {
                if (wordcount < maxgen - 1) {
                    std::cout << nextprefix.at(i) << " ";
                    file << nextprefix.at(i) << " ";
                    wordcount++;
                }
            }
        }
        std::string chosensuffix = ChooseSuffix(statetab, nextprefix);
        std::cout << chosensuffix << " ";
        file << chosensuffix << " ";
        wordcount++;
        nextprefix.pop_front();
        nextprefix.push_back(chosensuffix);
    }
    file.close();
}
