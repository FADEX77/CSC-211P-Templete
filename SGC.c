#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of courses and the maximum length of the course name
#define MAX_COURSES 13
#define MAX_NAME_LEN 100
#define MAX_SEMESTERS 14

// Define the datatype of each input
typedef struct {
    char name[MAX_NAME_LEN];
    int units;
    char letter_grade;
    int grade_points;
    int grade; // Changed the data type to int for grades
} Course;

// Function to calculate the GPA for a given number of courses
float calculate_gpa(int num_courses, Course courses[]) {
    int total_course_points = 0;
    int total_course_units = 0;

    for (int i = 0; i < num_courses; i++) {
        int course_points = courses[i].grade_points * courses[i].units;
        total_course_points += course_points;
        total_course_units += courses[i].units;
    }

    // Calculate and return the GPA
    return (float)total_course_points / total_course_units;
}

// Input for the number of semesters and courses
int main() {
    int num_semesters;
    Course courses[MAX_COURSES * 14]; // Assume a maximum of 14 courses per semester
    float semester_gpas[MAX_SEMESTERS]; // Array to store semester GPAs
    int num_courses_entered = 0; // Keep track of the number of courses entered
    int total_course_units = 0; // Keep track of the total course units
    float cumulative_gpa = 0.0; // Initialize cumulative GPA to 0.0

    // Prompt user to enter the number of semesters
    printf("Enter the number of semesters (1-14): ");
    scanf("%d", &num_semesters);

    // Ensure valid input
    while (num_semesters < 1 || num_semesters > 14) {
        printf("Invalid input. Try again: ");
        scanf("%d", &num_semesters);
    }

    // Calculate the GPA for each semester
    for (int semester = 0; semester < num_semesters; semester++) {
        int num_courses;

        // Prompt user to enter the number of courses for this semester
        printf("\nEnter the number of courses for semester %d: ", semester + 1);
        scanf("%d", &num_courses);

        // Ensure valid input
        while (num_courses < 1 || num_courses > MAX_COURSES) {
            printf("Invalid input. Try again: ");
            scanf("%d", &num_courses);
        }

        // Input for the course name, units, and grade
        for (int i = 0; i < num_courses; i++) {
            printf("Enter the name of course %d: ", i + 1);
            getchar(); // Consume the newline character left in the buffer
            fgets(courses[i].name, sizeof(courses[i].name), stdin);
            courses[i].name[strcspn(courses[i].name, "\n")] = '\0'; // Remove the trailing newline

            printf("Enter the units for course %d: ", i + 1);
            scanf("%d", &courses[i].units);

            // Check that the unit is within the valid range
            while (courses[i].units < 1 || courses[i].units > 4) {
                printf("Invalid units. Enter the units for course %d (1-4): ", i + 1);
                scanf("%d", &courses[i].units);
            }

            // Consume the newline character from the input buffer
            while (getchar() != '\n');

            // Input for the course grade
            printf("Enter the grade for course %d (1-100): ", i + 1);
            scanf("%d", &courses[i].grade);

            // Check that the grade is within the valid range
            while (courses[i].grade < 1 || courses[i].grade > 100) {
                printf("Invalid grade. Enter the grade for course %d (1-100): ", i + 1);
                scanf("%d", &courses[i].grade);
            }

            // Determine the letter grade and grade points based on the numeric grade
            if (courses[i].grade >= 90) {
                courses[i].letter_grade = 'A';
                courses[i].grade_points = 5;
            } else if (courses[i].grade >= 80) {
                courses[i].letter_grade = 'B';
                courses[i].grade_points = 4;
            } else if (courses[i].grade >= 70) {
                courses[i].letter_grade = 'C';
                courses[i].grade_points = 3;
            } else if (courses[i].grade >= 60) {
                courses[i].letter_grade = 'D';
                courses[i].grade_points = 2;
            } else {
                courses[i].letter_grade = 'F';
                courses[i].grade_points = 1;
            }

            // Add the course units to the total course units
            total_course_units += courses[i].units;
        }

        // Calculate and output the GPA for this semester
        semester_gpas[semester] = calculate_gpa(num_courses, &courses[num_courses_entered]);
        cumulative_gpa += semester_gpas[semester];
        num_courses_entered += num_courses;

        printf("Semester GPA: %.2f\n", semester_gpas[semester]);
    }

    // Calculate and output the cumulative GPA
    cumulative_gpa /= num_semesters;
    printf("\nCumulative GPA: %.2f\n", cumulative_gpa);

    return 0;
}

// FADEX COPY