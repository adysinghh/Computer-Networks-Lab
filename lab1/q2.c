#include <stdio.h>
#include <string.h>

struct student_info {
    int id;
    char full_name[50];
    float grade_point_average;
};

void displayInfo(struct student_info *person) {
    printf("ID: %d\n", person->id);
    printf("Full Name: %s\n", person->full_name);
    printf("GPA: %.2f\n", person->grade_point_average);
}

int main() {
    struct student_info person;

    person.id = 456;
    strcpy(person.full_name, "Alice Smith");
    person.grade_point_average = 3.90;

    displayInfo(&person);

    return 0;
}
