#include <iostream> //for basic I/O
#include <fstream> //for basic/fundemtnal (MUST) of creating, writing, and reading files. 
#include <sstream> //for istringstream object  to use iss(value) method from said object to read a specific word from a line within in a fil. This relies on getline(x,y) so it can break the word down within the line.
#include <vector> //to use vectors
#include <string> //so I can use certain built in methods for strings like getting the size
using namespace std;

//global variables & methods

string Username; //NOTE: The Username for Students == The StudentID for Students. for users of type Student, make sure there is NOT a duplicate in both Username and StudentID. Admins are added manually on the text file so no worries.
string Password;
int UserInput; 
char AccessGranted;

void Append(); //Inorder to register new students, we must add them into our databases (the two .txt files, the for the student info database by default the grades will be zero)
string LogIn();

class Admin{
    public: //access specifier
        float ClassAverageGPA(); //returns the class average GPA via float. So we must consider every student. Also used to display a summary stat 
        void LowestGPA(); //returns the lowest GPA in the class via float. Calculate the GPA for every student and return the GPA of student who has the Lowest. Also used to display summary stat method
        void HighestGPA(); //returns the highest GPA in the class via float. Calculate the GPA for every student 
        /*
        - GPA = Sum of the grade(s)/number of grades
        */
        void GradeDistribution(); //displays students who got A, B, etc
        void SortByName(); //Display summary stat method, specifically by students name in alphabetical order
        void SortByGrade(); //Display summary stat method, specifically bt students name via their grade from highest to lowest 
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

    Admin AdminObject; //creates an instance of the Admin class as the user is a Admin
    Student StudentObject; //creates an instance of the Student class as the user is a student
    
    cout << "Hello! Are you a new Student {Y/N}?: ";
    cin >> AccessGranted;

    if(AccessGranted == 'Y'){
        Append();
    }

    

    cout << "Welcome, would you like to log in {Y/N}?: ";
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

            do{ //for Student
                cout << "1. Logout \n";
                cout << "2. My GPA \n";
                cout << "3. My Grades \n";
                cout << "Enter: ";
                cin >> UserInput;

                if(UserInput == 1){
                    main();
                    break;
                }

                else if(UserInput == 2){
                    //
                }

                else if(UserInput == 3){
                    //
                }

                else{
                    cout << "Bad input, you must do an actual input from the list \n";
                }
            }while ((AccessGranted!='N') && (UserType == "Student")); 
        }

        else if(UserType == "Admin"){
            cout << "You are a Admin. Welcome back user " + Username + "\n";

            do{ //for Admin
                cout << "1. Logout \n";
                cout << "2. Add a Student Record \n";
                cout << "3. Retrieve The Class Average \n";
                cout << "4. Retrieve the highest GPA in the class \n";
                cout << "5. Retrieve the lowest GPA in the class \n";
                cout << "6. Retrieve Student Record \n";
                cout << "7. Retrieve Grade Distribution \n";
                cout << "8. Sort Students by Names \n";
                cout << "9. Sort Students by Grades \n";
                cout << "Enter: ";
                cin >> UserInput;


                if(UserInput == 1){
                    cout << "You will be redirected to the main login CLI now, goodbye \n";
                    main(); //calls the main method, recursive. Thus, the main method will start from the top all over again. 
                    break; //If we truly want to start all we need to make sure we leave this while loop so the def of it doesnt appear again. 
                }
                else if(UserInput == 2){
                    AdminObject.AddStudentRecord();
                }

                else if(UserInput == 3){
                    cout << "The class average is: " << AdminObject.ClassAverageGPA() << "\n";
                }

                else if(UserInput == 4){
                    AdminObject.HighestGPA();
                }

                else if(UserInput == 5){
                    AdminObject.LowestGPA();
                }

                else if(UserInput == 6){
                    AdminObject.LoadStudentRecord();
                }

                else if(UserInput == 7){
                    AdminObject.GradeDistribution();
                }

                else if(UserInput == 8){
                    AdminObject.SortByName();
                }

                else if(UserInput == 9){
                    AdminObject.SortByGrade();
                }
                
                else{
                    cout << "Bad input, you must enter an appropirate number \n";
                }
        
            }while((AccessGranted!='N') && (UserType == "Admin"));
        }

        else{
            cout << "User doesn't exsist or account creds are incorrect \n";
            main();
        }
}

