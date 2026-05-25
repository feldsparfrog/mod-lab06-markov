// Copyright 2021 GHA Test Team
#include <map>
#include <string>
#include <vector>
#include "textgen.h"
int main() {
    std::vector<std::string> allwords = ReadFromFile("training.txt");
    std::map<prefix, std::vector<std::string>> statetab =
        CreateTable(allwords, NPREF);
    Generate(statetab, MAXGEN);
}
