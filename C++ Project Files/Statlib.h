#ifndef STATLIB_H
#define STATLIB_H
#include <string>
#include <vector>

//Statlib is created by Diaz, Andreas Josef C. and Fernan, Simon Fredrick J.
using namespace std;
    //Extern is used so that compiler can find these variables on Statlib.cpp
    //This is placed here so that the main.cpp can call them
    extern vector<double> *x; //extern tells the compiler that the variables exist somewhere, and needs to find them
    extern vector<double> *y;
    extern int *y_counter;
    extern int *x_counter;

    //The following code are only used to calculate and to return values
    //They are created so that lines of code may be saved
    void Mean(vector<double> *data, int *counter);
    void Max_Min(vector<double> *data, int *counter);
    void distance(vector<double> *data, int *counter);
    void PVar(vector<double> *data, int *counter);
    void SVar(vector<double> *data, int *counter);
    void LoBF();
    void DataSize();


    //The following void functions are commands for statistics analysis
    void read(string Data_File);
    void help();
    void items(int *counter);
    void show_data();
    void head(int no);
    void tail(int no);
    void Switch();
    void Max_Show(vector<double> *data, int *counter);
    void Min_Show(vector<double> *data, int *counter);
    void range(vector<double> *data, int *counter);
    void Mean_Show(vector<double> *data, int *counter);
    void mode(vector<double> *data, int *counter);
    void median(vector<double> *data, int *counter);
    void PopVar(vector<double> *data, int *counter);
    void SamVar(vector<double> *data, int *counter);
    void PStdDev(vector<double> *data, int *counter);
    void SStdDev(vector<double> *data, int *counter);
    void Hist(vector<double> *data, int *counter, double inc);
    void LoBF_show();
    void CoD();

#endif // STATLIB_H
