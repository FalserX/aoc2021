#include <iostream>
#include <fstream>
#include <string>
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
int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        cerr << "The file input option is not provided. Retry" << endl;
        exit(1);
    }
    else
    {
        string pathFile = argv[1];
        ifstream FileTxt;
        size_t countIncrease = 0; //Function to get the current count that the current depth is increasing against the last one.
    
        int lastDepth = -1; //The last depth calculate -1 = initial depth calculation.
        int currentDepth = 0; //The current depth to calculate and compare with the last one.
        string currentLine = "";
        if(!FileTxt.is_open())
        {
            FileTxt.open(pathFile);
            if(!FileTxt.good())
            {
                cerr << "the input.txt file not found in the folder. Retry with the input.txt file in the folder." << endl;
                exit(1);
            }
        }
        while(!FileTxt.eof()) //We check all lines in the input.txt file.
        {
            getline(FileTxt,currentLine,'\n');
            currentDepth = stoi(currentLine.substr(0,currentLine.find('\r')));
            if(compare(lastDepth, currentDepth) == 1)
            {
                countIncrease++;
            }
            lastDepth = currentDepth;
        }
        FileTxt.close();
        cout << "The number of count of depth increasing is : " << countIncrease << endl;
    } 
    return 0;
}
