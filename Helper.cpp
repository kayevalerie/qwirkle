#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Helper.h"

// input validation methods

namespace Helper {

bool isASCII(std::string n) {
  unsigned int i;

  for (i = 0; i < n.size(); i++) {
    if (isalpha(n[i]) == 0) {
      return false;
    }
  }
  return true;
}

bool isNumber(std::string h) {
  unsigned int i;

  for (i = 0; i < h.size(); i++) {
    if (isdigit(h[i]) == 0) {
      return false;
    }
  }
  return true;
}

// bool isHandValid(std::string a)
// {
//   std::string tile;
//   std::string validTileChars = "RGBPOY123456";
//   while (a.good())
//   {
//     getline(a, tile, ',');

//     if (tile.length()) != 2 && tile.find_first_not_of(validTileChars) !=
//     std::string::npos)
//     {
//       return false;
//     }
//   }
//   return true;
// }

// bool isBoardValid(std::string b){
//   bool valid = true;
//   std::string test;
//   std::vector<std::string> token;

//   while (getline(hold[6], test, "    "))
//   {
//     token.push_back(test);
//   }
//   for (int i = 0, i < token.size(), i++)
//   {
//     if (!isNumber(token[i]) && token[0] != 0 && token[i + 1] != token[i] + 2)
//     {
//       valid = false;
//     }
//   }

//   int rowLength = hold[7].length();
//   int dashCount = 0;
//   if (rowLength > 0)
//   {
//     char dashRow[rowLength];
//     strcpy(dashRow, hold[7].c_str());
//     if (dashRow[0] == " " && dashRow[1] == " ")
//     {
//       for (int i = 2, i <= rowLength, i++)
//       {
//         dashRow[i] == "-";
//         dashCount++;
//       }
//       if (dashCount < 24){
//        valid = false;
//       }
//     }

//   std::vector<std::string> token2;
//   int rowLength2 = hold[8].length();
//   if (rowLength2 > 0)
//   {
//     char letter = 'A';
//     char rowA[rowLength2];
//     int linecount = 8;

//     strcpy(rowA, hold[linecount].c_str());

//     while(rowA[0] == letter){

//     if (rowA[1] == " ")
//     {
//       while (getline(hold[linecount], test, "|"))
//       {
//         token.push_back(test);
//         for (int i = 1, i <=5, i++)
//           if (test.length() != 4)
//         {
//           valid = false;
//         }
//       }
//     }

//     letter++;

//   }
// }
// return valid;
// }

bool isValidFormat(std::string fileName) {
  //   bool fileVal = true;
  //   bool nameVal = true;
  //   bool scoreVal = true;
  //   bool handVal = true;
  //   bool boardVal = true;
  //   bool bagVal = true;

  //   bool valid = false;
  //   std::fstream infile;
  //   infile.open(fileName);

  //   if (infile.fail())
  //   {
  //    // std::cout << "File Does Not Exist" << std::endl;
  //     fileVal = false;
  //   }

  //   std::string hold[50];
  //   std::string line;
  //   int count = 0;

  //   while (getline(infile, line))
  //   {
  //     hold[count] = line;
  //     count++;
  //   }

  //   // validate name is ASCII - check each char of string

  //   if (isASCII(hold[0]) == false && isASCII(hold[3]) == false)
  //   {
  //     std::cout << hold[0] << std::endl;
  //     std::cout << hold[3] << std::endl;
  //   //  std::cout << "Incorrect Format - Name Must Only Contain Letters"
  //    //           << std::endl;
  //     nameVal = false;
  //   }

  //   // validate score is number
  //   else if (isNumber(hold[1]) == false && isNumber(hold[4]) == false)
  //   {
  //    // std::cout << "Incorrect File Format - Score Not Number" << std::endl;
  //     scoreVal = false;
  //   }

  //   // validate player hands

  //   else if (isHandValid(hold[2]) == false && isHandValid(hold[5]) == false)
  //   {
  //   //  std::cout << "Incorrect File Format - Tile Hands" << std::endl;
  //     handVal = false;
  //   }

  //   // //validate board is same as cout

  //   else if (isBoardValid() == false){
  //     boardVal == false;
  //   }

  // // validate player hands

  // else if (isHandValid(hold[2]) == false && isHandValid(hold[5]) == false)
  // {
  // //  std::cout << "Incorrect File Format - Tile Hands" << std::endl;
  //   handVal = false;
  // }

  // // //validate board is same as cout

  // else if (isBoardValid() == false){
  //   boardVal == false;
  // }

  //   // hold[6] to hold[14]

  //   //     }

  //   return (fileVal && nameVal && scoreVal && handVal && boardVal &&
  //   handVal);

  return true;
}

}  // namespace Helper
