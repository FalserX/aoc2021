#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
/**
 * @brief Function to compare the current depth with the last one.
 * 
 * @param lastDepth The last depth.
 * @param currentDepth The current depth to compare.
 * @return const int 0 = equals, -1 = decreasing, 1 = increasing
 */
const int compare(const int& lastDepth, const int& currentDepth)
{
    if(lastDepth == -1)
    {
        return 0;
    }
    if(lastDepth < currentDepth)
    {
        return 1;
    }
    else if(lastDepth > currentDepth)
    {
        return -1;
    }
    return 0;
}

/**
 * @brief Function to calculate the sum of a 3-depth window and push it to a queue.
 * 
 * @param currentLine The current line who contains the depth value.
 * @param sumOf3Depths The queue with the sum of a 3-depth window.
 * @param secondLastDepth The second last depth calculate.
 * @param lastDepth The last depth calculate.
 */
const void addingIncreasing3DepthWindow(const string& currentLine, queue<int>& sumOf3Depths, int& secondLastDepth, int& lastDepth)
{
    int currentDepth = 0; //The current depth to calculate and compare with the last one.
    currentDepth = stoi(currentLine.substr(0,currentLine.find('\r')));
    if(secondLastDepth > 0)
        {
            sumOf3Depths.push(secondLastDepth+lastDepth+currentDepth);
        }
        secondLastDepth = lastDepth;
        lastDepth = currentDepth;
}
/**
 * @brief Function to calculate the number of increasing depth. In a window specification of 3-depth-calculation
 * 
 * @param sumOf3Depths The queue with the calculate sum of 3-depth window.
 * @return const size_t The number of increasing depth in a 3-depth window.
 */
const size_t numberOfIncreasingDepthIn3DepthWindow(queue<int> sumOf3Depths)
{
    size_t countIncrease = 0; //Function to get the current count that the current depth is increasing against the last one.
    int lastDepth = -1;
    int currentDepth = -1;
    while(!sumOf3Depths.empty())
    {
        currentDepth = sumOf3Depths.front();
        sumOf3Depths.pop();
        if(compare(lastDepth,currentDepth) == 1)
        {
            countIncrease++;
        }
        lastDepth = currentDepth;
    }
     return countIncrease;
}
/**
 * @brief function to calculate the number of increasing depth. Next to next
 * 
 * @param currentLine The line file text input who contains the depth value
 * @param lastInput the last input calculate and feeded by the main function
 * @return const size_t the number of increasing depth.
 */
const size_t numberOfIncreasingDepth(const std::string& currentLine, int& lastInput)
{
    ifstream FileTxt;
    int currentDepth = 0; //The current depth to calculate and compare with the last one.
    currentDepth = stoi(currentLine.substr(0,currentLine.find('\r')));
    if(compare(lastInput, currentDepth) == 1)
    {
        lastInput = currentDepth;
        return 1;
    }
    lastInput = currentDepth;
    return 0;
}
/**
 * @brief The main function of the program
 * 
 * @param argc The number of arguments
 * @param argv The arguments values
 * @return int The exit integer
 */
int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        cerr << "The file input option is not provided. Retry with the input file in the folder" << endl;
        exit(1);
    }
    else
    {
        string pathFile = argv[1];
        string currentLine = "";
        size_t countIncrease = 0;
        size_t countIncrease3Depths = 0;
        queue<int> sumOf3Depth;
        int secondLastInput3Depth = -1;
        int lastInput3Depth = -1;
        int lastInput = -1;
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
                while(!FileTxt.eof()) //We check all lines in the input.txt file.
                {
                    getline(FileTxt,currentLine,'\n');
                    countIncrease += numberOfIncreasingDepth(currentLine, lastInput);
                    addingIncreasing3DepthWindow(currentLine, sumOf3Depth, secondLastInput3Depth, lastInput3Depth);
                }
                FileTxt.close(); //We close the file to liberate memory usage.
                cout << "The number of count of depth increasing is : " << countIncrease << endl;
                cout << "The number of count of depth increasing in 3-depth window is : " << numberOfIncreasingDepthIn3DepthWindow(sumOf3Depth) << endl;
            }
        }
    }
    return 0;
}
