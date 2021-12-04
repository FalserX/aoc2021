#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
typedef unsigned char bit;
/**
 * @brief Function to convert binary data to decimal
 * 
 * @param value The binary
 * @return const int The decimal
 */
const int binaryToDecimal(const string& value)
{
    int result = 0;
    string val = value;
    int length = value.length();
    for(size_t i = 0; i < value.length(); i++)
    {
        result += pow(2,length-1) * (int(val.at(i))-48);
        length--;
    }
    return result;
}
/**
 * @brief Get the numberOfbits object (recursive)
 * 
 * @param data The data
 * @param binaryLength The length of the binary
 * @param dataPosition The position of the binary data to check.
 * @param count0 the number of zero calculate.
 * @param count1 the number of one calculate.
 * @return const vector<bit> The new vector with the data substracted from unnecessary data.
 */
void getNumberOfBits(const vector<bit>& data, size_t& binaryLength,const size_t& dataPosition, int& count0, int& count1)
{
    if(dataPosition < data.size())
    {
        if(data.at(dataPosition) == '0')
        {
            count0++;
        }
        else 
        {
            count1++;
        }
        getNumberOfBits(data, binaryLength, dataPosition+binaryLength,count0,count1);
    }
}
/**
 * @brief Get the Bytes object
 * 
 * @param data The data input
 * @param resultTemp the temporary result
 * @param binaryLength The length of the resulting binary
 * @param lessMore 0 = less, 1 = more
 * @param dataPosition The position of the data cursor
 * @param keepAll false, true
 * @return vector<bit> The resulting data bits.
 */
vector<bit> getBytes(const vector<bit>& data, const vector<bit>& resultTemp, size_t& binaryLength,const int& lessMore, const size_t&dataPosition, const bool& keepAll)
{
    vector<bit> result;
    if(keepAll)
    {
        result = resultTemp;
    }
    int count0 = 0;
    int count1 = 0;
    getNumberOfBits(data,binaryLength,dataPosition,count0,count1);
    if (count1 > count0 && dataPosition < binaryLength)
        {
            if(keepAll)
                {
                    if(lessMore == 1)
                    {
                        result.push_back('1');
                    }
                    else
                    {
                        result.push_back('0');
                    }  
                }
            else 
            {
                for(size_t i = 0; i < (data.size()/binaryLength);i++)
                {
                    if(data.at((i*binaryLength)+dataPosition) == '1' && lessMore == 1)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        }
                    }
                    else if(data.at((i*binaryLength)+dataPosition) == '0' && lessMore == 0)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        }
                    }     
                }
            }
            if(data.size() > binaryLength)
            {
                if(keepAll)
                {
                    result = getBytes(data,result,binaryLength,lessMore,dataPosition+1,keepAll);
                }
                else
                {
                    result = getBytes(result,result,binaryLength,lessMore,dataPosition+1,keepAll);
                }
            }
            else
            {
                result = data;
            }
        }
        else if(count1 < count0 && dataPosition < binaryLength)
        {
            if(keepAll)
                {
                    if(lessMore == 1)
                    {
                        result.push_back('0');
                    }
                    else
                    {
                        result.push_back('1');
                    }  
                }
            else 
            {
                for(size_t i = 0; i < (data.size()/binaryLength);i++)
                {
                    if(data.at((i*binaryLength)+dataPosition) == '0' && lessMore == 1)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        }
                    }
                    else if(data.at((i*binaryLength)+dataPosition) == '1' && lessMore == 0)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        }
                    }     
                }
            }
            if(data.size() > binaryLength)
            {
                if(keepAll)
                {
                    result = getBytes(data,result,binaryLength,lessMore,dataPosition+1,keepAll);
                }
                else
                {
                    result = getBytes(result,result,binaryLength,lessMore,dataPosition+1,keepAll);
                }
            }
            else
            {
                result = data;
            }
        }
        else if(dataPosition < binaryLength)
        {
            if(!keepAll)
            {
                for(size_t i = 0; i < (data.size()/binaryLength);i++)
                {
                    if(data.at((i*binaryLength)+dataPosition) == '1' && lessMore == 1)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        } 
                    }
                    else if(data.at((i*binaryLength)+dataPosition) == '0' && lessMore == 0)
                    {
                        for(size_t j = 0; j < binaryLength;j++)
                        {
                            result.push_back(data.at(j+(i*binaryLength)));
                        } 
                    }
                }
                if(data.size() > binaryLength && !keepAll)
                {
                    if(keepAll)
                    {
                        result = getBytes(data,result,binaryLength,lessMore,dataPosition+1,keepAll);
                    }
                    else
                    {
                        result = getBytes(result,result,binaryLength,lessMore,dataPosition+1, keepAll);
                    }
                }
                else
                {
                    result = data;
                }
            }
            else
            {
                if(lessMore == 1)
                {
                    result.push_back('1');
                }
                else
                {
                    result.push_back('0');
                }
            }
        }
        else
        {
            if(!keepAll)
            {
                result = data;
            }
        }
    return result;
}
/**
 * @brief Get the Oxygen Generator And Co2 Scrubber values
 * 
 * @param data the input data
 * @param binaryLength The binary length
 * @return const pair<string,string> first the oxygen, second the co2
 */
