
#include "Helper.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// input validation methods

namespace Helper {

bool isASCII(std::string n) {
  //   unsigned int i;
  //   for (i = 0; i < n.size(); i++) {
  //     if (isalpha(n[i]) == 0) {
  //       return false;
  //     }
  //   }
  return true;
}

bool isNumber(std::string h) {
  //   bool valid = true;
  //   for (unsigned int i = 0; i < h.size(); i++) {
  //     if (isdigit(h[i]) == 0) {
  //       valid = false;
  //     }
  //   }
  //   return valid;
  return true;
}

bool isTilesListValid(std::string a) {
  //   std::istringstream iss(a);
  //   std::string tile;
  //   std::string validTileChars = "RGBPOY123456";
  //   while (iss.good()) {
  //     getline(iss, tile, ',');

  //     if (tile.length() != 2 &&
  //         tile.find_first_not_of(validTileChars) != std::string::npos) {
  //       return false;
  //     }
  //   }
  return true;
}

bool isColHeadValid(std::string q) {
  //   bool valid = true;
  //   std::string test;
  //   std::vector<std::string> token3;
  //   unsigned int linelength = q.length();
  //   unsigned int i;
  //   for (i = 0; i <= linelength; i++) {
  //     if (q[i] != ' ') {
  //       if (q[i + 1] != q[i] + 2) {
  //         valid = false;
  //       }
  //     }
  //   }
  //   return valid;
  return true;
}

bool isDashValid(std::string l) {
  //   bool valid = true;
  //   unsigned int rowLength = l.length();
  //   int dashCount = 0;
  //   unsigned int i;
  //   if (rowLength > 0) {
  //     char dashRow[rowLength];
  //     strcpy(dashRow, l.c_str());
  //     if (dashRow[0] == ' ' && dashRow[1] == ' ') {
  //       for (i = 2; i <= rowLength; i++) {
  //         if (dashRow[i] == '-') {
  //           dashCount++;
  //         }
  //       }
  //       if (dashCount < 24) {
  //         valid = false;
  //       }
  //     }
  //   }
  //   return valid;
  return true;
}

bool isRowsValid(std::string b) {
  //   std::istringstream isb(b);
  //   std::vector<std::string> token2;
  //   int rowLength2 = b.length();
  //   unsigned int i;
  //   unsigned int j;
  //   bool valid = true;

  //   if (rowLength2 > 0) {
  //     char rowA[rowLength2];
  //     std::string test;
  //     strcpy(rowA, b.c_str());
  //     char letter = 'A';
  //     letter += 1;
  //     if (isalpha(rowA[0]) == 0 && rowA[1] == ' ') {
  //       while (isb.good()) {
  //         getline(isb, test, '|');
  //         token2.push_back(test);
  //       }

  //       if (letter % 2 != 0) {
  //         for (i = 1; i <= token2.size(); i++)
  //           if (token2[i].length() != 4) {
  //             valid = false;
  //           }
  //       } else if (letter % 2 == 0) {
  //         for (j = 1; j <= token2.size(); j++) {
  //           if (token2[j].length() != 4) {
  //             valid = false;
  //           }
  //         }
  //       }
  //     }
  //   }
  //   return valid;
  return true;
}

bool isValidFormat(std::string filename) {
  //   bool fileVal = true;
  //   bool nameVal = true;
  //   bool scoreVal = true;
  //   bool handVal = true;
  //   bool boardVal = true;
  //   bool bagVal = true;

  //   unsigned int i;
  //   std::fstream infile;
  //   infile.open(fileName);

  //   if (infile.fail()) {
  //     // std::cout << "File Does Not Exist" << std::endl;
  //     fileVal = false;
  //   }

  //   std::string hold[50];
  //   std::string line;
  //   int count = 0;

  //   while (getline(infile, line)) {
  //     hold[count] = line;
  //     count++;
  //   }

  //   // validate name is ASCII - check each char of string

  //   if (isASCII(hold[0]) == false && isASCII(hold[3]) == false) {
  //     // std::cout << hold[0] << std::endl;
  //     // std::cout << hold[3] << std::endl;
  //     //  std::cout << "Incorrect Format - Name Must Only Contain Letters"
  //     //           << std::endl;
  //     nameVal = false;
  //   }

  //   // validate score is number
  //   if (!isNumber(hold[1]) && !isNumber(hold[4])) {
  //     // std::cout << "Incorrect File Format - Score Not Number" <<
  //     std::endl; scoreVal = false;
  //   }

  //   // validate player hands

  //   if (isTilesListValid(hold[2]) == false &&
  //       isTilesListValid(hold[5]) == false) {
  //     //  std::cout << "Incorrect File Format - Tile Hands" << std::endl;
  //     handVal = false;
  //   }

  //   // //validate board is same as cout

  //   if (isColHeadValid(hold[6]) == true && isDashValid(hold[7]) == true) {
  //     unsigned int sizeOfGrid = count - 12;

  //     for (i = 8; i <= sizeOfGrid; i++) {
  //       if (isRowsValid(hold[i]) == false) {
  //         boardVal = false;
  //       }
  //     }

  //     if (isDashValid(hold[count - 3]) == false &&
  //         isColHeadValid(hold[count - 2]) == false) {
  //       boardVal = false;
  //     }
  //   }

  //   if (isTilesListValid(hold[count]) == false) {
  //     bagVal = false;
  //   }

  //   return (fileVal && nameVal && scoreVal && handVal && boardVal && handVal
  //   &&
  //           bagVal);
  return true;
}

}  // namespace Helper