void Append(){ //you will be writing to two files in this method so use ofstream
    string Text;
    string UN; //local Username of type string, we've already declared a gloabal var so dup is not allowed. Remember, for user Student, Username == ID
    string PW; //same as UN
    string StudentName; //we can re-use StudentName as it's a local varaible

    cout << "Enter your name: ";
    cin >> StudentName;
    cout << "Enter your Username, this will also be your Student ID (WSU FORMATE: xy####): ";
    cin >> UN;
    cout << "Enter your Password: ";
    cin >> PW;

    ofstream FileObject("UserCreds.txt", ios::app); //Add the user Student to the File/database that contains user creds

    FileObject << "\n";
    FileObject << "\n";
    FileObject << "Type: Student" << "\n";
    FileObject << "Username: " << UN << "\n";
    FileObject << "Password: " << PW << "\n";

    FileObject.close();

    ofstream FileObject2("StudentData.txt", ios::app); //Add the user Student to the file/database that contains information about the Student like their ID, etc

    FileObject2 << UN << "\n";
    FileObject2 << StudentName << "\n"; 
    FileObject2 << 0 << "\n";

}

string LogIn(){
    //local variable use and everytime this method everything happens again cincluding re-declaring the obkect from ifstream
    string Text; //LV 1
    int Pass = 0;
    int PlaceHolder = 0;
    vector<string>Words;


    ifstream File("UserCreds.txt"); // read from the text file , ifstream is a class from the fstream library to read from the text file. "File" is the object/instance of the class ifstream, which calls the pamatrized construcotr to open and read from a file

    while(getline(File, Text)){ //as we traverse through the while loop, Text will read/intialized by every char from the file until it see's a new line, thus reading the file line by line in each iteration. Thus, 1st iteration is the 1st line  stored in text so and so foruth

        istringstream iss(Text); //istringstream is a class from sstream lib and iss is the object/instance of the class istringstream. Were calling the paramtrized constructor of the class istringstream via the object parameter, which  breaks down Text into words,
        string WordFromLine; //Create a variable of type string which will be used to store each word from the current line of the current iteration

        while(iss >> WordFromLine){ //This inner while loop will break down the lines into words, we  will traverse through the words. Each word is a iteration, 1st word = 1st iteration etc
            Words.push_back(WordFromLine); //this is the def of the inner while loop. For every word/iteration, we will add it to our vector 
        }
    }

    for(int i = 0; i<Words.size(); i++){
        if(Words[i] == Username){
            Pass++;
           continue;
        }
        if(Words[i] == Password){
            Pass++;
            i = i - 4;
            PlaceHolder = i;
            break;
        }
        
    }

    if(Pass == 2){
        return Words[PlaceHolder];
    }

    return "bad";

}

//define the functions outside of the class for code optimization 

void Admin::AddStudentRecord(){ 
    int NumSubjects, Grade;
    string StudentID, StudentName;

    cout << "Enter the number of subjects: ";
    cin >> NumSubjects;
    vector<float>ListOfGrades(NumSubjects); //the number of grade(s) == number of of subjects
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
    for(int i = 0; i<NumSubjects; i++){ //user enters grade for each subject
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

    FileObject << "\n";

    FileObject.close(); //close the file for good practice

    cout << "Student Added Successfully \n";

}


float Admin::ClassAverageGPA(){

    float Avg = 0;
    float NumberFromLine = 0;
    string Text;
    vector<float>GradesFromFile;

    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        //first remove the the commas between the grades if any for each student
        for(char &c: Text){
            if(c == ','){
                c = ' ';
            }
        }


        //now, what are we going to do per line for the file?
        istringstream iss(Text);//It should be noted that the data type of the value passed in the paramtere for the pbject of the class to the constructor must be of a string type 
        while(iss >> NumberFromLine){
            GradesFromFile.push_back(NumberFromLine);
        }
    }

    for(int i = 0; i<GradesFromFile.size(); i++){
        Avg = Avg + GradesFromFile[i];
    }

    Avg = Avg/GradesFromFile.size();

    File.close();

    return Avg;
}

