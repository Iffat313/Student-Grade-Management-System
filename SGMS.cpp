#include <iostream> //for basic I/O
#include <fstream> //for basic/fundemtnal (MUST) of creating, writing, and reading files. 
#include <sstream> //for istringstream object  to use iss(value) method from said object to read a specific word from a line within in a fil. This relies on getline(x,y) so it can break the word down within the line.
#include <vector>
using namespace std;

//global variables

string Username;
string Password;
int UserInput;
char AccessGranted;

string LogIn();

class Admin{
    public: //access specifier
        float ClassAverageGPA(); //returns the class average GPA via int
        float LowestGPA(); //returns the lowest GPA in the class via float
        float HighestGPA(); //returns the highest GPA in the class via float
        void GradeDistribution(); //displays students who got A, B, etc
        void SortByName();
        void SortByGrade();
        void Modify(string Value);
        void LoadStudentRecord(); //loads student record from file and uploads it to terminal in the form of student ID, name, Grade N
        void AddStudentRecord(); //allows admin to enter a students data into a plain text file, creates a student record
        //~Admin(); //destructor
};

class Student{
    public: //access specifier
        float MyGPA(); //returns currently logged in student's GPA via float
        void MyGrades(); //returns 
        //~Student(); //destructor
};

int main(){

    cout << "Welcome, would you like to log in {Y/N}? ";
    cin >> AccessGranted;

    if(AccessGranted == 'N'){
        return 1;
    }

    cout << "Username: ";
    cin >> Username;
    cout << "Password: ";
    cin >> Password;  

    string UserType = LogIn();
        if(UserType == "Student"){
            cout << "You are a student. Welcome back user " + Username + "\n"; 
        }
        else if(UserType == "Admin"){
            cout << "You are a Admin. Welcome back user " + Username + "\n"; 
        }
        else{
            cout << "User doesn't exsist or account creds are incorrect \n";
            main();
        }
    
    /*
    - 
    */

    Admin AdminObject; //creates an instance of the Admin class as the user is a Admin
    Student StudentObject; //creates an instance of the Student class as the user is a student



    do{ //for admin
        cout << "1. Logout \n";
        cout << "2. Add a Student Record \n";
        cout << "Enter: ";
        cin >> UserInput;


        if(UserInput == 1){
            main();
        }
        else if(UserInput == 2){
            AdminObject.AddStudentRecord();
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

//define the functions outside of the class for code optimization 

void Admin::AddStudentRecord(){ 
    int NumSubjects, Grade;
    string StudentID, StudentName;

    cout << "Enter the number of subjects: ";
    cin >> NumSubjects;
    vector<int>ListOfGrades(NumSubjects); //the number of grade(s) == number of of subjects
    cout <<"    Enter Student ID: ";
    cin >> StudentID;
    cout <<"    Enter Student Name: ";
    cin >> StudentName;
    if(NumSubjects == 1){
        cout <<"    Enter " <<  NumSubjects  <<  " grade (comma-separated): "; 
    }
    else{
        cout <<"    Enter " <<  NumSubjects  <<  " grades (comma-separated): "; 
    }
    for(int i = 0; i<NumSubjects; i++){
        cin >> ListOfGrades[i];
    }

    ofstream FileObject("StudentData.txt", ios::app); //we created an instance of the ofstream class to write to a file named StudentData, the ios:app makes it to where we append rather than overwrite

    FileObject << StudentID << "\n";
    FileObject << StudentName << "\n";
    for(int j = 0; j<ListOfGrades.size(); j++){
        if(j == ListOfGrades.size() - 1){
            FileObject << ListOfGrades[j] << "\n"; //if we are on the last grade of the vector to put on the text file we dont want to put a comma after it as it is the last grade
            break;
        }
        FileObject << ListOfGrades[j] << ", ";
    }

    FileObject.close(); //close the file for good practice

    cout << "Student Added Successfully \n";

    

}




/*
- If you attempt to read from a file that doesnt exsist there wont be an error but rather the program wont be able to print anything onto the output as there is nothing to read

- When it comes to writing to a file and the file does not exsist, it will create that file and write the specified contents. We use the class ofstream from the lib fstream

- When it comes to writing to a file and the file does exsist, to not overwite the contents in the file we use ios::app and we still use the lib ofstream:
 (FYI $ means user specified! Can be anything)
ofstream $YOUR_OBJECT_NAME_FOR_CLASS_ofstream ("$FILENAME.TXT", ios::app);

(also applies if the file doesnt exsist, it will create it)

*/