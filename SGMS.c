#include <stdio.h> //standard I/O library. Needed for almost all c programs 
#include <string.h>

//global variables & methods:
char *Username; //NOTE: The Username for Students == The StudentID for user Students. for users of type Student, make sure there is NOT a duplicate in both Username and StudentID. Admins are added manually on the text file so no worries.
char *Password;
int UserInput; 
char AccessGranted;

void Append(); //Inorder to register new students, we must add them into our databases (the two .txt files, the for the student info database by default the grades will be zero)
char* LogIn(); //This method verifies that the user exsists and is valid by reading the data from the text file and comparing it to the user input of the global variables, Username and Password

typedef struct {
    void *Element; //pointer to our chosen datatype value
    size_t ElementSize; //size_t is an unsigned integer data type that tells us the size of the actual element it holds in memory. The format specifier for unsigned integer is %zu
    size_t Size;  //Size will be used to determine the number of elements in the vector
    size_t Capacity; 
    void (*Vector_Init)(struct Vector*, size_t); 
    /*
    - the intialize function is kinda like a constructor in the sense that it initalizes the values of the data members. The 
    second parameter takes an argument for the variable ElementSize. We use sizeof specificallyh element size to determine 
    the amount of bytes for the passed data type. You'll see that whenever we call this method via the pointer, we always do sizeof(datatype),
    this is what is essentially the number of bytes which further indicates the data type we will expect for the elements in the vector.
    */
    void (*Vector_Resize)(struct Vector*, size_t);
    void (*Vector_Push_Back)(struct Vector*, void*);
    void* (*Vector_Get)(struct Vector*, size_t);
} Vector;

//b for Vector struct 
                              //sizeof(respecitive data type)
void Vector_Init(Vector *PTO, size_t ElementSize){
    PTO->Size = 0;
    PTO->Capacity = 4; //by default 4 is the raw # of bytes
    PTO->ElementSize = ElementSize;
    PTO->Element = malloc(PTO->Capacity * ElementSize);
}
                                //sizeof(respective data type)
void Vector_Resize(Vector *PTO, size_t Capacity){
    PTO->Capacity = Capacity;
    PTO->Element = realloc(PTO->Element, PTO->Capacity * PTO->ElementSize);
}
                                    //&(respective data type)
void Vector_Push_Back(Vector* PTO, void *Element){
    if(PTO->Size == PTO->Capacity){
        Vector_Resize(PTO, PTO->Capacity * 2);
    }

    void *Slate = (char*)PTO + PTO->Size * PTO->ElementSize;
    memcpy(Slate, Element, PTO->ElementSize);

    PTO->Size++;
}

void* Vector_Get(Vector *PTO, size_t Index){
    return (char*)PTO->Element + Index * PTO->ElementSize;
}
//c for the vector struct
Vector RegVecObject = {
    .Vector_Init = Vector_Init,
    .Vector_Resize = Vector_Resize,
    .Vector_Push_Back = Vector_Push_Back,
    .Vector_Get = Vector_Get,
};

//--

typedef struct {
    //a for Admin (pointer to the method, the below is not the name of the method!)
    float (*ClassAverageGPA)(struct Admin*); //method return type,  Name of the pointer to the method (which will be used as the name of the method in main()), paremeter requires pointer to variable of that struct type and what you see fit
    void (*LowestGPA)(struct Admin*);
    void (*HighestGPA)(struct Admin*);
    void (*GradeDistribution)(struct Admin*);
    void (*SortByName)(struct Admin*);
    void (*SortByGrade)(struct Admin*);
    void (*Modify)(struct Admin*);
    void (*LoadStudentRecord)(struct Admin*);
    void (*AddStudentRecord)(struct Admin*);
} Admin;

//----

typedef struct {
    //a but for the struct Student 
    float (*MyGPA)(struct Student*);
    void (*Grades)(struct Student*);
} Student;


