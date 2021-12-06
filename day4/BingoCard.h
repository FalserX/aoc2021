#ifndef BINGOCARD_H_
#define BINGOCARD_H_
#include <vector>
#include <limits>
#include <algorithm>
class BingoCard
{
private:
    std::size_t cardColSize = 0;
    int sumOfUnmarkedValues = 0;
    std::vector<int> numbers;
    std::vector<bool> markNumbers;
    std::size_t numberOfDrawsForWinning = 0;
    void setMarkNumber(const bool& marking, const size_t& row, const size_t& col);
    bool checkRow(const std::size_t& checkRowNumber);
    bool checkCol(const std::size_t& checkColNumber);
public:
    BingoCard(const std::vector<int>& cardNumbers,const int& bingoCardSize);
    ~BingoCard();
    int getSumOfUnmarkedValues();
    std::size_t getCardSize();
    std::size_t getColCardSize();
    std::size_t getRowCardSize();
    std::vector<int> getNumbers();
    std::vector<bool> getMarkNumbers();
    std::size_t getNumberOfDrawsForWinning();
    void solvingCard(const std::vector<int>& drawNumbers);
};
#endif