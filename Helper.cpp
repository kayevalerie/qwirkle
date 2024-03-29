
#include "Helper.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define MIN_LINE_COUNT 18

// input validation methods
namespace Helper {

bool isASCII(std::string n) {
  bool valid = true;

  for (unsigned int i = 0; i < n.size(); i++) {
    if (isalpha(n[i]) == 0) {
      valid = false;
    }
  }
  return valid;
}

bool isNumber(std::string h) {
  bool valid = true;

  for (unsigned int i = 0; i < h.size(); i++) {
    if (isdigit(h[i]) == 0) {
      valid = false;
    }
  }
  return valid;
}

bool isTilesListValid(std::string a) {
  std::istringstream iss(a);
  std::string tile;
  std::string validColours = "RGBPOY";
  std::string validShapes = "123456";
  std::vector<std::string> temp;
  bool valid = true;

  while (iss.good()) {
    getline(iss, tile, ',');

    if (tile.length() != 2 ||
        validColours.find(tile.at(0)) == std::string::npos ||
        validShapes.find(tile.at(1)) == std::string::npos) {
      valid = false;
    }
  }

  return valid;
}

bool isColHeadValid(std::string q) {
  bool valid = true;
  std::vector<int> temp;
  int num = 0;
  for (unsigned int i = 0; i <= q.length(); i++) {
    if (i <= 29 && q[i] != ' ' && q[i + 1] == ' ') {
      int num = q[i] - '0';
      temp.push_back(num);
    }

    if (q[i] != ' ' && isdigit(q[i + 1]) != 0) {
      num = (10 * (q[i] - '0')) + q[i + 1] - '0';
      temp.push_back(num);
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
  int rowLength = l.length();
  int dashCount = 0;

  if (rowLength > 0) {
    char dashRow[rowLength];
    strcpy(dashRow, l.c_str());

    if (dashRow[0] == ' ' && dashRow[1] == ' ') {
      for (int i = 2; i < rowLength; i++) {
        if (dashRow[i] != '-') valid = false;

        if (dashRow[i] == '-') dashCount++;
      }

      if (dashCount < 24) valid = false;
    }
  }

  return valid;
}

bool isRowsValid(std::string b) {
  std::istringstream isb(b);
  std::vector<std::string> token2;
  int rowLength2 = b.length();
  bool valid = true;
  std::string validColours = "RGBPOY";
  std::string validShapes = "123456";
  char blankSpotFour[5] = "    ";
  char blankSpotOne[2] = " ";
  char testTile[100];

  if (rowLength2 > 0) {
    char rowA[rowLength2];
    std::string test;
    strcpy(rowA, b.c_str());
    char letter = rowA[0];

    if (isalpha(rowA[0]) == 0 || rowA[1] != ' ') {
      valid = false;
    } else {
      while (isb.good()) {
        getline(isb, test, '|');
        token2.push_back(test);
      }

      if (letter % 2 != 0) {
        if (token2[0].length() != 2 ||
            token2[0].find(blankSpotOne) == std::string::npos) {
          valid = false;
        }
        for (unsigned int i = 1; i < token2.size() - 1; i++) {
          if (token2[i].length() != 4) {
            valid = false;
          }

          strcpy(testTile, token2[i].c_str());

          if (strcmp(testTile, blankSpotFour) != 0) {
            if (validColours.find(token2[i].at(1)) == std::string::npos ||
                validShapes.find(token2[i].at(2)) == std::string::npos) {
              valid = false;
            }
          }
        }
      }

      if (letter % 2 == 0) {
        if (token2[0].length() != 5 ||
            token2[0].find(blankSpotFour) == std::string::npos ||
            token2[token2.size() - 1] != "") {
          valid = false;
        }
        for (unsigned int j = 1; j < token2.size() - 1; j++) {
          if (token2[j].length() != 4) {
            valid = false;
          }

          strcpy(testTile, token2[j].c_str());

          if (strcmp(testTile, blankSpotFour) != 0) {
            if (validColours.find(token2[j].at(1)) == std::string::npos ||
                validShapes.find(token2[j].at(2)) == std::string::npos) {
              valid = false;
            }
          }
        }
      }
    }
  }

  return valid;
}

bool fileExists(std::string fileName) {
  std::fstream infile;
  infile.open(fileName);
  bool fileopen = true;

  if (infile.fail()) {
    fileopen = false;
  }
  infile.close();

  return fileopen;
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

  if (infile.fail())
    fileVal = false;
  else {
    std::string hold[50];
    std::string line;
    int count = 0;

    while (getline(infile, line)) {
      hold[count] = line;
      count++;
    }

    if (count < MIN_LINE_COUNT) {
      fileVal = false;
    } else {
      // validate name is in ASCII
      if (isASCII(hold[0]) == false || isASCII(hold[3]) == false) {
        nameVal = false;
      }

      // validate score is a number
      if (isNumber(hold[1]) == false || isNumber(hold[4]) == false) {
        scoreVal = false;
      }

      // validate player hands and tilebag
      if (isTilesListValid(hold[2]) == false ||
          isTilesListValid(hold[5]) == false ||
          isTilesListValid(hold[count - 2]) == false) {
        handVal = false;
      }

      // validate board format (board must have the 4 spaces after row)
      if (isDashValid(hold[7]) == false || isColHeadValid(hold[6]) == false ||
          isDashValid(hold[count - 4]) == false ||
          isColHeadValid(hold[count - 3]) == false) {
        boardVal = false;
      }

      int sizeOfGrid = count - 4;

      for (int i = 8; i < sizeOfGrid; i++)

      {
        if (isRowsValid(hold[i]) == false) {
          gridVal = false;
        }
        if (i < sizeOfGrid - 1 && hold[i + 1].at(0) != hold[i].at(0) + 1) {
          gridVal = false;
        }
      }
    }
  }

  return (fileVal && nameVal && scoreVal && handVal && boardVal && gridVal);
}

}  // namespace Helper
