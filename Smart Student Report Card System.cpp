
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Student
{
    string name;
    int rollNo;
    int marks[5];
    int total;
    float percentage;
    char grade;
};

string subjects[5] =
{
    "Programming Fundamentals",
    "ICT",
    "English",
    "Calculus",
    "Physics"
};

char gradeCalculation(float percentage)
{
    if (percentage >= 90)
        return 'A';
    else if (percentage >= 80)
        return 'B';
    else if (percentage >= 70)
        return 'C';
    else if (percentage >= 60)
        return 'D';
    else
        return 'F';
}

bool isRollNoUnique(Student students[], int count, int rollNo)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            return false;
        }
    }

    return true;
}

// Add a new student
void addStudent(Student students[], int& count)
{
    if (count >= 100)
    {
        cout << "\nStudent limit reached!\n";
        return;
    }

    Student s;

    cout << "\n==============================================\n";
    cout << "                ADD STUDENT                   \n";
    cout << "==============================================\n";

    cout << "Enter student name: ";
    getline(cin, s.name);

    // Roll number validation
    while (true)
    {
        cout << "Enter roll number: ";
        cin >> s.rollNo;

        if (!isRollNoUnique(students, count, s.rollNo))
        {
            cout << "\n*** ERROR: Roll Number " << s.rollNo
                << " already exists! ***\n";
            cout << "Please enter a unique roll number.\n\n";
        }
        else
        {
            break;
        }
    }

    s.total = 0;

    cout << "\nEnter marks of 5 subjects:\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            cout << subjects[i] << ": ";
            cin >> s.marks[i];

            if (s.marks[i] >= 0 && s.marks[i] <= 100)
            {
                break;
            }

            cout << "Invalid marks! Enter marks between 0 and 100.\n";
        }

        s.total += s.marks[i];
    }

    s.percentage = (s.total / 500.0) * 100;
    s.grade = gradeCalculation(s.percentage);

    students[count] = s;
    count++;

    cout << "\n*** Student record added successfully! ***\n";

    cin.ignore();
}

// Display one student's report
void displayReport(Student s)
{
    cout << "\n";
    cout << "==============================================\n";
    cout << "              STUDENT REPORT CARD             \n";
    cout << "==============================================\n";

    cout << left << setw(20) << "Name"
        << ": " << s.name << endl;

    cout << left << setw(20) << "Roll Number"
        << ": " << s.rollNo << endl;

    cout << "----------------------------------------------\n";

    cout << left << setw(27) << "Subject"
        << right << setw(8) << "Marks" << endl;

    cout << "----------------------------------------------\n";

    for (int i = 0; i < 5; i++)
    {
        cout << left << setw(27) << subjects[i]
            << right << setw(8) << s.marks[i] << endl;
    }

    cout << "----------------------------------------------\n";

    cout << left << setw(20) << "Total Marks"
        << ": " << s.total << " / 500" << endl;

    cout << left << setw(20) << "Percentage"
        << ": " << fixed << setprecision(2)
        << s.percentage << "%" << endl;

    cout << left << setw(20) << "Grade"
        << ": " << s.grade << endl;

    cout << "==============================================\n";
}

// View all students
void viewAllStudents(Student students[], int count)
{
    if (count == 0)
    {
        cout << "\nNo student records available.\n";
        return;
    }

    cout << "\n";
    cout << "===============================================================\n";
    cout << "                     ALL STUDENTS                              \n";
    cout << "===============================================================\n";

    cout << left
        << setw(20) << "Name"
        << setw(12) << "Roll No"
        << setw(12) << "Total"
        << setw(15) << "Percentage"
        << setw(8) << "Grade" << endl;

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << left
            << setw(20) << students[i].name
            << setw(12) << students[i].rollNo
            << setw(12) << students[i].total
            << setw(15) << fixed << setprecision(2)
            << students[i].percentage
            << setw(8) << students[i].grade << endl;
    }

    cout << "===============================================================\n";
}

// Search student by roll number
void searchStudent(Student students[], int count)
{
    if (count == 0)
    {
        cout << "\nNo student records available.\n";
        return;
    }

    int rollNo;

    cout << "\nEnter roll number to search: ";
    cin >> rollNo;

    for (int i = 0; i < count; i++)
    {
        if (students[i].rollNo == rollNo)
        {
            displayReport(students[i]);
            return;
        }
    }

    cout << "\n*** Student with Roll Number "
        << rollNo << " not found! ***\n";
}

// Save report to file
void saveToFile(Student students[], int count)
{
    ofstream file("StudentReport.txt");

    if (!file)
    {
        cout << "\nError opening file!\n";
        return;
    }

    file << "===============================================================\n";
    file << "              STUDENT REPORT CARD SYSTEM                       \n";
    file << "===============================================================\n\n";

    for (int i = 0; i < count; i++)
    {
        file << "---------------------------------------------------------------\n";
        file << "Name       : " << students[i].name << endl;
        file << "Roll Number: " << students[i].rollNo << endl;

        file << "Marks:\n";

        for (int j = 0; j < 5; j++)
        {
            file << subjects[j] << " : "
                << students[i].marks[j] << endl;
        }

        file << "Total      : " << students[i].total << " / 500" << endl;
        file << "Percentage : " << fixed << setprecision(2)
            << students[i].percentage << "%" << endl;
        file << "Grade      : " << students[i].grade << endl;
        file << "---------------------------------------------------------------\n\n";
    }

    file.close();

    cout << "\n*** Records saved successfully to StudentReport.txt ***\n";
}

// Main menu
void displayMenu()
{
    cout << "\n";
    cout << "==============================================\n";
    cout << "       STUDENT REPORT CARD MANAGEMENT         \n";
    cout << "==============================================\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student by Roll Number\n";
    cout << "4. Save Records to File\n";
    cout << "5. Exit\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    Student students[100];
    int studentCount = 0;
    int choice;

    cout << "\n==============================================\n";
    cout << "       WELCOME TO REPORT CARD SYSTEM         \n";
    cout << "==============================================\n";

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            addStudent(students, studentCount);
            break;

        case 2:
            viewAllStudents(students, studentCount);
            break;

        case 3:
            searchStudent(students, studentCount);
            break;

        case 4:
            saveToFile(students, studentCount);
            break;

        case 5:
            saveToFile(students, studentCount);

            cout << "\n==============================================\n";
            cout << "   THANK YOU FOR USING THE SYSTEM!            \n";
            cout << "==============================================\n";
            break;

        default:
            cout << "\n*** Invalid choice! Please select 1-5. ***\n";
        }

    } while (choice != 5);

    return 0;
}