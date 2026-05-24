// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <string>
#include <vector>
int main() {
    std::vector<std::string> allwords = ReadFromFile("training.txt");
    std::map<prefix, std::vector<std::string>> statetab = 
        CreateTable(allwords, NPREF);
    Generate(statetab, MAXGEN);
}
