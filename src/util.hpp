#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Util {
  public:
    static int getInt(vector<bool> bbb);
    static vector<bool> getBoolByte(int num);
    static vector<bool> getBoolNibb(int num);
    static vector<bool> getBool(int num, int length);
    static vector<bool> getBoolByte(string sIn);
    static vector<bool> getFirstNibble(vector<bool> bbb);
    static vector<bool> getSecondNibble(vector<bool> bbb);
    static string getString(vector<bool> bbb);
    static string getChar(bool b);
    static string getFormatedInt(vector<bool> wordIn);
    static string getStringWithFormatedInt(vector<bool> wordIn);
    static vector<vector<bool>> getRamFromString(string ramString);
    static vector<bool> getRandomWord();
    static vector<bool> parseWord(string word);
    static vector<bool> readWordFromPipe();
    // UNICODE
    static vector<vector<string>> splitIntoLines(vector<string> drawing);
    // STRING
    static vector<string> splitString(string stringIn);
    static string makeString(vector<string> lines);
    static int hexToInt(char cIn);
    static string getString(char cIn);
    static tuple<int,int> getCoordinatesOfFirstOccurance(vector<string> text,
                                                         string cIn);
    static int getKey();
    static bool fileExists(string filename);
    static bool inputIsPiped();
    static bool outputIsPiped();
    static bool startsWithDigit(string line);
    static int extractInteger(string line);
    static int getSignedIntFromNibble(vector<bool> value);
    static void assertEqualLength(vector<bool> value1, vector<bool> value2,
                                  int errNumber);
    static vector<bool> bitwiseAndOrOr(vector<bool> value1, vector<bool> value2,
                                       bool isAnd);
    static vector<bool> bitwiseXor(vector<bool> value1, vector<bool> value2);
    static vector<bool> bitwiseNot(vector<bool> val);
    static vector<string> stringToVecOfString(string stringIn);
    static size_t getSizeOfLargestElement(vector<vector<string>> lines);
    static vector<string> getFilesInDirectory(const string &directory);
    static bool endsWith(string const &fullString, string const &ending);
    static bool isADir(string filename);
    static bool contains(vector<string> options, const char* arg);
};

#endif
