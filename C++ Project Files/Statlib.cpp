#include <iostream>
#include <fstream> //to read the files
#include <sstream> // also needed for reading files
#include <iomanip> //used to create a good visual table
#include <vector> // A better version of Arrays, can append without having any problems in indexes
#include <string>
#include <cmath> //Only used for sqrt()
#include <algorithm> //Used to sort for median
#include "Statlib.h"

//Statlib is created by Diaz, Andreas Josef C. and Fernan, Simon Fredrick J.

using namespace std;
//We need the following variables to be global in this .cpp file so that we can
//call the variable directly
int i, counter=0;
double stat_max, stat_min, mean, population_variance, sample_variance, sum_dist = 0, m, b, r, abs1;
string sign;
const char *sep = " ";
const int width = 12;

//Following variables are crucicial for placing the data from a file to C++ memory.
vector<double> *x;
vector<double> *y;
int *y_counter = new int (0);
int *x_counter = new int (0);




//The Following Functions are only calculating Functions
//they are created so that the creators of this library do
//not have to repeat the lines on the command voids
// and to save code lines
//These functions are only called in this Statlib.cpp

//Finds the max and minimum values of the data set
void Max_Min(vector<double> *data, int *counter){
    stat_max = (*data)[0];
    stat_min = (*data)[0];
    for(i=0; i< (*counter); i++) {
        if(stat_max < (*data)[i]) {
            stat_max = (*data)[i];
        }
        if(stat_min > (*data)[i]) {
            stat_min = (*data)[i];
        }
    }
}

void Mean(vector<double> *data, int *counter) {
    // simply gets the mean of the data set
    double *sum = new double (0);
    for(i = 0; i < (*counter); i++) {
        (*sum) += (*data)[i];
    }
    mean = (*sum) / (*counter);
    delete sum;
}

// distance is used for the variances and Standard Deviation voids
void distance(vector<double> *data, int *counter){
    sum_dist = 0;
    Mean(data, counter);
    for (i=0; i<(*counter); i++) {
        sum_dist += ((*data)[i] - mean) * ((*data)[i] - mean);
    }
}

//both PVar and Svar use the formula with the mean variable, it's easier to
//create rather than other formulas.
// used to find the population variance
void PVar(vector<double> *data, int *counter){
    distance(data, counter);
    population_variance = sum_dist/(*counter);
}

//used to find the sample variance
void SVar(vector<double> *data, int *counter){
    distance(data, counter);
    sample_variance = sum_dist/((*counter)-1);
}

//Finds Line of Best Fit and Correlation Coefficient
void LoBF(){
    double xave, yave, nume1 = 0, deno1 = 0, nume2 = 0 , deno2 = 0, sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0, sumy2 = 0;
    int nitems = counter;

    //calculate means of the data set
    Mean(x, x_counter);
    xave = mean;
    Mean(y, y_counter);
    yave = mean;

    // formula for m
    for (int i = 0; i <= nitems -1; i++) {
        double yvalLoBF, xvalLoBF;

        //Line of Best Fit vals
        xvalLoBF = (*x)[i] - xave;
        yvalLoBF = (*y)[i] - yave;

        nume1 = xvalLoBF * yvalLoBF + nume1;
        deno1 = xvalLoBF * xvalLoBF + deno1;

        //Coefficent of correlation vals
        // sum is short for summation
        sumx = sumx + (*x)[i];
        sumy = sumy + (*y)[i];
        sumxy = sumxy + (*x)[i] * (*y)[i];
        sumx2 = sumx2 + (*x)[i] * (*x)[i];
        sumy2 = sumy2 + (*y)[i] * (*y)[i];
    }
    //formula for the slope of the line
    m = nume1 / deno1;

    //formula for y intercept
    b= yave - (m * xave);

    //coefficient of correlation
    nume2 = (nitems * sumxy) - (sumx * sumy);
    deno2 = sqrt((nitems * sumx2 - sumx * sumx) * (nitems * sumy2 - sumy * sumy));

    r = nume2 / deno2;

    // used to check if the value of r is positive or negative
    if (r < 0) {
        sign = "negative";
    }
    else {
        sign = "positive";
    }

    // gets the absolute value of r
    abs1 = abs(r);
}