int main(){
    //c this is where we match (the pointer to the method) and the (corresponding created method) so the compiler knows
    Admin RegAdminObject = {
        .ClassAverageGPA = ClassAverageGPA,
        .LowestGPA = LowestGPA,
        .HighestGPA = HighestGPA,
        .GradeDistribution = GradeDistribution,
        .SortByName = SortByName,
        .SortByGrade = SortByGrade,
        .LoadStudentRecord = LoadStudentRecord,
        .AddStudentRecord = AddStudentRecord,
    };

    //c but for the struct Student 
    Student RegStudentObject = {
        .MyGPA = MyGPA,
        .Grades = Grades,
    };

    while((AccessGranted != 'Y') && (AccessGranted != 'N')){
        printf("Hello! Are you a new Student? {Y/N}?: ");
        scanf("%c", AccessGranted);
    }

    if(AccessGranted == 'Y'){
        Append();
    }

    printf("Welcome, would you like to log in {Y/N}?: ");
    scanf("%c", AccessGranted);

    if(AccessGranted == 'N'){
        return 1;
    }

    printf("Username: ");
    scanf("%s", Username);
    printf("Password: ");
    scanf("%s", Password);

    char *UserType = LogIn();
    if(UserType == "Student"){
        printf("You are a Student, welcome back user %s \n", Username);
        
        do
        {
            if(UserInput == 1){
                AccessGranted = ' ';
                main();
                break;
            }

            else if(UserInput == 2){
                printf("%s GPA: %s \n", Username, RegStudentObject.MyGPA(&RegStudentObject));
            }

            else if(UserInput == 3){
                RegStudentObject.Grades(&RegStudentObject);

            }
            else{
                printf("Bad Input, you must do an actual input from the list \n");
            }
            
        } while ((AccessGranted!='N') && (UserType == "Student"));      
    }

    else if(UserType == "Admin"){
        printf("You are a Admin. Welcome back user %s \n", Username);

        do
        {
            printf("1. Logout \n ");
            printf("2. Add a Student Record \n");
            printf("3. Retrieve The Class Average \n");
            printf("4. Retrieve the highest GPA in the class \n");
            printf("5. Retrieve the lowest GPA in the class \n");
            printf("6. Retrieve Student Record \n");
            printf("7. Retrieve Grade Distribution \n");
            printf("8. Sort Students by Names \n");
            printf("9. Sort Students by Grades \n");
            printf("Enter: ");
            scanf("%d", UserInput);
        } while ((AccessGranted!='N') && (UserType == "Admin"));
        
    }

    else{
        printf("User doesn't exsist or account creds are incorrect \n");
        AccessGranted = ' ';
        main();
    }

    
    return 0;
}

void Append(){
    //
}

char* LogIn(){ 
    //
}

//b create the actual method, return type, name of the method (can be anything you want, I'll have it the same as the name of the pointer to said method)
void ClassAverageGPA(Admin *PointerToObject){ 
    float GPA = 0;
    float PlaceHolder = 0;
    float NumberFromLine = 0;
    char Text[256];
    int Counter = 0;
    //create a local variable of type vector struct (to prevent from recalling previous values of using the global)
    Vector ISV = RegVecObject;
    ISV.Vector_Init(&ISV, sizeof(float)); 
    //Open the file
    FILE *ptr = fopen("StudentData.txt", "r");

    //we will use fgets wihtin the outer while loop to to read the file line by line - getline
    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //sscanf allows us parse or extract certain bits of data or a substring from the total string. s
            /*
            - sscanf returns one number, that number is the amount of values it parsed or took as input. This should typically be 1 as we want each iteration to be each number on the current line
            - Thus, as long as it return 1, that means we have successfully read one number from possiblt multiple numbers on the current line via the outer while loop. The moment ir returns 0, this 
            means there are no more numbers to read and so we break from the inner while loop and continue with the rest of the lines of code (definition) of the outer while loop if any at all. From there
            we move on to the next line per condition of the outer while loop. 
            */
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }
        GPA = PlaceHolder/Counter;
        ISV.Vector_Push_Back(&ISV, &GPA);
        PlaceHolder = 0;
        Counter = 0;
    }
    PlaceHolder = 0;
    for(int i = 0; i<ISV.Size; i++){
        PlaceHolder = PlaceHolder + *(float*)ISV.Vector_Get(&ISV, i);
    }
    GPA = PlaceHolder/ISV.Size;

    fclose(ptr);

    printf("The class average GPA is: %f\n", GPA);

}

