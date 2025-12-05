#include <stdio.h>

//global variables:
char *Username; //NOTE: The Username for Students == The StudentID for user Students. for users of type Student, make sure there is NOT a duplicate in both Username and StudentID. Admins are added manually on the text file so no worries.
char *Password;
int UserInput; 
char AccessGranted;

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
    void (*GPA)(struct Student*);
} Student;


int main(){

    //c (this is where we match the pointer to the method and the actual method so the compiler knows)
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
        .GPA = GPA,
    };
    
    return 0;
}

//b create the actual method, return type, name of the method (can be anything you want, I'll have it the same as the name of the pointer to said method)
void ClassAverageGPA(Admin *PointerToObject){

}

void LowestGPA(Admin *PointerToObject){

}

void HighestGPA(Admin *PointerToObject){

}

void GradeDistribution(Admin *PointerToObject){

}

void SortByName(Admin *PointerToObject){

}

void SortByGrade(Admin *PointerToOject){

}

void Modify(Admin *PointerToObject){

}

void LoadStudentRecord(Admin *PointerToObject){

}

void AddStudentRecord(Admin *PointerToObject){

}

//--

//b but for the struct Student 
float MyGPA(Student *PointerToObject){

}

void GPA(Student *PointerToObject){

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

(b) 
- Then we define the method (this includes the return type of the method/void, name of the method (naming convention of the pointer doesnt have to be the same name as the pointer to said method but it is allowed!), the parameters, the definition of the method)
(I'll be using the same naming convention between the name of the pointer to the method and name of the method for consistency)

(c)
- Then we match the pointer to the method from the struct to the respective method in (b)

(d)
- We use the method as so: $VARIABLE_OF_TYPE_STRUCT.pointer_to_method_name(parameters);

All of the parts are important but the most important is making sure the parameter of the method at least is a pointer to the variable of type struct
5) user input is also different, we use scanf("%formatspeciferfordatatype", &variable)
*/