void Admin::HighestGPA(){
    float Highest = 0;
    float NumberFromLine = 0;
    float PlaceHolder = 0;
    float Counter = 0;
    float GPA = 0;
    string Text;
    bool Proceed = 0;
    vector<float>GradesFromFile;

    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        //first remove the the commas between the grades if any for each student
        for(char &c: Text){
            if(c == ','){
                c = ' ';
            }
        }


        //now, what are we going to do per line for the file?
        istringstream iss(Text);
        while(iss >> NumberFromLine){
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            Proceed = 1;
        }
        if(Proceed){
            //cout << GPA << "\n";
            GPA =  PlaceHolder/Counter;
            GradesFromFile.push_back(GPA);
            PlaceHolder = 0;
            Counter = 0;
            GPA = 0;
            Proceed = 0;
        }
    }

    Highest = GradesFromFile[0];
    for(int i = 0; i<GradesFromFile.size(); i++){
        if(Highest<GradesFromFile[i]){
            Highest = GradesFromFile[i];
        }
    }

    File.close();

    cout << "The highest GPA in the class is: " << Highest << "\n";
}

void Admin::LowestGPA(){
    float Lowest = 0;
    float NumberFromLine = 0;
    float PlaceHolder = 0;
    float Counter = 0;
    float GPA = 0;
    string Text;
    bool Proceed = 0;
    vector<float>GradesFromFile;

    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        //first remove the the commas between the grades if any for each student
        for(char &c: Text){
            if(c == ','){
                c = ' ';
            }
        }


        //now, what are we going to do per line for the file? 
        istringstream iss(Text);
        while(iss >> NumberFromLine){
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            Proceed = 1;
        }
        if(Proceed){
            GPA =  PlaceHolder/Counter;
            GradesFromFile.push_back(GPA);
            PlaceHolder = 0;
            Counter = 0;
            GPA = 0;
            Proceed = 0;
        }
    }

    Lowest = GradesFromFile[0];
    for(int i = 0; i<GradesFromFile.size(); i++){
        if(Lowest>GradesFromFile[i]){
            Lowest = GradesFromFile[i];
        }
    }

    File.close();

    cout << "The lowest GPA in the class is " << Lowest << "\n";

    
}

void Admin::LoadStudentRecord(){
    string Text;

    ifstream File("StudentData.txt");

    while(getline(File, Text)){
         cout << Text << "\n";
    }

    File.close();
}

void Admin::GradeDistribution(){
    string Text;
    float NumberfromLine = 0;
    float PlaceHolder = 0;
    float Counter = 0;
    float GPA = 0;
    bool Proceed = 0;
    vector<float>GradesFromFile;
    int GD[9];
    for(int j = 0; j<9; j++){
        GD[j] = 0; //set the value to each index (respective grade) to zero by default manually. 
    }

    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        //first remove the the commas between the grades if any for each student
        for(char &c: Text){
            if(c == ','){
                c = ' ';
            }
        }

        istringstream iss(Text);
        while(iss >> NumberfromLine){
            PlaceHolder = PlaceHolder + NumberfromLine;
            Counter++;
            Proceed = 1;
        }
        if(Proceed == 1){
            //cout << "Placeholder value: " << PlaceHolder << " ";
            //cout << "Counter value: " << Counter << "\n";
            GPA = PlaceHolder/Counter;
            GradesFromFile.push_back(GPA); //remember, a student's grade is based on their GPA.
            PlaceHolder = 0;
            Proceed = 0;
            Counter = 0;
        }

    }

    for(int i = 0; i<GradesFromFile.size(); i++){

        if((GradesFromFile[i]>= 95) && (GradesFromFile[i]<=100)){ //DONT USE || (OR) logical operator, remeber with or as long as 1/2 conditions are true the whole conditional statment is considered as true. Because almost every student may have a GPA of less than 100, using OR with this specific condition will cause it to be true when someone who has a B grade should get B not A. In short, for ranges, we use && 
            GD[0]++; //A
        }
        else if((GradesFromFile[i]>= 90) && (GradesFromFile[i]<95)){
            GD[1]++; //A-
        }
        else if((GradesFromFile[i]>= 85) && (GradesFromFile[i]<90)){
            GD[2]++; //B+
        }
        else if((GradesFromFile[i]>= 80) && (GradesFromFile[i]<85)){
            GD[3]++; //B
        }
        else if((GradesFromFile[i]>= 75) && (GradesFromFile[i]<80)){
            GD[4]++; //B-
        }
        else if((GradesFromFile[i]>= 70) && (GradesFromFile[i]<75)){
            GD[5]++; //C+
        }
        else if((GradesFromFile[i]>= 65) && (GradesFromFile[i]<70)){
            GD[6]++; //C
        }
        else if((GradesFromFile[i]>= 60) && (GradesFromFile[i]<65)){
            GD[7]++; //C-
        }
        else{
            GD[8]++; //F
        }

        cout << GradesFromFile[i] << "\n";
        
    }

   cout << "The number of people that got a A: " << GD[0] << "\n";
   cout << "The number of people that got a A-: " << GD[1] << "\n";
   cout << "The number of people that got a B+: " << GD[2] << "\n";
   cout << "The number of people that got a B: " << GD[3] << "\n";
   cout << "The number of people that got a B-: " << GD[4] << "\n";
   cout << "The number of people that got a C+: " << GD[5] << "\n";
   cout << "The number of people that got a C: " << GD[6] << "\n";
   cout << "The number of people that got a C-: " << GD[7] << "\n";
   cout << "The number of people that got a F: " << GD[8] << "\n";    
}


