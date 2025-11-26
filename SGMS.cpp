#include <iostream> //for basic I/O
#include <fstream> //for basic/fundemtnal (MUST) of creating, writing, reading files. 
#include <sstream> //for istringstream object  to use iss(value) method from said object to read a specific word from a line within in a fil. This relies on getline(x,y) so it can break the word down within the line.
#include <vector>
using namespace std;

//global variables

string Username;
string Password;
string UserInput;
char AccessGranted;

string LogIn();

class Admin{
    float ClassAverageGPA(); //returns the class average GPA via int
    float LowestGPA(); //returns the lowest GPA in the class via float
    float HighestGPA(); //returns the highest GPA in the class via float
    void GradeDistribution(); //displays students who got A, B, etc
    void SortByName();
    void SortByGrade();
    void Modify(string Value);
    void LoadStudentRecord(); //loads student record from file and uploads it to terminal in the form of student ID, name, Grade N
    void AddStudentRecord(); //allows admin to enter a students data into a plain text file
};

class Student{
    float MyGPA(); //returns currently logged in student's GPA via float
    void MyGrades(); //returns 
};

int main(){
    cout << "Welcome, would you like to log in {Y/N}? ";
    cin >> AccessGranted;

    cout << "Username: ";
    cin >> Username;
    cout << "\n";
    cout << "Password: ";
    cin >> Password;  

    string UserType = LogIn();
        if(UserType == "Student"){
            Student StudentObject;
            cout << "You are a student. Welcome back user " + Username; 
        }
        else if(UserType == "Admin"){
            Admin AdminObject;
            cout << "You are a Admin. Welcome back user " + Username; 
        }
        else{
            cout << "User doesn't exsist or account creds are incorrect \n";
            main();
        }



    do{ //for admin
        cout << "1. Logout \n";
        cout << "2. Add a Student Record \n";
        cin >> UserInput;


        if(UserInput == "LogOut"){
            main();
        }
        else if(UserInput == "Add a Student Record"){
            
        }
        
    }while((AccessGranted!='N') && (UserType == "Admin"));
}




string LogIn(){
    //local variable use and everytime this method everything happens again cincluding re-declaring the obkect from ifstream
    string Text; //LV 1
    vector<string>Words;


    ifstream File("UserCreds.txt"); // read from the text file , ifstream is an object from ftream library to read from the text file

    while(getline(File, Text)){ //as we traverse through the while loop, Text will read/intialized by every char from the file until it see's a new line, thus reading the file line by line in each iteration. Thus, 1st iteration is the 1st line  stored in text so and so foruth

        istringstream iss(Text); //istringstream is an object from sstream lib and iss is a method that breaks down Text into words,
        string WordFromLine; //Create a variable of type string which will be used to store each word from the current line of the current iteration

        while(iss >> WordFromLine){ //Niw that 
            Words.push_back(WordFromLine);
        }
    }

    for(int i = 0; i<Words.size(); i++){
        if(Words[i] == Username){
           continue;
        }
        if(Words[i] == Password){
            i = i - 4;
            return Words[i];
        }
        
    }

    return "bad";

}