//Checks if the indexs of x and y are the same
void DataSize() {
    if ((*x_counter) > (*y_counter)) {
        cout << "\n\nNumber of items are not the same, x has more numbers than y. Please input a better data file" << endl;
        cout << "Program will use y's counter as the number of items." << endl << endl;
        counter = (*y_counter);
    }
    else if ((*x_counter) < (*y_counter)) {
        cout << "\n\nNumber of items are not the same, y has more numbers than x. Please input a better data file" << endl;
        cout << "Program will use x's counter as the number of items." << endl << endl;
        counter = (*x_counter);
    }
    else{
        counter = *x_counter;
    }
}


//Following Functions are the command functions, which would be called on main.cpp

void read(string Data_File){
    //Self Explanatory, this function opens the given file and then reads each line and
    //places it on a vector, specifically on the specified data set.
    cout << endl << endl;
    ifstream files(Data_File);
    if(files.is_open()) {
        (*x_counter) = 0; //resets the counter if user reads a new file
        (*y_counter) = 0;
        x = new vector<double>; //resets the vector if user reads a new file
        y = new vector<double>;
        string placeholder;
        int *x_error_counter = new int(0);
        int *y_error_counter = new int(0);

        cout << "Importing files to x and y" << endl << endl;
        while (getline(files, placeholder)) {
            if(placeholder != ""){ //First error trapping in the file, so that it doesn't read blank lines
                istringstream iss(placeholder);
                string sec_placeholder;
                getline(iss, sec_placeholder, '\t');
                if(sec_placeholder != ""){//Second Error Trapping, so that it would know if there are blank values in x
                    (*x).push_back(stod(sec_placeholder));
                    (*x_counter)++;
                    (*x_error_counter)++;
                }
                else { //Here the program tries to say to the user that there is no value in one of the rows of x and requests to change to a
                        // better data file. The user can still use it, but it would have problems later on
                        //*Garbage in, Garbage out*
                    (*x).push_back(0);
                    (*x_error_counter)++;
                    cout << "WARNING: No Data Found on index " << *x_error_counter << " of x" << endl;
                    cout << "All Statistics Commands could be inaccurate or could have errors due to this" << endl;
                    cout << "Please change into a better data file" << endl;
                    cout << "Will replace to 0..." << endl << endl;
                }

                getline(iss, sec_placeholder, '\t');
                if(sec_placeholder != ""){ //Third Error Trapping, now it's for y
                    (*y).push_back(stod(sec_placeholder));
                    (*y_counter)++;
                    (*y_error_counter)++;
                }
                else{
                    (*y).push_back(0);
                    (*y_error_counter)++;
                    cout << "WARNING: No Data Found on index " << *y_error_counter << " of y" << endl;
                    cout << "All Statistics Commands could be inaccurate or could have errors due to this" << endl;
                    cout << "Please change into a better data file" << endl;
                    cout << "Will replace to 0..." << endl << endl;
                }
            }
        }

        cout<<"Done importing files to x and y" << endl << endl;
    }

    else {// 4th Error trapping so that users can know that there are problems with the file, or the file name inputted.
        cout << "Unable to Import File" << endl << endl;
    }

    files.close();
}

