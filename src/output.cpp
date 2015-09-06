#include "output.hpp"

// tmp:
#include <fstream>
#include <iostream>

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <string>
#include <vector>

////////////////////////////

int getAbsoluteX(int x);
int getAbsoluteY(int y);
int getAbsoluteCoordinate(int value, int console, int track);
int coordinatesOutOfBounds(int x, int y);
void clearScreen(void);
void registerSigWinChCatcher(void);
void sigWinChCatcher(int signum);
void updateConsoleSize(void);
void copyArray(char dest[], const char src[], int width);
int getLengthOfString(char const s[]);
void setLine(string line, int y);
void replaceLine(char const s[], int y);

////////////////////////////

#define PRINT_IN_CENTER 1
#define DEFAULT_WIDTH 80
#define DEFAULT_HEIGHT 24

int pictureWidth = DEFAULT_WIDTH;
int pictureHeight = DEFAULT_HEIGHT;

int columns = DEFAULT_WIDTH;
int rows = DEFAULT_HEIGHT;

callback_function drawScreen;
volatile sig_atomic_t screenResized = 0;

vector<string> screenBuffer;
vector<string> onScreen;

////////// PUBLIC //////////

void setOutput(callback_function drawScreenThat, int width, int height) {
  drawScreen = drawScreenThat;
  pictureWidth = width;
  pictureHeight = height;
  registerSigWinChCatcher();
  updateConsoleSize();
  // Sets colors.
  printf("\e[%dm\e[%dm", 37, 40);
}

void updateScreen() {
  for (size_t i = 0; i < screenBuffer.size(); i++) {
    if (onScreen.size() <= i) {
      onScreen.push_back("");
    }
    if (screenBuffer.at(i) != onScreen.at(i)) {
      onScreen.at(i) = screenBuffer.at(i);
      printf("\033[%d;%dH%s", getAbsoluteY(i), getAbsoluteX(0),
             screenBuffer.at(i).c_str());
    }
  }
}

void setBuffer(string s, int x, int y) {
  int size = screenBuffer.size();
  if (size <= y) {
    for (int i = size; i <= y+1; i++) {
      screenBuffer.push_back("");
    }
  }
  screenBuffer.at(y).replace(x, s.length(), s);
}

void printCharXY(char c, int x, int y) {
  if (coordinatesOutOfBounds(x, y)) {
    return;
  }
  setBuffer(string(1, c), x, y);
}

void printCharImediately(char c, int x, int y) {
  if (coordinatesOutOfBounds(x, y)) {
    return;
  }
  printf("\033[%d;%dH%c", getAbsoluteY(y), getAbsoluteX(x), c);
}

void printString(char const s[], int x, int y) {
  if (coordinatesOutOfBounds(x, y)) {
    return;
  }
  int itDoesntFitTheScreen = getLengthOfString(s) + (unsigned) x > (unsigned) columns;
  if (itDoesntFitTheScreen) {
    int distanceToTheRightEdge = columns - x - 1;
    char subArray[distanceToTheRightEdge+2];
    copyArray(subArray, s, distanceToTheRightEdge+2);
    s = subArray;
    setBuffer(subArray, x, y);
  } else {
    setBuffer(s, x, y);
  }
}

// NEW:
void setLine(string line, int y) {
  int size = screenBuffer.size();
  if (size <= y) {
    for (int i = size; i <= y+1; i++) {
      screenBuffer.push_back("");
    }
  }
  screenBuffer.at(y) = line;
}

// NEW:
void replaceLine(char const s[], int y) {
  int x = 0;
  if (coordinatesOutOfBounds(x, y)) {
    return;
  }
  int itDoesntFitTheScreen = getLengthOfString(s) + (unsigned) x > (unsigned) columns;
  if (itDoesntFitTheScreen) {
    int distanceToTheRightEdge = columns - x - 1;
    char subArray[distanceToTheRightEdge+2];
    copyArray(subArray, s, distanceToTheRightEdge+2);
    s = subArray;
    setLine(subArray, y);
  } else {
    setLine(s, y);
  }
}

int getLengthOfString(char const s[]) {
  int counter = 0;
  bool insideEscapeSeqence = false;
  // for every char:
  for (size_t i = 0; i < strlen(s); i++) {
    // if escape sequence -> dont count
    if (s[i] == '\033') {
      insideEscapeSeqence = true;
      continue;
    }
    if (insideEscapeSeqence && s[i] == 'm') {
      insideEscapeSeqence = false;
      continue;
    }
    if (!insideEscapeSeqence) {
      counter++;
    }
  }
  return counter;
}

int getAbsoluteX(int x) {
  return getAbsoluteCoordinate(x, columns, pictureWidth);
}

int getAbsoluteY(int y) {
  return getAbsoluteCoordinate(y, rows, pictureHeight);
}

int getAbsoluteCoordinate(int value, int console, int track) {
  int offset = 0;
  if (PRINT_IN_CENTER) {
    offset = ((console - track) / 2) + ((console - track) % 2);
    if (offset < 0)
      offset = 0;
  }
  return value + 1 + offset;
}

int coordinatesOutOfBounds(int x, int y) {
  return x >= columns || y >= rows || x < 0 || y < 0;
}

/////////// DRAW ///////////

void refresh() {
  for (size_t i = 0; i < screenBuffer.size(); i++) {
    if (onScreen.size() <= i) {
      onScreen.push_back("");
    }
    printf("\033[%d;%dH%s", getAbsoluteY(i), getAbsoluteX(0),
           screenBuffer.at(i).c_str());
    if (screenBuffer.at(i) != onScreen.at(i)) {
      onScreen.at(i) = screenBuffer.at(i);
    }
  }
}

void clearScreen(void) {
  onScreen = {};
  screenBuffer = {};
  printf("\e[1;1H\e[2J");
}

void refreshScreen() {
  screenResized = 0;
  updateConsoleSize();
  clearScreen();
  drawScreen();
  refresh();
  fflush(stdout);
}

void redrawScreen() {
  if (screenResized == 1) {
    refreshScreen();
  } else {
    updateConsoleSize();
    drawScreen();
    updateScreen();
    fflush(stdout);
  }
}

///////// SIGNALS //////////

void registerSigWinChCatcher() {
  struct sigaction action;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  action.sa_handler = sigWinChCatcher;
  sigaction(SIGWINCH, &action, NULL);
}

/*
 * Fires when window size changes.
 */
void sigWinChCatcher(int signum) {
  screenResized = 1;
}

/*
 * Asks system about window size.
 */
void updateConsoleSize() {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  columns = w.ws_col;
  rows = w.ws_row;
}

/////////// UTIL ///////////

void copyArray(char dest[], const char src[], int width) {
  int i;
  for (i = 0; i < width-1; i++) {
    dest[i] = src[i];
  }
  dest[width-1] = '\0';
}


