#include <stdio.h>
#include <string.h>

// Defining the dob structure
struct dob {
    int day;
    int month;
    int year;
};

// Defining the structure of Student
struct Student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

// Function to print student (call by value)
void print_Student_info_by_value(struct Student_info Student) {
    printf("Call-By Value \n");
    printf("Roll No : %d \n", Student.roll_no);
    printf("Name : %s \n", Student.name);
    printf("CGPA : %.2f \n", Student.CGPA);
    printf("DOB : %02d-%02d-%04d \n", Student.age.day, Student.age.month, Student.age.year);
}

// Function to print student (call by address)
void print_Student_info_by_address(struct Student_info *Student) {
    printf("Call-By Address \n");
    printf("Roll No : %d \n", Student->roll_no);
    printf("Name : %s \n", Student->name);
    printf("CGPA : %.2f \n", Student->CGPA);
    printf("DOB : %02d-%02d-%04d \n", Student->age.day, Student->age.month, Student->age.year);
}

int main() {
    struct Student_info Student;

    Student.roll_no = 101;
    strcpy(Student.name, "MD ALam");
    Student.CGPA = 8.75;
    Student.age.day = 15;
    Student.age.month = 11;
    Student.age.year = 2003;

    // Printing student info by call by value
    print_Student_info_by_value(Student);
    printf("\n");

    // Printing student info by call by address
    print_Student_info_by_address(&Student);

    return 0;
}