void Admin::SortByName(){
    string Text;
    string WordFromLine; //this will be the student name, with the way we will traverse in the file via the outer while loop
    int LineNumber = 0;
    int Four = 4;
    vector<string>NamesFromFile;

    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        LineNumber++;

        int Total = LineNumber + Four;
        if((Total%2!=0) || (Text == " ")){
            continue; //hitting this will cause us to go back to the while loop and ultimately the beginning of the def of it if the condition is true
        }
        
        istringstream iss(Text);
        while(iss >> WordFromLine){
            //cout << WordFromLine << "\n";
            NamesFromFile.push_back(WordFromLine);
        }

    }

    for(int i = 0; i<NamesFromFile.size(); i++){//this outer for loop represent the number of times we do a "process". We do a "process" based on the number of elements there are in the vector.
        //size_t NameLength = NamesFromFile[i].length(); //get the length of current student name (string) from the vector
        for(int j = 0; j<NamesFromFile.size()-1; j++){ //this 1st nested for loop is what causes us to always look at the first element within the vector when comparing it to other elements in the vector
            size_t NameLength = min(NamesFromFile[j].length(), NamesFromFile[j+1].length()); 
            /*
            - In order to alphabetically sort the student names from the file we need to get the student name length or the number of characters from the string
            - This is so we know how many letters we need to compare from the current string to the neighboring string. 
            - But we will get the minimum number of the length between the two strings, this is becuase both strings may not be of the same length and we should only compare what exsists! no useless work
            if the smaller string is essetially a substring in the bigger string when comparing, the bigger string will be first.
            - Lastly, notice how we get the minimum length between the two strings in the inner/process loop. 
            This is so we don't go out of bounds (a value that doesnt exsist) when getting the index for the neighbooring string, the iterator
            in the inner loop can only go to the second to last index of the vector, we can take adavantage of this and safely get the neighboring 
            string (j+1) without going out of bounds.
            */
            for(int z = 0; z<NameLength; z++){  //this 2nd nested for loop is needed to compare x character of the current string to the x character of the next string at x character via the second outer for loop
                if(NamesFromFile[j][z]>NamesFromFile[j+1][z]){ //THIS IF STATEMENT GENUIALLY DOES THE SORTING PROCESS STATED ABOVE FOR THE 2ND NEST FOR LOOP
                    string temp = NamesFromFile[j];
                    NamesFromFile[j] = NamesFromFile[j+1];
                    NamesFromFile[j+1] = temp;
                    break; //we will go the 1st inner loop and leave the 2nd inner loop, moving to the next string as we have just sorted two strings alphabetically.
                }
                else if(NamesFromFile[j] == NamesFromFile[j+1].substr(0, NamesFromFile[i].length())){//THIS ELSE IF STATEMENT HANDLES THE SCANIRO WHERE THE CURRENT STRING IS A SUBSTRING IN THE NEIGHBOR STRING EX: Iffat, Iffatt
                    string temp = NamesFromFile[j];
                    NamesFromFile[j] = NamesFromFile[j+1];
                    NamesFromFile[j+1] = temp;
                    break; //we will go the 1st inner loop and leave the 2nd inner loop, moving to the next string as we have just sorted two strings alphabetically.
                }
                else if(NamesFromFile[j][z] == NamesFromFile[j+1][z]){//ELSE IF PURPOSE RIGHT BELOW:
                    continue; //the current character of the current string an the neighbor string are the same, we cant sort, so we move on to the next chars of the current string and current neighbor string
                }
                else{
                    break;
                }
            }
                
        }
    }

    for(int k = 0; k<NamesFromFile.size(); k++){
        cout << NamesFromFile[k] << "\n";
    } 

} 

