#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //needed to parse strings
#include "Statlib.h"

using namespace std;

int main()
{

    string line, option, arg1, arg2;
    bool repeat = true;

    cout << "Welcome to Statistics Analyzer" << endl;
    //the while loop is used to tell if the user still wants to use the program or not
    cout << "\nWhat would you like to do?" << endl;
    cout << "Type 'HELP' for  options and 'END' to stop" << endl << endl;
    while(repeat)
    {
        //refreshes the strings into nothing so that the command system works flawlessly
        option = "";
        arg1 = "";
        arg2 = "";
        getline(cin, line); // this replaces cin << because this gets all the commands + arugments
                            // It just needs to divide them
        //the following code divides all of them and places them in separate string variables
        istringstream command(line);
        getline (command, option, ' ');
        getline (command, arg1, ' ');
        getline (command, arg2, ' ');

        //options:
        if (option == "read"){
            if(arg1 == ""){
                cout << "Please enter name of file to read: ";
                getline(cin,arg1);
            }
            read(arg1);
        }

        else if (option == "HELP"){
            help();
        }

        else if (option == "showall"){
            show_data();
        }

        else if (option == "switch"){
            Switch();
        }

        else if (option == "head"){
            if(arg1 == ""){ //this is the first time that this is shown, so it will be explained here
                    //arg 1 is always read in the first part, but if the user didn't specify anything, it will be trapped here
                    //then the program will ask how many items or if they would use x or y (Depending on the command, see other options down)
                    //This is a good way to make it interactive for NEW users
                cout << "Please enter how many items you want to see: ";
                getline(cin, arg1);
            }
            head(stoi(arg1)); //stoi means string to integer, since the head()
                                //requires a integer in its argument, we will turn argument 1 into an int
        }

        else if (option == "tail"){
            if(arg1 == ""){
                cout << "Please enter how many items you want to see: ";
                getline(cin, arg1);
            }
            tail(stoi(arg1));
        }

        else if (option == "count"){
            if(arg1 == ""){
                cout << "Please choose between x and y: ";
                getline(cin, arg1);
            }

            if(arg1 == "x"){
                cout << "x has " << *x_counter << " items" << endl << endl;
            }

            else if(arg1 == "y"){
                cout << "y has " << *y_counter << " items" << endl << endl;
            }
        }

        else if (option == "max"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                Max_Show(x,x_counter);
            }

            else if(arg1 == "y"){
                Max_Show(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if (option == "min"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                Min_Show(x,x_counter);
            }

            else if(arg1 == "y"){
                Min_Show(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "range"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                range(x,x_counter);
            }

            else if(arg1 == "y"){
                range(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "mean"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                Mean_Show(x,x_counter);
            }

            else if(arg1 == "y"){
                Mean_Show(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "median"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                median(x,x_counter);
            }

            else if(arg1 == "y"){
                median(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "mode"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                mode(x,x_counter);
            }

            else if(arg1 == "y"){
                mode(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "PVar"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                PopVar(x,x_counter);
            }

            else if(arg1 == "y"){
                PopVar(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "SVar"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                SamVar(x,x_counter);
            }

            else if(arg1 == "y"){
                SamVar(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "PStdev"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                PStdDev(x,x_counter);
            }

            else if(arg1 == "y"){
                PStdDev(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "SStdev"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg1 == "x"){
                SStdDev(x,x_counter);
            }

            else if(arg1 == "y"){
                SStdDev(y,y_counter);
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "Hist"){
            if(arg1 == ""){
                cout << "Please choose between x or y: ";
                getline(cin,arg1);
            }

            if(arg2 == ""){ //this is the only time where arg2 is needed. It's just the same as arg1
                cout << "Please enter increments per bin: ";
                getline(cin, arg2);
            }

            if(arg1 == "x"){
                Hist(x,x_counter, stod(arg2)); //stod just truns the string (arg2) into a double value.
            }

            else if(arg1 == "y"){
                Hist(y,y_counter, stod(arg2));
            }

            else{
                cout << "Error, unknown column/data set" << endl << endl;
            }
        }

        else if(option == "lbf"){
            LoBF_show();
        }

        else if(option == "cd"){
            CoD();
        }

        else if(option == "END"){
            cout << "Thank you for using Statistics Analyzer" << endl;
            repeat = false;
        }

        else{
            cout << "Please enter the right command, type HELP to know all the commands" << endl << endl;
        }
    }

}







