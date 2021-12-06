#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "BingoCard.h"
using namespace std;
/**
 * @brief Function to convert the line of data to number.
 * 
 * @param strNumbers The line to convert.
 * @param numbers The numbers converted.
 * @param bingoCardSize The size of one line. (after convert by size*size)
 * @param isNotDraw: true: the line is the bingo card ; false: the line is the draw numbers.
 */
void convertLineToNumber(string& strNumbers, vector<int>& numbers, const size_t& bingoCardSize, const bool& isNotDraw)
{
    if(!strNumbers.empty() && (!isNotDraw || (numbers.size() < (bingoCardSize*bingoCardSize))))
    {
        if(strNumbers.find_first_of(',') < strNumbers.length())
        {
            numbers.push_back(stoi(strNumbers.substr(0,strNumbers.find_first_of(','))));
            strNumbers = strNumbers.substr(strNumbers.find_first_of(',')+1,strNumbers.length());
        }
        else
        {
            if(strNumbers.find_first_of(' ') < strNumbers.length())
            {
                if(strNumbers.at(0) == ' ')
                {
                    strNumbers = strNumbers.substr(1,strNumbers.length());
                }
                numbers.push_back(stoi(strNumbers.substr(0,strNumbers.find_first_of(' '))));
                if(strNumbers.find_first_of(' ') < strNumbers.length())
                {
                    strNumbers = strNumbers.substr(strNumbers.find_first_of(' ')+1, strNumbers.length());
                }
                else
                {
                     strNumbers.pop_back();
                }
            }
            else
            {
                numbers.push_back(stoi(strNumbers.substr(0,strNumbers.length())));
                if(strNumbers.find(numbers.at(numbers.size()-1)) < strNumbers.length())
                {
                    strNumbers = strNumbers.substr(strNumbers.find(numbers.at(numbers.size()-1)),strNumbers.length());
                }
                else
                {
                    strNumbers = "";
                }
            }
        }
        convertLineToNumber(strNumbers, numbers, bingoCardSize, isNotDraw);
    }
    else
    {
        strNumbers = "";
    }
}
/**
 * @brief Function to remove multiples spaces.
 * 
 * @param currentString The current string.
 * @return const string& The new string.
 */
const string removeMultipleSpaces(const string& currentString)
{
    string newString = "";
    int i = 0,j,n = currentString.length();
    while(i < n)
    {
        if(currentString[i+1] == ' ' && currentString[i] == ' ')
        {
            i++;
        }
        else
        {
            newString.push_back(currentString[i]);
            i++;
        }
    }
    return newString;
}
/**
 * @brief Get the Data line object 
 * 
 * @param File The file stream of the input file data
 * @return const string the data line
 */
const string getData(ifstream& File)
{
    string currentLine = "";
    string correctLine = "";
    getline(File,currentLine,'\n');
    currentLine = removeMultipleSpaces(currentLine);
    if(currentLine[0] == ' ')
    {
        for(size_t i = 1;i < currentLine.length();i++)
        {
            correctLine += currentLine.at(i);
        }
        currentLine = correctLine;
    }
    if(currentLine != "")
    {
        currentLine = currentLine.substr(0,currentLine.find_first_of('\r'));
    }
    else
    {
        currentLine = "-1";
    }
    std::replace(currentLine.begin(),currentLine.end(),' ', ',');
    return currentLine;
}
/**
 * @brief main function of the program
 * 
 * @param argc The number of arguments
 * @param argv The arguments
 * @return int 0 exit correctly, others numbers, error 
 */
int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        cerr << "The file input option is not provided. Retry with the input file in the folder. The bingo size height is not defined. Defined it." << endl;
        exit(1);
    }
    else
    {
        std::vector<int> drawNumbers;
        std::vector<int> minDrawNumberInBingoCards;
        std::vector<int> winningBingoCardOrder;
        int minWinnerCard = -1;
        int maxWinnerCard = -1;
        std::size_t maxCompare = 0;
        std::size_t minCompare = 0;
        std::vector<int> bingoCardsWinnings;
        std::vector<BingoCard> bingoCards;
        int bingoCardNumber = -1;
        int result = 0;
        std::vector<int> bingoCardNumbersData;
        string strData;
        string strDrawNumbers;
        std::vector<int> numbersConvert;
        string pathFile = argv[1];
        size_t bingoHeightSize = atoi(argv[2]);
        ifstream FileTxt;
        if(!FileTxt.is_open())
        {
            FileTxt.open(pathFile);
            if(!FileTxt.good())
            {
                cerr << "the input file not found in the folder. Retry with the input file in the folder." << endl;
                exit(1);
            }
            else
            {
                while(!FileTxt.eof())
                {
                    strData += getData(FileTxt);
                    strData += ',';
                }
                strData.pop_back();
                FileTxt.close(); //we close the file to liberate memory usage.
                strDrawNumbers = strData.substr(0,strData.find("-1")-1);
                strData = strData.substr(strData.find("-1")+3,strData.length());
                convertLineToNumber(strDrawNumbers, drawNumbers,bingoHeightSize,false);
                strDrawNumbers.clear();
                numbersConvert.clear();
                while(!strData.empty())
                {
                    if(strData.find("-1") < strData.length())
                    {
                        strDrawNumbers = strData.substr(0,strData.find("-1")-1);
                        if(strData.find("-1")+3 < strData.length())
                        {
                            strData = strData.substr(strData.find("-1")+3,strData.length());
                        }
                        else
                        {
                            strData.clear();
                        }
                    }
                    else
                    {
                        strDrawNumbers = strData.substr(0,strData.length());
                        strData.clear();
                    }
                    convertLineToNumber(strDrawNumbers,numbersConvert,bingoHeightSize,true);
                    bingoCards.push_back(BingoCard(numbersConvert,bingoHeightSize));
                    numbersConvert.clear();
                    strDrawNumbers.clear();
                }
                for(size_t i = 0; i < bingoCards.size();i++)
                {
                    bingoCards.at(i).solvingCard(drawNumbers);
                    minDrawNumberInBingoCards.push_back(bingoCards.at(i).getNumberOfDrawsForWinning());
                }
                auto findSmallestDrawNumber = std::min_element(minDrawNumberInBingoCards.begin(),minDrawNumberInBingoCards.end());
                auto findBiggestDrawNumber = std::max_element(minDrawNumberInBingoCards.begin(),minDrawNumberInBingoCards.end());
                std::size_t minPosition = std::distance(minDrawNumberInBingoCards.begin(),findSmallestDrawNumber);
                std::size_t maxPosition = std::distance(minDrawNumberInBingoCards.begin(),findBiggestDrawNumber); 
                minCompare = minDrawNumberInBingoCards.at(minPosition);
                maxCompare = minDrawNumberInBingoCards.at(maxPosition);
                minWinnerCard = minPosition;
                maxWinnerCard = maxPosition;
                if(minWinnerCard == -1 && maxWinnerCard == -1)
                {
                    cout << "Nothing (no bingo card is winning)" << endl;
                    exit(1);
                }
                cout << "The result of the winning bingo card times the current draw number is: "<< bingoCards.at(minWinnerCard).getSumOfUnmarkedValues()*drawNumbers.at(minCompare-1) << endl;
                cout << "The result of the losing bingo card times the current draw number is: " << bingoCards.at(maxWinnerCard).getSumOfUnmarkedValues()*drawNumbers.at(maxCompare-1) << endl;
            }
        }
    }
    return 0;
}