
#include "Helper.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// input validation methods

namespace Helper
{

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

bool isColHeadValid(std::string q)
{
    bool valid = true;

    std::vector<char> temp;
    int linelength = q.length();
    unsigned int i;
    for (i = 0; i <= linelength; i++)
    {
        if (q[i] != ' ')
        {
            temp.push_back(q[i]);
        }
    }

    for (unsigned int j = 0; j < temp.size() - 1; j++)
    {

        if (temp[j + 1] != temp[temp.size() - 1] && temp[j] + 2 != temp[j + 1])
        {

            valid = false;
        }
    }
    return valid;
}

bool isDashValid(std::string l)
{
    bool valid = true;
    int rowLength = l.length();
    int dashCount = 0;
    unsigned int i;
    if (rowLength > 0)
    {
        char dashRow[rowLength];
        strcpy(dashRow, l.c_str());
        if (dashRow[0] == ' ' && dashRow[1] == ' ')
        {
            for (i = 2; i < rowLength; i++)
            {
                if (dashRow[i] != '-')
                {
                    valid = false;
                }
                if (dashRow[i] == '-')
                {
                    dashCount++;
                }
            }

            if (dashCount < 24)
            {

                valid = false;
            }
        }
    }

    return valid;
}

bool isRowsValid(std::string b)
{
    std::istringstream isb(b);
    std::vector<std::string> token2;
    int rowLength2 = b.length();
    unsigned int i;
    unsigned int j;
    bool valid = true;

    if (rowLength2 > 0)
    {

        char rowA[rowLength2];
        std::string test;
        strcpy(rowA, b.c_str());
        char letter = rowA[0];

        if (isalpha(rowA[0]) == 0 || rowA[1] != ' ')
        {
            valid = false;
        }
        else
        {
            while (isb.good())
            {
                getline(isb, test, '|');
                token2.push_back(test);
            }

            if (letter % 2 != 0)
            {

                if (token2[0].length() != 2)
                {
                    valid = false;
                }
                for (i = 1; i < token2.size(); i++)
                {

                    if (token2[i].length() != 4)
                    {

                        valid = false;
                    }
                }
            }

            if (letter % 2 == 0)
            {

                if (token2[0].length() != 5)
                {

                    valid = false;
                }
                for (j = 1; j < token2.size() - 1; j++)
                {

                    if (token2[j].length() != 4)
                    {
                        valid = false;
                    }
                }
            }
        }
    }

    return valid;
}

bool isValidFormat(std::string fileName)
{
    bool fileVal = true;
    bool nameVal = true;
    bool scoreVal = true;
    bool handVal = true;
    bool boardVal = true;
    bool gridVal = true;

    unsigned int i;
    std::fstream infile;
    infile.open(fileName);

    if (infile.fail())
    {
        // std::cout << "File Does Not Exist" << std::endl;
        fileVal = false;
    }

    std::string hold[50];
    std::string line;
    int count = 0;

    while (getline(infile, line))
    {
        hold[count] = line;
        count++;
    }

    // validate name is ASCII - check each char of string

    if (isASCII(hold[0]) == false || isASCII(hold[3]) == false)
    {
        nameVal = false;
    }

    // validate score is number
    if (isNumber(hold[1]) == false || isNumber(hold[4]) == false)
    {

        scoreVal = false;
    }

    // // validate player hands and bag

    if (isTilesListValid(hold[2]) == false || isTilesListValid(hold[5]) == false || isTilesListValid(hold[count - 2]) == false)
    {

        handVal = false;
    }

    // // //validate board is same as cout (board must have the 4 spaces after | on lines A C E)

    if (isDashValid(hold[7]) == false || isColHeadValid(hold[6]) == false || isDashValid(hold[count - 4]) == false || isColHeadValid(hold[count - 3]) == false)
    {
        boardVal = false;
    }

    int sizeOfGrid = count - 4;

    for (i = 8; i < sizeOfGrid; i++)

    {
        if (isRowsValid(hold[i]) == false)
        {
            gridVal = false;
        }
    }
    // std::cout << fileVal << ", " << nameVal << ", " << scoreVal << ", " << handVal << ", " << boardVal << ", " << gridVal << std::endl;

    return (fileVal && nameVal && scoreVal && handVal && boardVal && gridVal);
}

} // namespace Helper
