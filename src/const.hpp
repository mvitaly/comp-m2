#ifndef CONST_H
#define CONST_H

#include <string>
#include <vector>
#include <set>

using namespace std;

// Miliseconds between cycles (when run in interactive mode).
const int FQ = 333;

const string SAVE_FILE_NAME = "punchcard-";
const string FILE_EXTENSION = "cm2";

const string LIGHTBULB_ON_3D = u8"\u2737";
const string LIGHTBULB_OFF_3D = u8"\u00b7"; 
const string LIGHTBULB_ON_3D_B = u8"\u2666";
const string LIGHTBULB_OFF_3D_B = u8"\u00b7"; 
const string LIGHTBULB_ON_2D = "*";
const string LIGHTBULB_OFF_2D = "-";

const int INIT_OPERAND_INDEX = 1;
const int AND_OPERAND_INDEX = 2;
const int OR_OPERAND_INDEX = 3;

const string GCC_COMMAND = "g++ -std=c++11 -g -O2 -o";

const bool BRIGHTEN_CURSOR = false;
const bool BRIGHTEN_LIGHTBULBS = false;

// Folowing constants will probably break code if changed.

const int WORD_SIZE = 8;
const int ADDR_SIZE = 4;
const int RAM_SIZE = 15;

const vector<bool> EMPTY_WORD = { false, false, false, false, false, false,
                                  false, false };
const vector<bool> FIRST_ADDRESS = { false, false, false, false };
const vector<bool> LAST_ADDRESS = { true, true, true, true };
const vector<bool> ONE_BEFORE_LAST_ADDRESS = { true, true, true, false };
const int MAX_VALUE = 255;

const vector<bool> INIT_INSTRUCTION = { false, true, true, true, false, false,
                                        true, false };
const vector<bool> AND_INSTRUCTION = { false, true, true, true, false, true,
                                       true, false };
const vector<bool> OR_INSTRUCTION = { false, true, true, true, false, true,
                                      true, true };
const vector<bool> LAST_XOR_INSTRUCTION = { false, true, true, true, true, true,
                                            true, true };
const int LAST_XOR_OPERAND_INDEX = 7;                                  

const int PRINTER_WIDTH = 12;

const string LOGIC_OPS_INDICATOR = "JRI~<>&VX";
const int LOGIC_OPS_INDEX = 7;

const string INC_DEC_OPS_INDICATOR = "INC/DEC";
const int INC_DEC_OPS_INDEX = 10;

const string LAST_CODE_ADDR_LABEL = "  STOP  ";
const string LAST_DATA_ADDR_LABEL = " IN/OUT ";

// const char DEFAULT_VAR_NAME = '-';

const string HIGHLIGHT_ESC = "\e[7m";
const string HIGHLIGHT_END_ESC = "\e[27m";

const vector<string> HIGHLIGHT_ESC_VEC = { "\e", "[", "7", "m" };
const vector<string> HIGHLIGHT_END_ESC_VEC = { "\e", "[", "2", "7", "m" };

const vector<string> BRIGHT_ESC_VEC = { "\e", "[", "9", "7", "m" };
const vector<string> BRIGHT_END_ESC_VEC = { "\e", "[", "3", "7", "m" };

const string CODE_INDICATOR = "a";
const string DATA_INDICATOR = "b";
const string CODE_ADR_INDICATOR = "g";
const string DATA_ADR_INDICATOR = "v";
const string REGISTER_INDICATOR = "r";
const set<string> LIGHTBULB_INDICATORS = { CODE_INDICATOR, DATA_INDICATOR, CODE_ADR_INDICATOR,
                             DATA_ADR_INDICATOR, REGISTER_INDICATOR };

const string OUTPUT_INDICATOR = "o";

const string NEW_LINE_FIRST = u8"\u000D";
const string NEW_LINE_SECOND = u8"\u000A";
const string ESCAPE = u8"\u001B";
const string LOWERCASE_M = u8"\u006D";

const string SOURCE_INCLUDES= ""
"#include <stdio.h>\n"
"#include <stdlib.h>\n"
"#include <unistd.h>\n"
"\n"
"#include <bitset>\n"
"#include <iostream>\n"
"#include <string>";


