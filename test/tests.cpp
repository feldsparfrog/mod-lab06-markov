// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>
#include "textgen.h"
TEST(Tests, TestPrefixSize) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Съешь", "же", "этих", "французских", "булок", "да", "выпей", "чаю" };
    EXPECT_EQ(CreatePrefix(testsentence, 3, 0).size(), 3);
}
TEST(Tests, TestPrefix) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Съешь", "же", "этих", "французских", "булок", "да", "выпей", "чаю" };
    prefix testprefix = { "этих", "французских", "булок" };
    EXPECT_EQ(CreatePrefix(testsentence, 3, 2), testprefix);
}
TEST(Tests, TestSuffixSize) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    prefix testprefix = CreatePrefix(testsentence, 2, 0);
    EXPECT_EQ(CreateSuffix(testsentence, 2, testprefix).size(), 2);
}
TEST(Tests, TestSuffix) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    prefix testprefix = CreatePrefix(testsentence, 2, 0);
    std::vector<std::string> testsuffix = { "ворон,", "воздух," };
    EXPECT_EQ(CreateSuffix(testsentence, 2, testprefix), testsuffix);
}
TEST(Tests, TestTable) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    std::map<prefix, std::vector<std::string>> testtab =
        CreateTable(testsentence, 2);
    prefix testprefix = CreatePrefix(testsentence, 2, 0);
    std::vector<std::string> testsuffix = { "ворон,", "воздух," };
    EXPECT_EQ(testtab[testprefix], testsuffix);
}
TEST(Tests, TestRandomNumber) {
    int testgen = RandomNumber(20);
    EXPECT_TRUE(testgen >= 0 && testgen <= 20);
}
TEST(Tests, TestPrefixGenerate) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Съешь", "же", "этих", "французских", "булок", "да", "выпей", "чаю" };
    std::map<prefix, std::vector<std::string>> testtab =
        CreateTable(testsentence, 5);
    EXPECT_TRUE(GeneratePrefix(testtab).back() == "булок" ||
        GeneratePrefix(testtab).back() == "да" ||
        GeneratePrefix(testtab).back() == "выпей" ||
        GeneratePrefix(testtab).back() == "чаю");
}
TEST(Tests, TestSuffixChoose1) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    prefix testprefix = CreatePrefix(testsentence, 2, 1);
    std::map<prefix, std::vector<std::string>> testtab =
        CreateTable(testsentence, 2);
    EXPECT_EQ(ChooseSuffix(testtab, testprefix), "ты");
}
TEST(Tests, TestSuffixChoose2) {
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    prefix testprefix = CreatePrefix(testsentence, 2, 0);
    std::map<prefix, std::vector<std::string>> testtab =
        CreateTable(testsentence, 2);
    EXPECT_TRUE(ChooseSuffix(testtab, testprefix) == "ворон," ||
        ChooseSuffix(testtab, testprefix) == "воздух,");
}
TEST(Tests, TestGenerate) {
    setlocale(LC_ALL, "Russian");
    vector<string> testsentence =
    { "Ты", "мне", "ворон,", "ты", "мне", "воздух,", "величиною", "с", "кулак",
        "смотрят", "звёзды" };
    std::map<prefix, std::vector<std::string>> testtab =
        CreateTable(testsentence, 2);
    Generate(testtab, 20);
    std::vector<std::string> newtext = ReadFromFile("gen.txt");
    EXPECT_EQ(newtext.size(), 20);
}
