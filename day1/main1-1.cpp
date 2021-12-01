#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Function to compare the current depth with the last one.
 * 
 * @param lastDepth The last depth.
 * @param currentDepth The current depth to compare.
 * @return const int& 0 = equals, -1 = decreasing, 1 = increasing
 */
const int& compare(const int& lastDepth, const int& currentDepth)
{

}
int main(int argc, char const *argv[])
{
    size_t countIncrease = 0; //Function to get the current count that the current depth is increasing against the last one.
    int lastDepth = -1; //The last depth calculate -1 = initial depth calculation.
    int currentDepth = 0; //The current depth to calculate and compare with the last one.

    while(getLine())
    {
        if(lastDepth == -1)
        {

        }
        if(compare == 1)
        {
            countIncrease++;
        }
    }
    cout << countIncrease << endl;
    return 0;
}