void LowestGPA(Admin *PointerToObject){
    float GPA = 0;
    float PlaceHolder = 0;
    float NumberFromLine = 0;
    char Text[256];
    int Counter = 0;
    //create a local variable of type vector struct (to prevent from recalling previous values of using the global)
    Vector ISV = RegVecObject;
    ISV.Vector_Init(&ISV, sizeof(float)); 
    //Open the file
    FILE *ptr = fopen("StudentData.txt", "r");

    //we will use fgets wihtin the outer while loop to to read the file line by line - getline
    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //sscanf allows us parse or extract certain bits of data or a substring from the total string
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }
        GPA = PlaceHolder/Counter;
        ISV.Vector_Push_Back(&ISV, &GPA);
        PlaceHolder = 0;
        Counter = 0;
    }
    GPA = *(float*)ISV.Vector_Get(&ISV, 0);
    for(int i = 0; i<ISV.Size; i++){
        if(GPA > *(float*)ISV.Vector_Get(&ISV, i)){
            GPA = *(float*)ISV.Vector_Get(&ISV, i);
        }
    }

    fclose(ptr);

    printf("The lowest GPA in the class is: %f\n", GPA);
}

void HighestGPA(Admin *PointerToObject){
    float GPA = 0;
    float PlaceHolder = 0;
    float NumberFromLine = 0;
    char Text[256];
    int Counter = 0;
    //create a local variable of type vector struct (to prevent from recalling previous values of using the global)
    Vector ISV = RegVecObject;
    ISV.Vector_Init(&ISV, sizeof(float)); 
    //Open the file
    FILE *ptr = fopen("StudentData.txt", "r");

    //we will use fgets wihtin the outer while loop to to read the file line by line - getline
    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //sscanf allows us parse or extract certain bits of data or a substring from the total string
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }
        GPA = PlaceHolder/Counter;
        ISV.Vector_Push_Back(&ISV, &GPA);
        PlaceHolder = 0;
        Counter = 0;
    }
    GPA = *(float*)ISV.Vector_Get(&ISV, 0);
    for(int i = 0; i<ISV.Size; i++){
        if(GPA < *(float*)ISV.Vector_Get(&ISV, i)){
            GPA = *(float*)ISV.Vector_Get(&ISV, i);
        }
    }

    fclose(ptr);

    printf("The Highest GPA in the class is: %f\n", GPA);
}

