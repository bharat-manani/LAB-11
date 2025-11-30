#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char studentName[50];
    int rollNumber;
    float subjectMarks[3];
    float totalPercentage;
    char gradeLetter[3];
};

void enterStudentData(struct Student arr[], int total);
void computeResults(struct Student arr[], int total);
void showAllStudents(struct Student arr[], int total);
void searchByGrade(struct Student arr[], int total, char grade[]);
void searchByRoll(struct Student arr[], int total, int roll);
void searchByName(struct Student arr[], int total, char name[]);
void showClassAverage(struct Student arr[], int total);
void rankByPercentage(struct Student arr[], int total);

int main() {
    int numberOfStudents, menuChoice;
    struct Student data[MAX_STUDENTS];

    printf("Enter number of students: ");
    scanf("%d", &numberOfStudents);

    enterStudentData(data, numberOfStudents);
    computeResults(data, numberOfStudents);

    do {
        printf("\n----- MENU -----\n");
        printf("1. Display all students\n");
        printf("2. Search students by grade\n");
        printf("3. Search student by roll number\n");
        printf("4. Search student by name\n");
        printf("5. Class average and above/below average\n");
        printf("6. Display student ranking\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menuChoice);

        if (menuChoice == 1)
            showAllStudents(data, numberOfStudents);

        else if (menuChoice == 2) {
            char gradeSearch[3];
            printf("Enter grade: ");
            scanf("%s", gradeSearch);
            searchByGrade(data, numberOfStudents, gradeSearch);
        }

        else if (menuChoice == 3) {
            int rollSearch;
            printf("Enter roll number: ");
            scanf("%d", &rollSearch);
            searchByRoll(data, numberOfStudents, rollSearch);
        }

        else if (menuChoice == 4) {
            char nameSearch[50];
            printf("Enter name: ");
            scanf("%s", nameSearch);
            searchByName(data, numberOfStudents, nameSearch);
        }

        else if (menuChoice == 5)
            showClassAverage(data, numberOfStudents);

        else if (menuChoice == 6)
            rankByPercentage(data, numberOfStudents);

    } while (menuChoice != 0);

    return 0;
}

void enterStudentData(struct Student arr[], int total) {
	int i, j;
    for ( i = 0; i < total; i++) {
        printf("\nStudent %d\n", i + 1);

        printf("Name: ");
        scanf("%s", arr[i].studentName);

        printf("Roll number: ");
        scanf("%d", &arr[i].rollNumber);

        for ( j = 0; j < 3; j++) {
            do {
                printf("Marks in subject %d (0-100): ", j + 1);
                scanf("%f", &arr[i].subjectMarks[j]);
            } while (arr[i].subjectMarks[j] < 0 || arr[i].subjectMarks[j] > 100);
        }
    }
}

void computeResults(struct Student arr[], int total) {
		int i, j;
    for ( i = 0; i < total; i++) {
        float sumMarks = arr[i].subjectMarks[0] +
                         arr[i].subjectMarks[1] +
                         arr[i].subjectMarks[2];

        arr[i].totalPercentage = sumMarks / 3;

        float p = arr[i].totalPercentage;

        if (p >= 90) strcpy(arr[i].gradeLetter, "A+");
        else if (p >= 80) strcpy(arr[i].gradeLetter, "A");
        else if (p >= 70) strcpy(arr[i].gradeLetter, "B+");
        else if (p >= 60) strcpy(arr[i].gradeLetter, "B");
        else if (p >= 50) strcpy(arr[i].gradeLetter, "C");
        else strcpy(arr[i].gradeLetter, "F");
    }
}

void showAllStudents(struct Student arr[], int total) {
    printf("\n%-12s %-10s %-10s %-10s %-10s %-12s %-8s\n",
           "Name", "Roll", "M1", "M2", "M3", "Percent", "Grade");
	int i, j;
    for (i = 0; i < total; i++) {
        printf("%-12s %-10d %-10.1f %-10.1f %-10.1f %-12.2f %-8s\n",
               arr[i].studentName,
               arr[i].rollNumber,
               arr[i].subjectMarks[0],
               arr[i].subjectMarks[1],
               arr[i].subjectMarks[2],
               arr[i].totalPercentage,
               arr[i].gradeLetter);
    }
}

void searchByGrade(struct Student arr[], int total, char grade[]) {
    int found = 0;
	int i, j;
    for ( i = 0; i < total; i++) {
        if (strcmp(arr[i].gradeLetter, grade) == 0) {
            printf("%s (Roll %d) - %.2f%%\n",
                   arr[i].studentName,
                   arr[i].rollNumber,
                   arr[i].totalPercentage);
            found = 1;
        }
    }

    if (!found) printf("No student found with grade %s\n", grade);
}
	int i, j;
void searchByRoll(struct Student arr[], int total, int roll) {
    for ( i = 0; i < total; i++) {
        if (arr[i].rollNumber == roll) {
            printf("%s - %.2f%% Grade: %s\n",
                   arr[i].studentName,
                   arr[i].totalPercentage,
                   arr[i].gradeLetter);
            return;
        }
    }

    printf("No student found with roll number %d\n", roll);
}

void searchByName(struct Student arr[], int total, char name[]) {
    for ( i = 0; i < total; i++) {
        if (strcmp(arr[i].studentName, name) == 0) {
            printf("Roll %d | %.2f%% | Grade %s\n",
                   arr[i].rollNumber,
                   arr[i].totalPercentage,
                   arr[i].gradeLetter);
            return;
        }
    }

    printf("No student found with name %s\n", name);
}

void showClassAverage(struct Student arr[], int total) {
    float totalPercentSum = 0;
	int i, j;
    for ( i = 0; i < total; i++)
        totalPercentSum += arr[i].totalPercentage;

    float averagePercent = totalPercentSum / total;

    printf("\nClass Average: %.2f%%\n", averagePercent);

    printf("\nAbove Average:\n");
    for (i = 0; i < total; i++)
        if (arr[i].totalPercentage > averagePercent)
            printf("%s (%.2f%%)\n", arr[i].studentName, arr[i].totalPercentage);

    printf("\nBelow Average:\n");
    for ( i = 0; i < total; i++)
        if (arr[i].totalPercentage < averagePercent)
            printf("%s (%.2f%%)\n", arr[i].studentName, arr[i].totalPercentage);
}

void rankByPercentage(struct Student arr[], int total) {
		int i, j;
    for ( i = 0; i < total - 1; i++) {
        for (j = 0; j < total - i - 1; j++) {
            if (arr[j].totalPercentage < arr[j + 1].totalPercentage) {
                struct Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\nStudent Ranking:\n");
    for (i = 0; i < total; i++) {
        printf("Rank %d: %s (%.2f%%)\n",
               i + 1,
               arr[i].studentName,
               arr[i].totalPercentage);
    }
}

