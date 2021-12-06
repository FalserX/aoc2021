#include "BingoCard.h"
using namespace std;
/**
 * @brief Construct a new Bingo Card:: Bingo Card object
 * @param cardNumbers The numbers of the bingoCard.
 * @param bingoCardSize The size of one row or one column like
 */
BingoCard::BingoCard(const std::vector<int>& cardNumbers, const int& bingoCardSize)
{
    for(size_t i = 0; i < cardNumbers.size();i++)
    {
        numbers.push_back(cardNumbers.at(i));
        markNumbers.push_back(false);
    }
    cardColSize = bingoCardSize;
}
/**
 * @brief Destroy the Bingo Card:: Bingo Card object
 * 
 */
BingoCard::~BingoCard(){}
/**
 * @brief Function to get the sum of the unmarked values in the bingo card
 * 
 * @return int The sum of the unmarked values.
 */
int BingoCard::getSumOfUnmarkedValues() 
{
    return sumOfUnmarkedValues;
}
/**
 * @brief Function to get the bingo card size.
 * 
 * @return std::size_t the size of the bingo card.
 */
std::size_t BingoCard::getCardSize() 
{
    return cardColSize*cardColSize;
}
/**
 * @brief Function to get the bingo card column size.
 * 
 * @return std::size_t the column size.
 */
std::size_t BingoCard::getColCardSize() 
{
    return cardColSize;
}
/**
 * @brief Function to get the bingo card row size.
 * 
 * @return std::size_t the row size.
 */
std::size_t BingoCard::getRowCardSize() 
{
    return cardColSize;
}
/**
 * @brief Function to get the numbers of the card.
 * 
 * @return std::vector<int> The numbers like (column + (row*bingoCardSize)) in representation.
 */
std::vector<int> BingoCard::getNumbers() 
{
    return numbers;
}
/**
 * @brief Function to get the bingo card markings.
 * 
 * @return std::vector<bool> The marks like (column + (row*bingoCardSize)) in representation.
 */
std::vector<bool> BingoCard::getMarkNumbers() 
{
    return markNumbers;
}
/**
 * @brief Function to get the number of draw it's take for winning.
 * 
 * @return std::size_t The number of draw.
 */
std::size_t BingoCard::getNumberOfDrawsForWinning() 
{
    return numberOfDrawsForWinning;
}
/**
 * @brief Function to solve the bingo card.
 * 
 * @param drawNumbers The draw numbers for the bingo card.
 */
void BingoCard::solvingCard(const std::vector<int>& drawNumbers) 
{
    for(size_t i = 0; i < drawNumbers.size();i++)
    {
        auto findDrawNumber = find(numbers.begin(),numbers.end(),drawNumbers.at(i));
        int position = distance(numbers.begin(),findDrawNumber);
        int rowPosition = position / cardColSize;
        int colPosition = position % cardColSize;
        if(position >= numbers.size())
        {
            continue;
        }
        markNumbers.at(position) = true;
        if(checkRow(rowPosition))
        {
            numberOfDrawsForWinning = i+1;
            for(size_t j = 0; j < cardColSize;j++)
            {
                for(size_t i = 0; i < cardColSize;i++)
                {
                    if(!markNumbers.at(i+(j*cardColSize)))
                    {
                        sumOfUnmarkedValues += numbers.at(i+(j*cardColSize));
                    }
                }
            }
            break;
        }
        else if(checkCol(colPosition))
        {
            numberOfDrawsForWinning = i+1;
            for(size_t j = 0; j < cardColSize;j++)
            {
                for(size_t i = 0; i < cardColSize;i++)
                {
                    if(!markNumbers.at(i+(j*cardColSize)))
                    {
                        sumOfUnmarkedValues += numbers.at(i+(j*cardColSize));
                    }
                }
            }
            break;
        }
    }
}
/**
 * @brief Function to set mark for the number.
 * 
 * @param marking The value of the mark. True or false.
 * @param row The row of the number.
 * @param col The column of the number.
 */
void BingoCard::setMarkNumber(const bool& marking, const size_t& row, const size_t& col) 
{
    markNumbers.at(col + (row*getRowCardSize())) = true;
}
/**
 * @brief Function to check a specific row in the card.
 * @param checkRowNumber the row to check.
 * @return true: the line is winning, false: the line is not winning.
 */
bool BingoCard::checkRow(const std::size_t& checkRowNumber) 
{
    bool rowWinning = true;
    for(size_t j = 0; j < cardColSize;j++)
    {
        if(!markNumbers.at((checkRowNumber*cardColSize)+j))
        {
            rowWinning = false;
            break;
        }
    }
    return rowWinning;
}
/**
 * @brief Function to check a specific column in the card.
 * @param checkColNumber the column to check.
 * @return true: the column is winning, false: the column is not winning.
 */
bool BingoCard::checkCol(const std::size_t& checkColNumber) 
{
    bool colWinning = true;
    for(size_t i = 0; i < cardColSize;i++)
    {
        if(!markNumbers.at((i*cardColSize)+(checkColNumber)))
        {
            colWinning = false;
            break;
        }
    }
    return colWinning;
}