void GradeDistribution(Admin *PointerToObject){
    float GPA = 0;
    float PlaceHolder = 0;
    float NumberFromLine = 0;
    char Text[256];
    int Counter = 0;
    int GD[9] = {0,0,0,0,0,0,0,0,0};
    //create a local variable of type vector struct (to prevent from recalling previous values of using the global)
    Vector ISV = RegVecObject; 
    ISV.Vector_Init(&ISV, sizeof(float)); 
    //Open the file
    FILE *ptr = fopen("StudentData.txt", "r");

    //we will use fgets wihtin the outer while loop to to read the file line by line - getline
    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //sscanf allows us parse or extract certain bits of data or a substring from the total string
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }
        GPA = PlaceHolder/Counter;
        ISV.Vector_Push_Back(&ISV, &GPA);
        PlaceHolder = 0;
        Counter = 0;
    }
    for(int i = 0; i<ISV.Size; i++){
        GPA = *(float*)ISV.Vector_Get(&ISV, i); //initailze GPA with the current value 

        if((GPA>=95) && (GPA<=100)){
            GD[0]++; //A
        }
        else if((GPA>=90) && (GPA<95)){
            GD[1]++; //A-
        }
        else if((GPA>=85) && (GPA<90)){
            GD[2]++; //B+
        }
        
        else if((GPA>=80) && (GPA<85)){
            GD[3]++; //B
        }

        else if((GPA>=75) && (GPA<80)){
            GD[4]++; //B-
        }

        else if((GPA>=70) && (GPA<75)){
            GD[5]++; //C+
        }

        else if((GPA>=65) && (GPA<70)){
            GD[6]++; //C
        }

        else if((GPA>=60) && (GPA<65)){
            GD[7]++; //C-
        }

        else{
            GD[8]++; //F
        }
        
    }

    for(int i = 0; i<9; i++){
        printf("This many students got an A: %f\n", GD[0]);
        printf("This many students got an A-: %f\n", GD[1]);
        printf("This many students got an B+: %f\n", GD[2]);
        printf("This many students got an B: %f\n", GD[3]);
        printf("This many students got an B-: %f\n", GD[4]);
        printf("This many students got an C+: %f\n", GD[5]);
        printf("This many students got an C: %f\n", GD[6]);
        printf("This many students got an C-: %f\n", GD[7]);
        printf("This many students got an F: %f\n", GD[8]);
    }

    fclose(ptr);
    
}

void SortByName(Admin *PointerToObject){ //display the names of the students in alphabetical order
    char Text[256];
    float NumberFromLine = 0;
    float GPA = 0;
    float PlaceHolder = 0;
    int Counter = 0;
    int CurrentLine = 0;
    Vector ISVNames = RegVecObject; 
    Vector ISVGrades = RegVecObject; //remeber in order to be a value in this Vector, it has to be the GPA of students grade, not each of their individual grades 
    ISVNames.Vector_Init(&ISVNames, sizeof(Text));
    ISVGrades.Vector_Init(&ISVGrades, sizeof(float));

    FILE *ptr = fopen("student.txt", "r");

    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        if((CurrentLine%2!=0) && (Text!=' ')){ //this will push the names into the vector ISVNames
            ISVNames.Vector_Push_Back(&ISVNames, &Text);
        }

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //remeber, we break from this while loop when there are no more numbers to read thus returning 0 to again brea the loop
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }

        GPA = PlaceHolder/Counter;
        ISVGrades.Vector_Push_Back(&ISVGrades, &GPA); //this will push the grades into the vector ISVGrades
        GPA = 0;
        PlaceHolder = 0;
        Counter = 0;
    }

    

    //now we will create an array for each vector, traverse through each vector and intialize the respective array
    //1.Names
    int Val = ISVNames.Size; 
    //char *NamesArray[val]; in this version of compiler for c, we are unable to represent the length of the array via variable of type int, we must use a constant numerical value thats why it doesnt work
    char **NamesArray = malloc(Val * sizeof(char*)); //double astrick for just pointer to char (remember in c strings dont exsist!)
    for(int a = 0; a<Val; a++){
        NamesArray[a] = *(char**)ISVNames.Vector_Get(&ISVNames, a);
    }

    //2.Grades
    int Val2 = ISVGrades.Size;
    float *GradesArray = malloc(Val2 * sizeof(char*)); //no need for double astrick for float data type unless you want to create a pointer to a float
    for(int b = 0; b<Val2; b++){
        GradesArray[b] = *(float*)ISVGrades.Vector_Get(&ISVNames, b);

    }

    for(int i = 0; i<ISVGrades.Size; i++){
        for(int j = 0; j<ISVGrades.Size-1; j++){
            int StringLength = 0;
            if(strlen(ISVNames.Vector_Get(&ISVNames, i)) < strlen(ISVNames.Vector_Get(&ISVNames, i+1))){
                StringLength = ISVNames.Vector_Get(&ISVNames, i);
            }
            else{
                StringLength = ISVNames.Vector_Get(&ISVNames, i+1);
            }
            for(int z = 0; z<StringLength; z++){
                if(NamesArray[j][z] > NamesArray[j+1][z]){
                    char *temp =  NamesArray[j];
                    NamesArray[j] = NamesArray[j+1];
                    NamesArray[j+1] = temp;

                    //reflect those changes in the grades as well
                    float temp2 = GradesArray[j];
                    GradesArray[j] = GradesArray[j+1];
                    GradesArray[j+1] = temp2;
                    continue;
                }
                else if(NamesArray[j][z] == NamesArray[j+1][z]){
                    continue;
                }
                else{
                    continue;
                }
            }
        }
    }

        //Again, the size for both arrays should be equivalent as the number of students == number of GPA's. 
    for(int m = 0; m<Val; m++){
        printf("%s - %f\n", NamesArray[m], GradesArray[m]);
    }
}