void Admin::SortByGrade(){
    int NumberFromLine = 0;
    int CurrentLine = 1;
    float PlaceHolder = 0;
    float Counter = 0;
    float GPA = 0;
    bool Proceed = 0;
    int MAX = 0;
    string Text;
    vector<float>GradesFromFile;
    vector<string>NamesFromFile;


    ifstream File("StudentData.txt");

    while(getline(File, Text)){

        //get the words from each line, specifically the student name and upload it to the respective vector;
        if((CurrentLine%2==0)&&(Text!="")){
            NamesFromFile.push_back(Text);
        }
        CurrentLine++;

        //first remove the the commas between the grades if any for each student
        for(char &c: Text){
            if(c == ','){
                c = ' ';
            }
        }

        //get the numbers from each line in the nested while loop. In the def of the nested while loop, make sure to upload the GPA of each student to the respective vector
        istringstream iss(Text);
        while(iss >> NumberFromLine){
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            Proceed = 1;
        }
        if(Proceed == 1){
            GPA = PlaceHolder/Counter;
            //cout << GPA << "\n";
            GradesFromFile.push_back(GPA);
            PlaceHolder = 0;
            Counter = 0;
            Proceed = 0;
            GPA = 0;
        }
    }

    //keep in mind that number of names should be equivalent to the number of GPA's as each student has their own GPA
    if(NamesFromFile.size() == GradesFromFile.size()){
        MAX = NamesFromFile.size();
    }
    //SORT
    for(int i = 0; i<MAX; i++){
        for(int j = 0; j<MAX-1; j++){
            if(GradesFromFile[j]<GradesFromFile[j+1]){
                //swap the grades
                float TempGrade = GradesFromFile[j];
                GradesFromFile[j] = GradesFromFile[j+1];
                GradesFromFile[j+1] = TempGrade;
                //reflect the change on to the respective student name;
                string TempStudentName = NamesFromFile[j];
                NamesFromFile[j] = NamesFromFile[j+1];
                NamesFromFile[j+1] = TempStudentName;
            }
        }
    }

    for(int z = 0; z<MAX; z++){
        cout << "Student Name: "<< NamesFromFile[z] << " GPA: " << GradesFromFile[z] << "\n";
    }
}
//

/*
- If you attempt to read from a file that doesnt exsist there wont be an error but rather the program wont be able to print anything onto the output as there is nothing to read

- When it comes to writing to a file and the file does not exsist, it will create that file and write the specified contents. We use the class ofstream from the lib fstream

- When it comes to writing to a file and the file does exsist, to not overwite the contents in the file we use ios::app and we still use the lib ofstream:
 (FYI $ means user specified! Can be anything)
ofstream $YOUR_OBJECT_NAME_FOR_CLASS_ofstream ("$FILENAME.TXT", ios::app);

(also applies if the file doesnt exsist, it will create it)

- ifstream is a class from the fstream library to read from the text file. Creating an object/instance of the class will have you call the paramtrized constructor which is to open and read from a file
ifstream $YOUR_OBJECT_NAME_FOR_CLASS_ifstream("$FILENAME.TXT");

- istringstream is a a class from the library sstream. We can use the class to break down every word when we read the current line, from the current iteration of the while loop. from a file via the object of the class
istringstram  $YOUR_OBJECT_NAME_FOR_CLASS_istringstream("$VARIABLE_OF_TYPE_STRING")

while($YOUR_OBJECT_NAME_FOR_CLASS_istringstream << $VARAIBELE_OF_NUMERICTYPE){ //this while loop will end once there is a word that is read or there is no remainig words within a line. The variable of type numeric stores the current number from the current line were on 
    def..
    //we can store the numbers from the words we read from the current line
}

while($YOUR_OBJECT_NAME_FOR_CLASS_istringstream << $VARAIBELE_OF_STRINGTYPE){ //this while loop will end once there is a word that is read or there is no remainig words within a line 
    def..
    //we can store the words from the current line were reading 
}

- local variables  are only viewable and accessible within the scope they are declared and intialized.
Once we re-enter the scope of the creation of the local variable, not only will it be re-created per lines
but it will also forget the previous value it once stored

- Within the methods that we define for our classes, when declaring the variables of numerical data types (int & float), we must intialize them to 0 expliclity 
otherwise we risk having garbage values that may potitentally risk in messing up the algorithim in determining the average. 

- size_t $YOUR_OBJECT_NAME_FOR_CLASS_size_t; no passed value for parameter thus we do not call paramtraized constructor

- continue leaves the current iteration of the loop to the next iteration of said loop
- break compleletely leaves the loop 
*/