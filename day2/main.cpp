#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

/**
 * @brief Enumeration of direction values.
 * 
 */
enum directionValue 
{
    dv_forward,
    dv_up,
    dv_down
};

std::map<string,directionValue> directionMap; //To associate direction with the value of the direction
/**
 * @brief Function to calculate the direction and the depth of the submarine
 * 
 * @param currentLine The current line of the input.
 * 
 * @param depth The current depth.
 * 
 * @param horizontalPosition the current horizontal position.
 * 
 * @param useAim The usage of Aim.
 * 
 * @param aimPosition The position of aim.
 * 
 */
void calculateDirectionDepth(const string& currentLine, int& depth, int& horizontalPosition, const bool& useAim, int& aimPosition)
{
    string direction = currentLine.substr(0,currentLine.find_first_of(' '));
    int directionValue = stoi(currentLine.substr(currentLine.find_first_of(' ')+1, currentLine.length()));

    switch (directionMap[direction])
    {
        case dv_forward:
        {
            horizontalPosition += directionValue;
            if(useAim)
            {
                if(aimPosition > 0)
                {
                    depth += aimPosition*directionValue;
                }
            }
            break;
        }
        case dv_down:
        {
            if(useAim)
            {
                aimPosition += directionValue;
            }
            else 
            {
                depth += directionValue;
            }
            break;
        }
        case dv_up:
        {
            if(useAim)
            {
                aimPosition -= directionValue;
            }
            else
            {
                depth -= directionValue;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        cerr << "The file input option is not provided. Retry with the input file in the folder" << endl;
        exit(1);
    }
    else
    {
        directionMap["forward"] = dv_forward;
        directionMap["up"] = dv_up;
        directionMap["down"] = dv_down;
        string pathFile = argv[1];
        string currentLine = "";
        int horizontalPosition = 0;
        int horizontalPositionAim = 0;
        int depth = 0;
        int depthAim = 0;
        int aim = 0;
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
                    calculateDirectionDepth(currentLine, depth, horizontalPosition, false, aim);
                    calculateDirectionDepth(currentLine,depthAim,horizontalPositionAim, true,aim);
                }
                FileTxt.close(); //We close the file to liberate memory usage.
                cout << "The depth times the horizontal position is : "<< depth*horizontalPosition << endl;
                cout << "The depth times the horizontal position with using aim is : " << depthAim* horizontalPositionAim << endl;
            }
        }
    }
    return 0;
}