void SortByGrade(Admin *PointerToOject){
    char Text[256];
    float NumberFromLine = 0;
    float GPA = 0;
    float PlaceHolder = 0;
    int Counter = 0;
    int CurrentLine = 0;
    Vector ISVNames = RegVecObject; 
    Vector ISVGrades = RegVecObject; //remeber in order to be a value in this Vector, it has to be the GPA of students grade, not each of their individual grades 
    ISVNames.Vector_Init(&ISVNames, sizeof(Text));
    ISVGrades.Vector_Init(&ISVGrades, sizeof(float));

    FILE *ptr = fopen("student.txt", "r");

    while(fgets(Text, sizeof(Text), ptr)){
        char *Copy = Text;

        if((CurrentLine%2!=0) && (Text!=' ')){ //this will push the names into the vector ISVNames
            ISVNames.Vector_Push_Back(&ISVNames, &Text);
        }

        while(sscanf(Copy, "%f", &NumberFromLine) == 1){ //remeber, we break from this while loop when there are no more numbers to read thus returning 0 to again brea the loop
            PlaceHolder = PlaceHolder + NumberFromLine;
            Counter++;
            //we need to move the cursor from one number to the next without acknowledging the commas if any
            while(*Copy && *Copy != ',' && *Copy != ' ' && *Copy != '\n'){
                Copy++;
            }
            while(*Copy == ',' || *Copy == ' '){
                Copy++;
            }
        }

        GPA = PlaceHolder/Counter;
        ISVGrades.Vector_Push_Back(&ISVGrades, &GPA); //this will push the grades into the vector ISVGrades
        GPA = 0;
        PlaceHolder = 0;
        Counter = 0;
    }

    

    //now we will create an array for each vector, traverse through each vector and intialize the respective array
    //1.Names
    int Val = ISVNames.Size; 
    //char *NamesArray[val]; in this version of compiler for c, we are unable to represent the length of the array via variable of type int, we must use a constant numerical value thats why it doesnt work
    char **NamesArray = malloc(Val * sizeof(char*)); //double astrick for just pointer to char (remember in c strings dont exsist!)
    for(int a = 0; a<Val; a++){
        NamesArray[a] = *(char**)ISVNames.Vector_Get(&ISVNames, a);
    }

    //2.Grades
    int Val2 = ISVGrades.Size;
    float *GradesArray = malloc(Val2 * sizeof(char*)); //no need for double astrick for float data type unless you want to create a pointer to a float
    for(int b = 0; b<Val2; b++){
        GradesArray[b] = *(float*)ISVGrades.Vector_Get(&ISVNames, b);

    }

    for(int i = 0; i<ISVGrades.Size; i++){
        for(int j = 0; j<ISVGrades.Size-1; j++){
            if(GradesArray[j]<GradesArray[j+1]){
                float temp = GradesArray[j];
                GradesArray[j] = GradesArray[j+1];
                GradesArray[j+1] = temp;
                //reflect those changes in the names array
                char *temp2 = NamesArray[j];
                NamesArray[j] = NamesArray[j+1];
                NamesArray[j+1] = temp2;
            }
        }
    }

    //Again, the size for both arrays should be equivalent as the number of students == number of GPA's. 
    for(int m = 0; m<Val; m++){
        printf("%s - %f\n", NamesArray[m], GradesArray[m]);
    }

}