//this function is used to display information on commands that can be used
void help() {
    const int width_help = 30;

    cout << "--------------------------------------------------HELP----------------------------------------------------" << endl;
    cout <<"List of Commands with syntax:" << endl << endl;
    cout << left << setw(width_help) << setfill(*sep) << "Command Syntax"; //left and setw() and setfill() are part of library iomanip.
                                                                            //It makes good formatting! Recommend this.
                                                                            //left makes it left aligned
                                                                            // setw() sets the width of each column
                                                                            // setfill() sets what character to use for filling
    cout << left << setw(width_help) << setfill(*sep) << "Example Command";
    cout << left << setw(width_help) << setfill(*sep) << "Description" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "read (datafilename.extension)";
    cout << left << setw(width_help) << setfill(*sep) << "read test2.txt";
    cout << left << setw(width_help) << setfill(*sep) << "reads the given file and places it in two vectors" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "switch";
    cout << left << setw(width_help) << setfill(*sep) << "switch";
    cout << left << setw(width_help) << setfill(*sep) << "switches x and y data" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "count (x/y) ";
    cout << left << setw(width_help) << setfill(*sep) << "count y";
    cout << left << setw(width_help) << setfill(*sep) << "shows how many items are in the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "showall";
    cout << left << setw(width_help) << setfill(*sep) << "showall";
    cout << left << setw(width_help) << setfill(*sep) << "shows all the data of the data frame*" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "head (# of items)";
    cout << left << setw(width_help) << setfill(*sep) << "head 5";
    cout << left << setw(width_help) << setfill(*sep) << "shows the first few data items of the data frame" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "tail (# of items)";
    cout << left << setw(width_help) << setfill(*sep) << "tail 5";
    cout << left << setw(width_help) << setfill(*sep) << "shows the last few data items of the data frame" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "max (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "max y";
    cout << left << setw(width_help) << setfill(*sep) << "shows the maximum value in the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "min (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "min y";
    cout << left << setw(width_help) << setfill(*sep) << "shows the minimum value in the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "range (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "range y";
    cout << left << setw(width_help) << setfill(*sep) << "shows the range of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "mean (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "mean x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the mean of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "median (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "median x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the median of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "mode (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "mode x";
    cout << left << setw(width_help) << setfill(*sep) << "shows one* mode of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "PVar (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "PVar x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the population variance of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "SVar (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "SVar x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the sample variance of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "PStdev (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "PStdev x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the population standard deviation of " << endl;

    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "  the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "SStdev (x/y)";
    cout << left << setw(width_help) << setfill(*sep) << "SStdev x";
    cout << left << setw(width_help) << setfill(*sep) << "shows the sample standard deviation of the chosen" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "  column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "Hist (x/y) (Increment)";
    cout << left << setw(width_help) << setfill(*sep) << "Hist x 10";
    cout << left << setw(width_help) << setfill(*sep) << "shows the histogram of the chosen column/data set" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "cd";
    cout << left << setw(width_help) << setfill(*sep) << "cd";
    cout << left << setw(width_help) << setfill(*sep) << "shows the correlation of determination of the data frame" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "lbf";
    cout << left << setw(width_help) << setfill(*sep) << "lbf";
    cout << left << setw(width_help) << setfill(*sep) << "shows the line of best fit and correlation coefficents" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "";
    cout << left << setw(width_help) << setfill(*sep) << "  of the data frame" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "HELP";
    cout << left << setw(width_help) << setfill(*sep) << "HELP";
    cout << left << setw(width_help) << setfill(*sep) << "shows all the possible commands in the program" << endl;

    cout << left << setw(width_help) << setfill(*sep) << "END";
    cout << left << setw(width_help) << setfill(*sep) << "END";
    cout << left << setw(width_help) << setfill(*sep) << "Ends the program" << endl << endl;

    cout << left << setw(width_help) << setfill(*sep) << "Please type the command as seen" << endl;
    cout << left << setw(width_help) << setfill(*sep) << "*If data size is large, it is suggested not to use this command" << endl;
    cout << left << setw(width_help) << setfill(*sep) << "*Please input text files with 2 columns of data separated by a tab only" << endl;
    cout << left << setw(width_help) << setfill(*sep) << "*The program would only output a single mode if there are multiple modes in the data set" << endl;

    cout << endl;
}

void show_data() {
    //Just like the name suggests, this displays the data by using a for loop
    //Then it outputs the total number of items found in the file
    cout << "Show Data" << endl;
    if((*x_counter) > (*y_counter)){
        counter = (*x_counter);
    }
    else if ((*y_counter) > (*x_counter)){
        counter = (*y_counter);
    }
    else{
        counter = (*x_counter);
    }

    cout << left << setw(width) << setfill(*sep) << "x";
    cout << left << setw(width) << setfill(*sep) << "y" << endl;
    for(i=0; i< counter; i++) {
        // used in the loop to display the data individually per line
        cout << left << setw(width) << setfill(*sep) << (*x)[i];
        cout << left << setw(width) << setfill(*sep) << (*y)[i] << endl;
    }
    cout << "Data has " << counter << " items" << endl;
    cout << endl;
}

void head(int no) {
    //head shows the head of the data
    //it also takes input to how many items should be displayed
    //the number of items input affects the number of times the loop repeats
    cout << "\nHead" << endl << endl;
    DataSize();
    if (no <= counter){
        cout << left << setw(width) << setfill(*sep) << "x";
        cout << left << setw(width) << setfill(*sep) << "y" << endl;

        for(i=0; i<no; i++) {
            cout << left << setw(width) << setfill(*sep) << (*x)[i];
            cout << left << setw(width) << setfill(*sep) << (*y)[i] << endl;
        }
    }

    else{
        cout << "The input is greater than the number of data items" << endl;
    }
    cout << endl;
}

void tail(int no) {
    //tail shows the tail of the data
    //it also takes input to how many items should be displayed
    //the number of items input affects the number of times the loop repeats
    cout << "\nTail" << endl;
    DataSize();
    if (no <= counter){
        cout << left << setw(width) << setfill(*sep) << "x";
        cout << left << setw(width) << setfill(*sep) << "y" << endl;

        for(i= counter - no; i < counter; i++) {
            cout << left << setw(width) << setfill(*sep) << (*x)[i];
            cout << left << setw(width) << setfill(*sep) << (*y)[i] << endl;
        }
    }


    else{
        cout << "The input is greater than the number of data items" << endl;
    }
    cout << endl;
}

void Switch(){
    cout << "Switching x and y..." << endl;
    vector<double> *vec_placeholder = new vector<double>; //created a place holder for temporary placement of one of the vectors
    int *counter_placeholder = new int(0); //also created a place holder for counter
                                            //(In case there is a difference between the x and y counters)
    *vec_placeholder = *x;
    *x = *y;
    *y = *vec_placeholder;
    *counter_placeholder = *x_counter;
    *x_counter = *y_counter;
    *y_counter = *counter_placeholder;
    delete vec_placeholder, counter_placeholder;
    cout << "Switched x and y" << endl << endl;
}

void Max_Show(vector<double> *data, int *counter) {
    //finds the max data of the file by comparing the first value to the next one
    Max_Min(data, counter);
    cout << "Maximum value is: " << stat_max << endl << endl;
}

void Min_Show(vector<double> *data, int *counter) {
    //finds the min data of the file by comparing the first value to the next one
    Max_Min(data, counter);
    cout << "Minimum value is: " << stat_min << endl << endl;
}

void range(vector<double> *data, int *counter) {
    // finds the range of the values in the data set
    cout << "Range" << endl;
    Max_Min(data, counter);
    cout << "Range is " << stat_max - stat_min << endl << endl;
}

void Mean_Show(vector<double> *data, int *counter){
    cout << "Mean" << endl;
    Mean(data, counter);
    cout << "Mean is " << mean << endl << endl;
}

void mode(vector<double> *data, int *counter) {
    //uses a variable to count the number of times something occurs
    //if something occurs more then the current value it uses that new number as the mode
    cout << "Mode" << endl;
    int* ipRepetition = new int[(*counter)];

    for (i = 0; i < (*counter); ++i) {
        ipRepetition[i] = 0;
        int j = 0;
        bool bFound = false;

        while ((j < i) && ((*data)[i] != (*data)[j])) {
            if ((*data)[i] != (*data)[j]) {
                ++j;
            }
        }
        ++(ipRepetition[j]);
    }

    int iMaxRepeat = 0;

    for (i = 1; i < (*counter); ++i) {
        if (ipRepetition[i] > ipRepetition[iMaxRepeat]) {
            iMaxRepeat = i;
        }
    }

    if (ipRepetition[iMaxRepeat] == 1) {
        cout << "Mode does not exist." << endl << endl;
    }

    else {
        cout << "Mode is: " << (*data)[iMaxRepeat] << endl << endl;
    }
    delete [] ipRepetition;
}

void median(vector<double> *data, int *counter) {
    //finds the number of items, divides it by two and uses that to find the
    //median of the set of numbers
    cout << "Median" << endl;
    int top = 0, bot = 0;
    double median, midval;
    vector<double> *sorted = new vector<double>  (*data); // copy the values from the original vector to another vector for rearranging
    //used to arrange the vector for when we find the median
    sort((*sorted).begin(), (*sorted).end());
    if ((*counter)%2 == 0) {
        midval = (*counter) / 2;
        top = midval + 0;
        bot = midval - 1;
        median = ((*sorted)[top] + (*sorted)[bot]) / 2;
        cout << "Median is: " << median << endl << endl;
    }
    else {
        midval = ((*counter)+ 0) / 2;
        median = (*sorted)[midval];
        cout << "Median is: " << median << endl << endl;
    }
    delete sorted;
    delete &top, &bot, &median, &midval;

}

// shows the Population Variance
void PopVar(vector<double> *data, int *counter) {
    cout << "Population Variance" << endl;
    PVar(data, counter);
    cout << "Population Variance: " << population_variance << endl << endl;
}

// shows the Sample Variance
void SamVar(vector<double> *data, int *counter) {
    cout << "Sample Variance" << endl;
    SVar(data, counter);
    cout << "Sample Variance: " << sample_variance << endl << endl;
}

//used to find population standard deviation
void PStdDev(vector<double> *data, int *counter) {
    cout << "Population Standard Deviation" << endl;
    PVar(data, counter);
    cout << "Population Standard Deviation: " << sqrt(population_variance)
         << endl << endl;
}

//used to find sample standard deviation
void SStdDev(vector<double> *data, int *counter) {
    cout << "Sample Standard Deviation" << endl;
    SVar(data, counter);
    cout << "Sample Standard Deviation: " << sqrt(sample_variance)
         << endl << endl;
}

//Histogram code from histogram lib, adjusted only the variables so that it can take vectors
void Hist(vector<double> *data, int *counter, double inc) {
    int * bins;
    int nBins;
    double * binMarkers;

    Max_Min(data, counter);

    cout << "Histogram" << endl;
    int j;
    nBins = (int)(trunc((stat_max - stat_min))/inc + 2);
    if( (stat_min + nBins*inc) < stat_max) nBins++;

    bins  = new int[ nBins];
    for (i=0; i<nBins; i++)
        bins[i]=0;
    binMarkers = new double[nBins-1];

    for (i=0; i< nBins-2; i++) {
        binMarkers[i] = stat_min+i*inc;
    }
    binMarkers[ nBins-2] = stat_max;

    for ( i = 0; i< (*counter); i++) {
        for ( j = 0; j< nBins-1; j++) {
            if ((*data)[i] < binMarkers[j]) {
                bins[j]++;
                break;
            }
        }
        if ((*data)[i] >= binMarkers[nBins-2])
            bins[nBins-1]++;
    }

    int sum = 0;


    sum += bins[0];
    if (bins[0]>0)
        cout << "< " << binMarkers[0] <<": " << bins[0];

    for (j = 1; j< nBins-1; j++) {
        sum+=bins[j];
        cout <<"[ "<< binMarkers[j-1]<< ", " << binMarkers[j]
             <<"): " << bins[j] <<endl;
    }

    sum+= bins[nBins-1];
    if (bins[nBins-1]>0)
        cout << " > " << binMarkers[nBins-2] <<": "
             << bins[nBins-1]<<endl;
    cout << "Total counted: " << sum << endl << endl;
}


void LoBF_show() {
    //call data size
    DataSize();
    cout << "Line of Best Fit Formula" << endl << endl;
    //generates the slope and y-intercept of the line of best fit
    LoBF ();
    cout << "Line of Best Fit: " << endl;
    cout << "y = " << m << "x + " << b << endl <<  endl;
    cout << "Corellation Coefficient:" << endl;
    cout << "r = " << r << endl;

    // checks what is the absolute value of r
    // then displays output with the sign if it has a sign
    if ( abs1 > 0.9 && abs1 <= 1) {
        cout << "Very high " << sign << " correlation" << endl;
    }
    else if ( abs1 > 0.7 && abs1 <= 0.9) {
        cout << "High " << sign << " correlation" << endl;
    }
    else if ( abs1 > 0.5 && abs1 <= 0.7) {
        cout << "Moderate " << sign << " correlation" << endl;
    }
    else if ( abs1 > 0.3 && abs1 <= 0.5) {
        cout << "Low " << sign << " correlation" << endl;
    }
    else if ( abs1 > 0 && abs1 <= 0.3) {
        cout << "Negligible " << sign << " correlation" << endl;
    }
    else if (abs1 == 0){
        cout << "No correlation" << endl;
    }
    cout << endl;
}

void CoD() {
    //checks the size of the data
    DataSize();
    //used line of best fit function to ge the value of r
    LoBF ();
    cout << "Coefficient of Determination" << endl;
    //r * r is the coefficient of determination
    cout << "Percentage variation in y: r^2 = " << r * r << endl << endl;
}


