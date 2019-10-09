
#include "Helper.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// input validation methods

namespace Helper {

bool isASCII(std::string n) {
  bool valid = true;

  for (unsigned int i = 0; i < n.size(); i++) {
    if (!isalpha(n[i])) {
      valid = false;
    }
  }

  return valid;
}

bool isNumber(std::string h) {
  bool valid = true;
  for (unsigned int i = 0; i < h.size(); i++) {
    if (!isdigit(h[i])) {
      valid = false;
    }
  }
  return valid;
}

bool isTilesListValid(std::string a)
{
    std::istringstream iss(a);
    std::string tile;
    std::string validTileChars = "RGBPOY123456";
    std::vector<std::string> temp;
    while (iss.good())
    {
        getline(iss, tile, ',');

        if (tile.length() != 2 || tile.find_first_not_of(validTileChars) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}


bool isColHeadValid(std::string q) {
  bool valid = true;
  std::vector<char> temp;

  for (unsigned int i = 0; i <= q.length(); i++) {
    if (q[i] != ' ') {
      temp.push_back(q[i]);
    }
  }

  for (unsigned int j = 0; j < temp.size() - 1; j++) {
    if (temp[j + 1] != temp[temp.size() - 1] && temp[j] + 2 != temp[j + 1]) {
      valid = false;
    }
  }

  return valid;
}

bool isDashValid(std::string l) {
  bool valid = true;
  unsigned int rowLength = l.length();
  int dashCount = 0;

  if (rowLength > 0) {
    char dashRow[rowLength];
    strcpy(dashRow, l.c_str());
    if (dashRow[0] == ' ' && dashRow[1] == ' ') {
      for (unsigned int i = 2; i < rowLength; i++) {
        if (dashRow[i] != '-') {
          valid = false;
        }
        if (dashRow[i] == '-') {
          dashCount++;
        }
      }

      if (dashCount < 24) {
        valid = false;
      }
    }
  }

  return valid;
}

bool isRowsValid(std::string b) {
  std::istringstream isb(b);
  std::vector<std::string> token2;
  int rowLength2 = b.length();
  bool valid = true;

  if (rowLength2 > 0) {
    char rowA[rowLength2];
    std::string test;
    strcpy(rowA, b.c_str());
    char letter = rowA[0];

    if (!isalpha(rowA[0]) || rowA[1] != ' ') {
      valid = false;
    } else {
      while (isb.good()) {
        getline(isb, test, '|');
        token2.push_back(test);
      }

      if (letter % 2 != 0) {
        if (token2[0].length() != 2) {
          valid = false;
        }
        for (unsigned int i = 1; i < token2.size(); i++) {
          if (token2[i].length() != 4) {
            valid = false;
          }
        }
      } else {
        if (token2[0].length() != 5) {
          valid = false;
        }
        for (unsigned int i = 1; i < token2.size() - 1; i++) {
          if (token2[i].length() != 4) {
            valid = false;
          }
        }
      }
    }
  }

  return valid;
}

bool isValidFormat(std::string fileName) {
  bool fileVal = true;
  bool nameVal = true;
  bool scoreVal = true;
  bool handVal = true;
  bool boardVal = true;
  bool gridVal = true;

  std::fstream infile;
  infile.open(fileName);

  if (infile.fail()) fileVal = false;

  std::string hold[50];
  std::string line;
  int count = 0;

  while (getline(infile, line)) {
    hold[count] = line;
    count++;
  }

  // validate that player names are ASCII characters
  if (!isASCII(hold[0]) || !isASCII(hold[3])) {
    nameVal = false;
  }

  // validate that player scores are integers
  if (!isNumber(hold[1]) || !isNumber(hold[4])) {
    scoreVal = false;
  }

  // // validate player hands and tilebag
  if (!isTilesListValid(hold[2]) || !isTilesListValid(hold[5]) ||
      !isTilesListValid(hold[count - 2])) {
    handVal = false;
  }

  // validate that board is same as cout
  if (!isDashValid(hold[7]) || !isColHeadValid(hold[6]) ||
      !isDashValid(hold[count - 4]) || !isColHeadValid(hold[count - 3])) {
    boardVal = false;
  }

  unsigned int sizeOfGrid = count - 4;
  for (unsigned int i = 8; i < sizeOfGrid; i++) {
    if (isRowsValid(hold[i]) == false) {
      gridVal = false;
    }
  }
  std::cout << "fileVal: " << fileVal << " nameVal: " << nameVal << " scoreVal: " << scoreVal << " handVal: " << handVal << " boardVal: " << boardVal << " gridVal: " << gridVal << std::endl;
  return (fileVal && nameVal && scoreVal && handVal && boardVal && gridVal);
}

}  // namespace Helper
