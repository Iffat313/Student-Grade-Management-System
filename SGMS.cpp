#include <iostream>
#include <fstream>

using namespace std;

//global variables

string Username;
string Password;
string UserInput;
char AccessGranted;

void LogIn();

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
    cout << "Welcome, would you like to log in {Y/N}?";
    cin >> AccessGranted;

    if(AccessGranted == 'Y'){
        LogIn();
    }

    do{
        cout << "1. Logout";
        cout << "2. Add a Student Record";

        if(UserInput == "LogOut"){
            main();
        }
        else if(UserInput == "Add a Student Record"){
            
        }
        
    }while(AccessGranted!='N');
}

void LogIn(){

    cout << "Username: ";
    cin >> Username;
    cout << "\n";
    cout << "Password: ";
    cin >> Password;  

    //local variable use and everytime this method everything happens again cincluding re-declaring the obkect from ifstream
    string Text;

    ifstream File("UserCreds.txt");

    while(getline(File, Text)){
        if(Text == Username){
            "user exsists!";
        }
    }



}