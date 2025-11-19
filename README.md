# Student-Grade-Management-System
CSC 3200: Course Project

Each student will develop a Student Grade Management System using the new language they
are learning and a language they are already familiar with: **For me it is C and C++**

**Features and Requirements**

**1) User Authentication and Role Management**
  * The system supports two types of users:
    - Admin: Can add, modify, and delete student records.
    - Student: Can view only their own record.
  * At program start up, users must log in with username and password.
  * A simple authentication system (stored in a file or hardcoded for simplicity).
  * Role-based access control ensures students cannot modify data

**2) Adding Student Records**
  * Admins can enter the number of subjects per studdents.
  * Admins can enter a student's name, ID, and grades for different subjects.
  * Data is stored in a plaint text file for persistence.

**3) Calculating GPA**
  * The system computes GPA using a basic formula: GPA = Sum of Grades/Number of Subjects

**4) Storing and Retrieving Data**
  * Load student records from a text file in the following format: Student ID, name, Grade1, Grade2, Grade3, ...Garde n. Here n is the numnber of subjects fixed by the admin.
  * Store records in a text file. Any changes made by the admin records function will be stored in the file as well.
  * Retrieve and display records when needed.
  * Handle missing files or corrupted data gracefully.

**5) Display Summary Statistics**:
  Admins can:
  * Generate class avg GPA.
  * Highest and lowest GPA.
  * Grade Distribution (how many stidents got an A, B, etc).
  * Sort students by their grade/name.

**6) Retrieving/Modifying Data**
  * Admins can lookup and modify data of one student using student name/student ID. (change a grade from B+ -> A)
  * When a student logs in, they can chek their individual grades and GPA. A student can only view his/her own grade. You can either let the students register with their ID or take that as an input from the CLI once they log in

* This is a command line application, NO GUI NEEDED.
* Both of your apps should implement the above features. They should also handle invalid inputs and exceptions gracefully.
* You should modularize your code as best as you can by using the language specific features (classes/functions/structs etc).
