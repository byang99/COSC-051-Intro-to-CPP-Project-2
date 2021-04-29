/*
* main.cpp
*
* COSC 051 Fall 2018
* Project #2 (Code)
*
* Due on: OCT 17, 2018
* Author: byy2
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <cmath>
using namespace std;

//global constants
    const double MARBLE_PRICE = 92.99;
    const double GRANITE_PRICE = 78.99;
    const double QUARTZ_PRICE = 56.99;
    const double EDGE_FINISHING_RATE = 4.99;
    const double WASTAGE_PERCENT = 0.26;
    const double MAX_LENGTH = 25.0;
    const double MIN_LENGTH = 5.0;
    const double MAX_DEPTH = 25.0;
    const double MIN_DEPTH = 5.0;
    const int MIN_EDGES_FINISHED = 0;
    const int MAX_EDGES_FINISHED = 2;
    const int MONTH_DIFFERENCE = 8;
    const double MIN_HEIGHT_FACTOR = 0.58;
    const double MAX_HEIGHT_FACTOR = 0.80;
    const int FOUR_MONTH_DIFFERENCE = 4;
    const int TWO_YEAR_DIFFERENCE = 2;
    const int ONE_YEAR_DIFFERENCE = 1;
    const int FOUR_MONTH_DIFFERENCE_NEW_YEAR = -7;
    const int TWELVE_MONTH_DIFFERENCE = 12;
    const int ONE_ERROR = 1;
    const int ZERO_ERRORS = 0;

    
int main()
{
    //variables for reading a file
    ifstream inputFile;
    string fileName;

    //order date variables
    int ODYear = 0;
    int ODMonth = 0;
    int ODDay = 0;
    
    //delivery date variables
    int DDYear = 0;
    int DDMonth = 0;
    int DDDay = 0;
    
    //variable for slash between date
    char ch = ' '; 
    
    //variable to read over first line and "get it over with"
    string firstLine = " ";
    
    //variable to read rest of line (address, state code, name, etc)
    string restOfLine = " ";

    //data and calculation variables
    char stoneCode = ' ';
    double stonePriceRate = 0.0;
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int numLengthEdgesFinished = 0;
    int numDepthEdgesFinished = 0;
    double totalFinishingLength = 0.0;
    double counterArea = 0.0;
    double totalMaterialSqFt = 0.0;
    double totalMaterialCost = 0.0;
    double edgeFinishingCost = 0.0;
    double totalCost = 0.0;
    double minHeight = 0.0;
    double maxHeight = 0.0;
    string orderNumber = "";
    string stateCode = "";
    string nameAddress = "";
            
    //variables to count number of records with errors
    int totalErrorCount = 0;
    int OrderDeliverySame = 0;
    int DeliveryDateTooFar = 0;
    int invalidStoneCode = 0;
    int invalidLength = 0;
    int invalidDepth = 0;
    int invalidHeight =0;
    int invalidLengthEdges = 0;
    int invalidDepthEdges = 0;
    
    //variables to count number of records without errors
    int marbleRecords = 0;
    int graniteRecords = 0;
    int quartzRecords = 0;
    int totalNonError = 0;
    int totalRecords = 0;
    
    //total square feet
    double totalSqFtMarble = 0.0;
    double totalSqFtGranite = 0.0;
    double totalSqFtQuartz = 0.0;
    
    //total cost
    double totalCostMarble = 0.0;
    double totalCostGranite = 0.0;
    double totalCostQuartz = 0.0;
    
    //total count of all errors in all records
    int totalErrors = 0;

    //count of records with multiple errors
    int multipleErrorRecords = 0;
    
    //welcome message and ask for file name    
    cout << "Welcome to Claude's custom Counters, Inc. Calculator." << endl;
    cout << "This application calculates cost and fabrication" << endl;
    cout << "data based on sales data input files." << endl;
    cout << "Please enter the complete path and name of the input data file: ";
    //cin >> fileName;
    
    cout << endl;
    
    //open the input file
    //inputFile.open(fileName.c_str());
    inputFile.open("C://P2Orders.dat");
    
    // test if file successfully opened
    if (!inputFile) //file didn't open successfully
    {
        //display error message
        cout << "Error opening the file. Processing can't continue. " << endl;
    }
    
    else //file opened successfully. Continue processing the rest of the program.
    {
        cout << setw(8)<< "Order" << setw(17) << "Delivery" << setw(8) << "S";
        cout << setw(48) << "L" << "\t";
        cout << "D" << "\t" << "Sq." << setw(13) << "Total" << endl;
        cout << setw(8) << "Date" << setw(17) << "Date" <<"\t" << "C" << setw(15) << "Len.";
        cout << setw(14) << "Dep." << setw(12) << "Hei." << "\t" << "E" << "\t" << "E";
        cout << "\t" << "Ft" << setw(14) << "Cost" << endl;
        cout << "_____________________________________________________________________________";
        cout << "__________________________________________\n";
        
        getline(inputFile, firstLine);
        
        //process the file until end of the file is reached
        while (inputFile >> ODYear >> ch >> ODMonth >> ch >> ODDay >> DDYear >> ch 
                >> DDMonth >> ch >> DDDay >> stoneCode >> length >> depth >> height
                >> numLengthEdgesFinished >> numDepthEdgesFinished >> orderNumber >> stateCode
                && getline(inputFile, nameAddress))
        {
            //count number of total records in the file
            totalRecords++;
            
            //print data            
            //print order date
            cout << ODYear << ch;
            if(ODMonth <=9)
            {
                cout << "0" << ODMonth << ch;
            }
            else
            {
                cout << ODMonth << ch;
            }
            
            if(ODDay <=9)
            {
                cout << "0" << ODDay << "\t";
            }
            else
            {
                cout << ODDay << "\t";
            }
            
            //print delivery date
            cout << DDYear << ch;
            if(DDMonth <=9)
            {
                cout << "0" << DDMonth << ch;
            }
            else
            {
                cout << DDMonth << ch;
            }
            
            if(DDDay <=9)
            {
                cout << "0" << DDDay << "\t";
            }
            else
            {
                cout << DDDay << "\t";
            }
            
            cout << stoneCode << "\t";
            cout << fixed << setprecision(2) << setw(8) << length << "\t" << setw(6) << depth;
            cout << "\t" << setw(10) << height << "\t";
            cout << numLengthEdgesFinished << "\t";
            cout << numDepthEdgesFinished;
            
            //set price rates for stone
            //if stone is Granite
            if(toupper(stoneCode) == 'G')
            {
                stonePriceRate = GRANITE_PRICE;
            }
    
            //if stone is Marble
            if(toupper(stoneCode) == 'M')
            {
                 stonePriceRate = MARBLE_PRICE;
            }

            //if stone is Quartz
            if(toupper(stoneCode) == 'Q')
            {
                stonePriceRate = QUARTZ_PRICE;
            }
            
                     
            //test data validity and display error messages as necessary
            
            //variable to count number of errors within one record
            //in the while loop because it must be reset before reading every record
            //to count number of errors within each record.
            int individualErrorCount = 0;
            
            //order date and delivery date are equal
            if(ODYear == DDYear && ODMonth == DDMonth && ODDay == DDDay)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: order date and delivery date are equal.";
                individualErrorCount ++;
                OrderDeliverySame ++;
                totalErrors ++;
            }
            
            //order date and delivery date are too far apart
            
            if(DDYear >= ODYear && DDYear < ODYear + TWO_YEAR_DIFFERENCE)
            {
                if (DDYear == ODYear)
                {
                    if(DDMonth-ODMonth > FOUR_MONTH_DIFFERENCE)
                    {
                        cout << endl;
                        cout << "t";
                        cout << "ERROR: order date and delivery date are too far apart.";
                        individualErrorCount ++;                       
                        DeliveryDateTooFar ++;
                        totalErrors ++;
                    } 
                }
                if (DDYear == ODYear + ONE_YEAR_DIFFERENCE)
                {
                    if(DDMonth-ODMonth >= FOUR_MONTH_DIFFERENCE_NEW_YEAR 
                            && DDMonth-ODMonth < TWELVE_MONTH_DIFFERENCE)
                    {
                        cout << endl;
                        cout << "t";
                        cout << "ERROR: order date and delivery date are too far apart.";
                        individualErrorCount ++;
                        DeliveryDateTooFar ++;
                        totalErrors ++;
                    }
                }
            }
            else if(DDYear >= ODYear + TWO_YEAR_DIFFERENCE)
            {
                cout << endl;
                cout << "t";
                cout << "ERROR: order date and delivery date are too far apart.";
                individualErrorCount ++;
                DeliveryDateTooFar ++;
                totalErrors ++;
            }
            

            //test stone type validity - stone code must be g, G, m, M, q, or Q
            if ((toupper(stoneCode)!= 'G')&&(toupper(stoneCode)!= 'M')&&(toupper(stoneCode)!= 'Q'))
            {
                cout << endl;
                cout << "\t" << "ERROR: stone code is not a valid value.";
                individualErrorCount ++;
                invalidStoneCode ++;
                totalErrors ++;
            }
            
            //test length validity - MIN_LENGTH < length < MAX_LENGTH
            if((length < MIN_LENGTH) || (length > MAX_LENGTH))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid length.";    
                individualErrorCount ++;
                invalidLength ++;
                totalErrors ++;
            }
            
            
            //test depth validity - MIN_DEPTH < depth < MAX_DEPTH and depth <=length
            if((depth < MIN_DEPTH) || (depth > MAX_DEPTH) || (depth > length))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid depth.";
                individualErrorCount ++;
                invalidDepth ++;
                totalErrors ++;
            }
            
            //initialize range for min and max height
            minHeight = MIN_HEIGHT_FACTOR*depth;
            maxHeight = MAX_HEIGHT_FACTOR*depth;
            
            //test height entry validity
            if((height < minHeight) || (height > maxHeight))
            {
                cout << endl;
                cout << "\t" << "ERROR: Invalid height value."; 
                individualErrorCount ++;
                invalidHeight ++;
                totalErrors ++;
            }
            
            //test for validity of number of finished length edges
            if(numLengthEdgesFinished < MIN_EDGES_FINISHED
                    || numLengthEdgesFinished > MAX_EDGES_FINISHED)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: The number of length edges you want finished is out of our range.";

                individualErrorCount ++;
                invalidLengthEdges ++;
                totalErrors ++;
            }
            
            //test for validity of number of finished depth edges
            if(numDepthEdgesFinished < MIN_EDGES_FINISHED
                    || numDepthEdgesFinished > MAX_EDGES_FINISHED)
            {
                cout << endl;
                cout << "\t";
                cout << "ERROR: The number of depth edges you want finished is out of our range.";
                individualErrorCount ++;
                invalidDepthEdges ++;
                totalErrors ++;
            }
            
            
            if (individualErrorCount > ZERO_ERRORS) 
            {
                cout << endl;
                totalErrorCount ++;
                if (individualErrorCount > ONE_ERROR)
                {
                    multipleErrorRecords ++;                    
                }
            }
            
            else
            {
                //calculate total square feet and total cost
                counterArea = length * height;

                //calculate total square feet of material and round up to nearest whole number
                totalMaterialSqFt = ceil(counterArea * (1 + WASTAGE_PERCENT));

                totalMaterialCost = totalMaterialSqFt * stonePriceRate;

                totalFinishingLength = numLengthEdgesFinished * length + numDepthEdgesFinished * depth;
                edgeFinishingCost = totalFinishingLength * EDGE_FINISHING_RATE;
                totalCost = totalMaterialCost + edgeFinishingCost;
            
                //print total square feet and total cost in the data table 
                //if all values are valid
                cout << setw(10) << totalMaterialSqFt << "\t";
                cout << setw(10) << totalCost << endl;

                //if the record has no error, then count it toward total number of
                //records without errors
                totalNonError++;
                
                if(toupper(stoneCode)== 'G')
                {                    
                    graniteRecords++;
                    //total cost of granite = sum of total cost for each granite record
                    totalCostGranite += totalCost;
                    //total square feet of granite = sum of total sq ft of granite in each
                    //granite record
                    totalSqFtGranite += totalMaterialSqFt;
                }
                else if(toupper(stoneCode)== 'M')
                {
                    marbleRecords++;
                    totalCostMarble += totalCost;
                    totalSqFtMarble += totalMaterialSqFt;
                }
                else if(toupper(stoneCode)== 'Q')
                {
                    quartzRecords++;
                    totalCostQuartz += totalCost;
                    totalSqFtQuartz += totalMaterialSqFt;
                }
            }
        } //END while loop
        
        
        //close the file
        inputFile.close();
        
        //print out summary data
        cout << endl;
        cout << "Counts: " << "\t";
        cout << "Total Records = " << totalRecords << "\t";
        cout << "Records with Errors = " << totalErrorCount <<  "\t";
        cout << "Records without Errors = " << totalNonError << "\t" << endl;
        cout << endl;
        
        cout << "\t\t\t" << "TOTALS (records without errors)" << endl;
        cout << setw(15) << "Stone" << setw(15) << "Count" << setw(20) << "Square Feet";
        cout << setw(25) << "Cost" << endl;
        cout << "______________________________________________________________________________";
        cout << "____________________";
        cout << endl;
        
        
        //print marble data
        cout << setw(15) << "Marble" << setw(15) << marbleRecords;
        cout << setw(20) << totalSqFtMarble << setw(30) <<totalCostMarble;
        cout << endl;
        
        
        //print granite data
        cout << setw(15) << "Granite" << setw(15) << graniteRecords;
        cout << setw(20) << totalSqFtGranite << setw(30) <<totalCostGranite;
        cout << endl;
        
        
        //print quartz data
        cout << setw(15) << "Quartz" << setw(15) << quartzRecords;
        cout << setw(20) << totalSqFtQuartz << setw(30) << totalCostQuartz;
        cout << endl;     
        cout << "______________________________________________________________________________";
        cout << "____________________" << endl;
        cout << endl;
        
        cout << "\t\t" << "*****************************************************" << endl;
        cout << "\t\t" << "*             Count of Individual Errors            *" << endl;
        cout << "\t\t" << "*****************************************************" << endl;
        cout << endl;
        
        cout << setw(25) << OrderDeliverySame << " - order date and delivery date same" << endl;
        cout << setw(25) << DeliveryDateTooFar << " - delivery date too far in future" << endl;
        cout << setw(25) << invalidStoneCode << " - stone code not valid." << endl;
        cout << setw(25) << invalidLength << " - length not valid" << endl;
        cout << setw(25) << invalidDepth << " - depth not valid" << endl;
        cout << setw(25) << invalidHeight << " - height not valid" << endl;
        cout << setw(25) << invalidLengthEdges << " - length edges to finish not valid" << endl;
        cout << setw(25) << invalidDepthEdges << " - depth edges to finish not valid" << endl;
        cout << "\t\t" << "____________________________________________________" << endl;
        cout << setw(25) << totalErrors << " - total count of all errors in all records" << endl;
        cout << setw(25) << multipleErrorRecords;
        cout << " - count of records with multiple errors" << endl;
    } //END else part of if(!inputFile)
    
    return 0;
} //END function main