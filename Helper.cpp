#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// input validation methods

namespace Helper
{

bool isASCII(std::string n)
{
  unsigned int i;

  for (i = 0; i < n.size(); i++)
  {
    if (isalpha(n[i]) == 0)
    {
      return false;
    }
  }
  return true;
}

bool isNumber(std::string h)
{
  unsigned int i;

  for (i = 0; i < h.size(); i++)
  {
    if (isdigit(h[i]) == 0)
    {
      return false;
    }
  }
  return true;
}

bool isHandValid(std::string a){
        std::string tile;
        while (a.good())
        {
            getline(a, tile, ',');
            if (Game::isTileValid(tile) == false)
            {
                return false;
            }
        }
        return true;
}

bool isValidFormat(std::string fileName)
{
  std::fstream infile;
  infile.open(fileName);

  if (infile.fail())
  {
    std::cout << "File Does Not Exist" << std::endl;
    return false;
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

  if (isASCII(hold[0]) == false && isASCII(hold[3]) == false)
  {
    std::cout << hold[0] << std::endl;
    std::cout << hold[3] << std::endl;
    std::cout << "Incorrect Format - Name Must Only Contain Letters"
              << std::endl;
    return false;
  }

  // validate score is number
  else if (isNumber(hold[1]) == false && isNumber(hold[4]) == false)
  {
    std::cout << "Incorrect File Format - Score Not Number" << std::endl;
    return false;
  }

  // validate player hands 

 
  else if (isHandValid(hold[2]) == false && isHandValid(hold[5]) == false)
    {
     std::cout << "Incorrect File Format - Tile Hands" << std::endl;
     return false
    }
  
  // //validate board is same as cout

  // else if (hold[6].find){

  // hold[6] to hold[14]

  //     }

  return true;
}

} // namespace Helper