void Modify(Admin *PointerToObject){

}

void LoadStudentRecord(Admin *PointerToObject){
    char Text[256];

    FILE *ptr = fopen("StudentData.txt", "r");

    while(fgets(Text, sizeof(Text),ptr) != NULL){ //this allows us to read the file line by line. So each iteraion represents the current line. 1st iteration == 1st line etc. We won't move on to the next iteration until 
        printf("%s", Text);
    }

    fclose(ptr);
}

void AddStudentRecord(Admin *PointerToObject){

}

//--

//b but for the struct Student 
float MyGPA(Student *PointerToObject){

}

void Grades(Student *PointerToObject){

}





/*

This Student Grade Management System is created in C. Here are the difference in comparison cpp

1)  Predefined libraries are .h

2) There is no cout, you need to use printf. There are also format specificers to print 

3) strings are not a datatype in c, instead they're an array of type char.
To declare an array of type char without a known size as determined by user input we use pointers. 
This is the only we to determine the size during runtime. 

3) The programming language c does not support OOP principales like C++ does, but we can mimick it

4) classes are a concept of oop, becuase c does not support this we can mimick it via structs

4.2) How do we create methods inside of the struct in c?: 

THIS METHOD CAUSES YOU TO HAVE MORE LINES OF CODE BUT WITH THE PROFIT OF ILLUSTRATING THAT SAID METHOD BELONGS TO THE STRUCT
(a)
- We use pointers. Keep in mind that pointers themselevs arent a oop concept but we can use them to be
- Structs must only store data members, therefore we cant store the name of the method inside a  struct directly the way we would with classes in c++.
Thus, we create a pointer to the desried method and the parameter of said method needs to have the memory of the object of the struct or the variable of that struct type (pointer to that struct)
- in c, you can have x amount of methods with the same parameter and return type but they must have a different name
- The name for the pointer to a method for a struct must be unqiue, no duplicates 
- Again, in the struct, these are pointers to the method, not the method itself. 

(b) 
- Then we define the method (this includes the return type of the method/void, name of the method (naming convention of the pointer doesnt have to be the same name as the pointer to said method but it is allowed!), the parameters, the definition of the method)
(I'll be using the same naming convention between the name of the pointer to the method and name of the method for consistency)

(c)
- Then we match the pointer to the method from the struct to the respective method in (b)

(d)
- We use the method as so: $VARIABLE_OF_TYPE_STRUCT.pointer_to_method_name(parameters);

All of the parts are important but the most important is making sure the parameter of the method at least is a pointer to the variable of type struct
5) user input is also different, we use scanf("%formatspeciferfordatatype", &variable)

6) Vectors are a form of a dynamic array that can change their size during the run time.
Unfortunately, vectors do not exsist in C. The alternative is to create our own struct, 
we manullay use malloc and realloc to give the first inital size of memory and to resize the memory
for dynamic memory (change size during run time) or we can create our own struct that uses pointers to
achieve dynamic memory 

7) UserInput is scanf and has a special keyword that differs from cpp for handling whitespace

8) in c++, when using the keywords (objects for the classes) for reading and writing to a file, we were simulatenosuly opening the file. However, in c, for both cases, we must manullay open the file 

9) In c, you canmnot use a variable of type int to represent the length of an array in some versions of the compiler and instead must an numerical constant

in C, the file handling (which is the process of creating, opening, reading, wiriting, and closing to a file) comes from the struct FILE that is already defined and has the respective methods for each file handling 
from the lib stlib.h
*/