const string SOURCE_HEADER = ""
"using namespace std;\n"
"\n"
"bool outputNumbers = false;\n"
"\n"
"unsigned char sadd(unsigned char a, unsigned char b) {\n"
"  return (a > 255 - b) ? 255 : a + b;\n"
"}\n"
"\n"
"unsigned char ssub(unsigned char a, unsigned char b) {\n"
"  return (b > a) ? 0 : a - b;\n"
"}\n"
"\n"
"unsigned char extractInteger(string line) {\n"
"  int i = 0;\n"
"  for (char c : line) {\n"
"    if (!isdigit(c)) {\n"
"      break;\n"
"    }\n"
"    i++;\n"
"  }\n"
"  string stringNumber = line.substr(0, i);\n"
"  return (unsigned char) stoi(stringNumber, NULL);\n"
"}\n"
"\n"
"unsigned char getBoolByte(string sIn) {\n"
"  string sOut;\n"
"  for (char c : sIn) {\n"
"    if (c == '*') {\n"
"      sOut.push_back('1');\n"
"    } else {"
"      sOut.push_back('0');\n"
"    }\n"
"  }\n"
"  return (unsigned char) stoi(sOut, NULL, 2);\n"
"}\n"
"\n"
"unsigned char parseWord(string word) {\n"
"  bool startsWithDigit = isdigit(word[0]);\n"
"  if (startsWithDigit) {\n"
"    return extractInteger(word);\n"
"  } else {\n"
"    return getBoolByte(word);\n"
"  }\n"
"}\n"
"\n"
"string getString(unsigned char c) {\n"
"  std::bitset<8> x(c);\n"
"  string out;\n"
"  for (size_t i = 0; i < 8; i++) {\n"
"    if (x[i]) {\n"
"      out += \"*\";\n"
"    } else {\n"
"      out += \"-\";\n"
"    }\n"
"  }\n"
"  return out;\n"
"}\n"
"\n"
"string getFormatedInt(unsigned char c) {\n"
"  char formatedInt [4];\n"
"  sprintf(formatedInt, \"%3d\", c);\n"
"  return formatedInt;\n"
"}\n"
"\n"
"string getStringWithFormatedInt(unsigned char c) {\n"
"  return getString(c) + \" \" + getFormatedInt(c) + \"\\n\";\n"
"}";

const string PRINT_BASIC = ""
"void print(unsigned char c) {\n"
"  if (outputNumbers) {\n"
"    cout << getStringWithFormatedInt(c);\n"
"  } else {\n"
"    cout << getString(c) + \"\\n\";\n"
"  }\n"
"}";

const string PRINT_OUTPUT_CHARS = ""
"void print(unsigned char c) {\n"
"  cout << c;\n"
"}";

const string PRINT_RAW = ""
"void print(unsigned char c) {\n"
"  cout << c;\n"
"  fflush(stdout);\n"
"}";

const string F0_BASIC = ""
"unsigned char f0() {\n"
"  string word;\n"
"  cin >> word;\n"
"  if (!cin) {\n"
"    exit(0);\n"
"  }\n"
"  return parseWord(word);\n"
"}";

const string F0_INPUT_CHARS = ""
"unsigned char f0() {\n"
"  int c = getchar();\n"
"  if (c == EOF) {\n"
"    cout << endl;\n"
"    exit(0);\n"
"  }\n"
"  return (unsigned char) c;\n"
"}";

const string F0_RAW = ""
"unsigned char f0() {\n"
"  unsigned char c = 0;\n"
"  errno = 0;\n"
"  ssize_t num = read(0, &c, 1);\n"
"  if (num == -1 && errno == EINTR) {\n"
"    // Exits if ctrl-c was pressed.\n"
"    if (pleaseExit) {\n"
"      exit(0);\n"
"    }\n"
"    return f0();\n"
"  }\n"
"  return c;\n"
"}";

const string SOURCE_FOOTER_1 = ""
"int main() {\n"
"  outputNumbers = isatty(fileno(stdout));\n"
"  while(1) {\n"
"    print(f";

const string SOURCE_FOOTER_1_RAW = ""
"int main() {\n"
"  setEnvironment();\n"
"  outputNumbers = isatty(fileno(stdout));\n"
"  while(1) {\n"
"    print(f";

const string SOURCE_FOOTER_2 = "());\n"
"  }\n"
"}";

const string SOURCE_FUNCTION_HEADER_1 = "unsigned char f";

const string SOURCE_FUNCTION_HEADER_2 = "() {\n"
"  static unsigned char (*predecesor)() = &f";

const string SOURCE_FUNCTION_HEADER_3 = ";\n"
"  static void *a[16] = { &&a00, &&a01, &&a02, &&a03, &&a04, &&a05,\n"
"                              &&a06, &&a07, &&a08, &&a09, &&a10, &&a11,\n" 
"                              &&a12, &&a13, &&a14, &&a15 };\n"
"  static unsigned char reg = 0;\n"
"  static unsigned char pc = 0;\n"
"  static unsigned char adr = 0;\n"
"  static unsigned char data[15] = { ";

const string SOURCE_FUNCTION_HEADER_4 = " };\n"
"\n"
"  goto *a[pc];";

const string SOURCE_FUNCTION_FOOTER = ""
"  a15: exit(0);\n"
"}";

#endif