const pair<string,string> getOxygenGeneratorAndCo2Scrubber(const vector<bit> data, size_t& binaryLength)
{
    vector<bit> oxygenValues;
    vector<bit> co2Values;
    int count0 = 0;
    int count1 = 0;
    if(binaryLength == 0)
    {
        cerr << "the binary length can't be 0. check the file data input if it's contains something" << endl;
        exit(1);
    }
        oxygenValues = getBytes(data,oxygenValues,binaryLength,1,0,false);
        co2Values = getBytes(data,co2Values,binaryLength,0,0,false);
        return pair<string,string>(string(oxygenValues.begin(),oxygenValues.end()),string(co2Values.begin(),co2Values.end()));
}
/**
 * @brief Get the Gamma And Epsilon Rate object
 * 
 * @param data The data object
 * @param binaryLength the length of the binary number.
 * @return const pair<string,string> first element the gamma, second element the epsilon 
 */
const pair<string,string> getGammaAndEpsilonRate(const vector<bit> data, size_t& binaryLength)
{
    int count0 = 0;
    int count1 = 0;
    vector<bit> gammaBits;
    vector<bit> epsilonBits;
    if(binaryLength == 0)
    {
        cerr << "the binary length can't be 0. check the file data input if it's contains something" << endl;
        exit(1);
    }
    gammaBits = getBytes(data,gammaBits,binaryLength,1,0,true);
    epsilonBits = getBytes(data,epsilonBits,binaryLength,0,0,true);
    return pair<string,string>(string(gammaBits.begin(),gammaBits.end()),string(epsilonBits.begin(),epsilonBits.end()));
}
/**
 * @brief Get the Data objectFunction 
 * 
 * @param File The file stream of the input file data
 * @param length the length of a line of data.
 * @return const bit The data value (0 or 1)
 */
const vector<bit> getData(ifstream& File, size_t& length)
{
    vector<bit> data;
    string currentLine = "";
    while(!File.eof()) //We check all lines in the input.txt file.
    {
        getline(File,currentLine,'\n');
        currentLine = currentLine.substr(0,currentLine.find_first_of('\r'));
        length = currentLine.size();
        for(size_t i = 0; i < length;i++)
        {
            data.push_back(currentLine.at(i));
        }
    }
    return data;
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
    if(argc < 2)
    {
        cerr << "The file input option is not provided. Retry with the input file in the folder" << endl;
        exit(1);
    }
    else
    {
        std::pair<string,string> gammaEpsilon;
        std::pair<string,string> oxygenCo2;
        std::vector<bit> inputData;
        string pathFile = argv[1];
        int gamma = 0;
        int epsilon = 0;
        int oxygenRating = 0;
        int co2ScrubberRating = 0;
        size_t binaryLength = 0;
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
                inputData = getData(FileTxt, binaryLength);
                FileTxt.close(); //we close the file to liberate memory usage.
                gammaEpsilon = getGammaAndEpsilonRate(inputData, binaryLength);
                oxygenCo2 = getOxygenGeneratorAndCo2Scrubber(inputData,binaryLength);
                gamma = binaryToDecimal(gammaEpsilon.first);
                epsilon = binaryToDecimal(gammaEpsilon.second);
                oxygenRating = binaryToDecimal(oxygenCo2.first);
                co2ScrubberRating = binaryToDecimal(oxygenCo2.second);
                cout << "The gamma times the epsilon is: "<< gamma*epsilon << endl;
                cout << "The life support rating of the submarine is : " << co2ScrubberRating * oxygenRating << endl;
            }
        }
    }
    return 0;
}