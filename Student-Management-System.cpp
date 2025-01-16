#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <conio.h> // For _getch() on Windows
#include <cstdlib> // For system("cls") on Windows
using namespace std;

// Global maps to store login credentials
unordered_map<string, string> adminLogin;
unordered_map<string, string> teacherLogin;
unordered_map<string, string> studentLogin;

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Unix
#endif
}

// Function to handle password input with asterisks
string getPassword() {
    string password;
    char ch;
    cout << "Enter your password: ";
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                cout << "\b \b"; // Erase the last asterisk
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*'; // Display asterisk
        }
    }
    cout << endl; // Move to the next line
    return password;
}

// Function for user login
bool login(const string& role) {
    string username, password;

    cout << "Enter username for " << role << ": ";
    cin >> username;

    // Check if the username exists in the respective map
    if ((role == "Admin" && adminLogin.find(username) == adminLogin.end()) ||
        (role == "Teacher" && teacherLogin.find(username) == teacherLogin.end()) ||
        (role == "Student" && studentLogin.find(username) == studentLogin.end())) {
        cout << "No account found for this username. Please set a new password.\n";
        cout << "Set your password: ";
        password = getPassword(); // Use the new password function

        // Save the username and password in the respective map
        if (role == "Admin") adminLogin[username] = password;
        else if (role == "Teacher") teacherLogin[username] = password;
        else if (role == "Student") studentLogin[username] = password;

        cout << "Account created successfully!\n";
        return true;
    }

    // Existing user: Verify credentials
    password = getPassword(); // Use the new password function

    if ((role == "Admin" && adminLogin[username] == password) ||
        (role == "Teacher" && teacherLogin[username] == password) ||
        (role == "Student" && studentLogin[username] == password)) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Incorrect credentials. Please try again.\n";
        return false;
    }
}

// Student structure with a linked list approach
struct Student {
    string name;
    string fatherName;
    int rollNo;
    map<string, string> grades;  // Map for grades (subject -> grade)
    map<string, bool> attendance; // Map for attendance (subject -> attendance)
};

struct StudentNode {
    Student student;
    StudentNode* next; // Pointer to the next student node
};

// Course structure
struct Course {
    string courseName;
    vector<string> subjects;          // List of subjects
    vector<string> teachers;          // List of teachers
    vector<string> times;             // Timetable
};

// Admin class
class Admin {
private:
    unordered_map<string, string> subjectTeachers; // Subject -> Teacher
    string adminPassword;

public:
    StudentNode* studentHead; // Linked list to manage students
    vector<Course> courses;   // Vector to store courses

    // Admin constructor
    Admin() : studentHead(nullptr) {
        // Predefined student data (roll numbers and names)
        for (int i = 1; i <= 20; ++i) {
            StudentNode* newNode = new StudentNode;
            newNode->student.rollNo = i;
            newNode->student.name = "Student " + to_string(i);
            newNode->next = studentHead;
            studentHead = newNode;
        }

        // Initialize courses with subjects, teacher names, and timetable details
        Course it = {"IT", {"DSA", "Calculus", "Automata", "SE", "THQ", "English", "Civics"},
                     {"Sir Samraiz", "Sir Mubeen", "Ma'am Sabahat", "Ma'am Anum", "Ma'am Farhat", "Dr. Rabia", "Ma'am Sobia"},
                                         {"9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM"}};
        courses.push_back(it);

        Course cs = {"CS", {"DSA", "Calculus", "Automata", "SE", "THQ", "English", "Civics"},
                     {"Sir Samraiz", "Sir Mubeen", "Ma'am Sabahat", "Ma'am Anum", "Ma'am Farhat", "Dr. Rabia", "Ma'am Sobia"},
                     {"9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM"}};
        courses.push_back(cs);

        Course se = {"SE", {"DSA", "Calculus", "Automata", "SE", "THQ", "English", "Civics"},
                     {"Sir Samraiz", "Sir Mubeen", "Ma'am Sabahat", "Ma'am Anum", "Ma'am Farhat", "Dr. Rabia", "Ma'am Sobia"},
                     {"9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM"}};
        courses.push_back(se);

        Course ai = {"AI", {"DSA", "Calculus", "Automata", "SE", "THQ", "English", "Civics"},
                     {"Sir Samraiz", "Sir Mubeen", "Ma'am Sabahat", "Ma'am Anum", "Ma'am Farhat", "Dr. Rabia", "Ma'am Sobia"},
                     {"9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM"}};
        courses.push_back(ai);

        // Initialize the 7 subjects with default teachers
        subjectTeachers = {
            {"DSA", "Sir Samraiz"},
            {"Calculus", "Sir Mubeen"},
            {"Automata", "Ma'am Sabahat"},
            {"SE", "Ma'am Anum"},
            {"THQ", "Ma'am Farhat"},
            {"English", "Dr. Rabia"},
            {"Civics", "Ma'am Sobia"}
        };
    }

    // Function to add a student (to linked list)
    void addStudent() {
        Student s;
        cout << "Enter student name: ";
        cin >> s.name;
        cout << "Enter father's name: ";
        cin >> s.fatherName;
        cout << "Enter roll number: ";
        cin >> s.rollNo;

        StudentNode* newStudent = new StudentNode;
        newStudent->student = s;
        newStudent->next = studentHead;
        studentHead = newStudent;

        cout << "Student added successfully!\n";
    }

    // Function to update student information (in linked list)
    void updateStudent() {
        int rollNo;
        cout << "Enter roll number to update: ";
        cin >> rollNo;

        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            if (temp->student.rollNo == rollNo) {
                cout << "Enter new name: ";
                cin >> temp->student.name;
                cout << "Enter new father's name: ";
                cin >> temp->student.fatherName;
                cout << "Student information updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Student not found.\n";
    }

    // Function to delete a student (from linked list)
    void deleteStudent() {
        int rollNo;
        cout << "Enter roll number to delete: ";
        cin >> rollNo;

        if (studentHead == nullptr) {
            cout << "No students to delete.\n";
            return;
        }

        if (studentHead->student.rollNo == rollNo) {
            StudentNode* temp = studentHead;
            studentHead = studentHead->next;
            delete temp;
            cout << "Student deleted successfully!\n";
            return;
        }

        StudentNode* temp = studentHead;
        while (temp->next != nullptr) {
            if (temp->next->student.rollNo == rollNo) {
                StudentNode* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                cout << "Student deleted successfully!\n";
                return;
            }
            temp = temp->next;
        }
                cout << "Student not found.\n";
    }

    // Function to search student by roll number (in linked list)
    void searchStudent() {
        int rollNo;
        cout << "Enter roll number to search: ";
        cin >> rollNo;

        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            if (temp->student.rollNo == rollNo) {
                cout << "Student found: " << temp->student.name << ", Father: " << temp->student.fatherName << ", Roll No: " << temp->student.rollNo << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Student not found.\n";
    }

    // Function to assign grade to a student for a specific subject
    // Function to display courses and return the selected course index
    int selectCourse() {
        cout << "Select a course:\n";
        cout << "1. IT\n";
        cout << "2. CS\n";
        cout << "3. SE\n";
        cout << "4. AI\n";
        cout << "Enter your choice: ";
        int courseIndex;
        cin >> courseIndex;

        if (courseIndex < 1 || courseIndex > 4) {
            cout << "Invalid choice. Try again.\n";
            return selectCourse();
        }
        return courseIndex - 1; // Adjust to zero-based indexing
    }

    // Function to display subjects and teachers for a course
    int selectSubject(int courseIndex) {
        cout << "Subjects and Teachers:\n";
        int i = 1;
        for (const auto &subject : subjectTeachers) {
            cout << i++ << ". " << subject.first << " - " << subject.second << "\n";
        }
        cout << "Enter subject number: ";
        int subjectIndex;
        cin >> subjectIndex;

        if (subjectIndex < 1 || subjectIndex > 7) {
            cout << "Invalid choice. Try again.\n";
            return selectSubject(courseIndex);
        }
        return subjectIndex - 1; // Adjust to zero-based indexing
    }

    // Function to assign grade
    void assignGrade() {
        int courseIndex = selectCourse();
        int subjectIndex = selectSubject(courseIndex);

        string subject = std::next(subjectTeachers.begin(), subjectIndex)->first;

        // Step 1: Display roll numbers (1 to 20)
        cout << "Available Roll Numbers (1-20):\n";
        for (int i = 1; i <= 20; ++i) {
            cout << i << " ";
            if (i % 10 == 0) cout << "\n"; // Formatting for readability
        }
        cout << "\n";

        // Step 2: Assign grades for each student roll number
        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            cout << "Enter grade for Roll No: " << temp->student.rollNo << " (" << temp->student.name << "): ";
            string grade;
            cin >> grade;

            // Update the grades map for the selected subject
            temp->student.grades[subject] = grade; // Using subject as key to store the grade

            cout << "Grade assigned successfully to Roll No: " << temp->student.rollNo << " for " << subject << ".\n";
            temp = temp->next; // Move to the next student
        }
    }

    // Function to view a student's grades
    void viewGrades() {
        int courseIndex = selectCourse();  // Assuming this function allows selecting a course

        int rollNo;
        cout << "Enter roll number to view grades: ";
        cin >> rollNo;

        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            if (temp->student.rollNo == rollNo) {
                cout << "Grades for " << temp->student.name << " (Roll No: " << temp->student.rollNo << "):\n";

                // Loop through subjects to print each grade
                for (const auto& subject : subjectTeachers) {
                    string subjectName = subject.first;
                    if (temp->student.grades.find(subjectName) != temp->student.grades.end()) {
                        cout << subjectName << " - " << subject.second << ": " 
                             << temp->student.grades.at(subjectName) << "\n";
                    } else {
                        cout << subjectName << " - " << subject.second << ": No grade assigned\n";
                    }
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Student not found.\n";
    }

        // Function to view courses
    void viewCourses() {
        cout << "Choose a course:\n";
        cout << "1. IT\n";
        cout << "2. SE\n";
        cout << "3. AI\n";
        cout << "4. CS\n";

        int courseChoice;
        cin >> courseChoice;

        if (courseChoice < 1 || courseChoice > 4) {
            cout << "Invalid choice.\n";
            return;
        }

        Course selectedCourse = courses[courseChoice - 1];
        cout << "Subjects for " << selectedCourse.courseName << " course:\n";
        for (size_t i = 0; i < selectedCourse.subjects.size(); ++i) {
            cout << selectedCourse.subjects[i] << " - " << selectedCourse.teachers[i] << "\n";
        }
    }

    // Function to view the timetable
    void viewTimetable() {
        int courseChoice, dayChoice;
        cout << "Choose a course (1.IT, 2.CS, 3.SE, 4.AI): ";
        cin >> courseChoice;

        if (courseChoice < 1 || courseChoice > 4) {
            cout << "Invalid choice.\n";
            return;
        }

        Course selectedCourse = courses[courseChoice - 1];
        cout << "Choose a day (1.Monday, 2.Tuesday, 3.Wednesday, 4.Thursday, 5.Friday, 6.Saturday, 7.Sunday): ";
        cin >> dayChoice;

        if (dayChoice < 1 || dayChoice > 7) {
            cout << "Invalid day choice.\n";
            return;
        }

        // Printing the timetable for the selected day
        string dayName;
        switch (dayChoice) {
            case 1: dayName = "Monday"; break;
            case 2: dayName = "Tuesday"; break;
            case 3: dayName = "Wednesday"; break;
            case 4: dayName = "Thursday"; break;
            case 5: dayName = "Friday"; break;
            case 6: dayName = "Saturday"; break;
            case 7: dayName = "Sunday"; break;
        }

        cout << "Timetable for " << selectedCourse.courseName << " course on " << dayName << ":\n";

        for (size_t i = 0; i < selectedCourse.subjects.size(); ++i) {
            cout << selectedCourse.subjects[i] << " - " << selectedCourse.teachers[i] << " - " << selectedCourse.times[i] << "\n";
        }
    }

    // Function to add or update teacher
    void addOrUpdateTeacher() {
        // Choose a course
        cout << "Select a course:\n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << (i + 1) << ". " << courses[i].courseName << endl;
        }
        int courseChoice;
        cin >> courseChoice;
        courseChoice--; // Adjusting for zero-based index

        cout << "\nAssign or Update a Teacher for a Subject:\n";
        int index = 1;
        for (const auto& subject : subjectTeachers) {
            cout << index++ << ". " << subject.first << " (Current: " << subject.second << ")\n";
        }

        int choice;
        cout << "Enter the subject number (1-7): ";
        cin >> choice;

        if (choice < 1 || choice > 7) {
            cout << "Invalid choice.\n";
            return;
        }

        string newTeacherName;
        auto it = subjectTeachers.begin();
        advance(it, choice - 1);
        string selectedSubject = it->first;
        string currentTeacher = it->second;

        cout << "Enter the new teacher's name: ";
        cin.ignore(); // Clear input buffer
        getline(cin, newTeacherName);

        // Update the teacher for the selected subject
        subjectTeachers[selectedSubject] = newTeacherName;

        cout << "Teacher for \"" << selectedSubject << "\" updated successfully.\n";
        cout << "Previous Teacher: " << currentTeacher << "\n";
        cout << "New Teacher: " << newTeacherName << "\n";
    }



    // Function to view teachers 
    void viewTeachers() {
        // Step 1: Choose a course
        cout << "Select a course:\n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << (i + 1) << ". " << courses[i].courseName << endl;
        }
        int courseChoice;
        cin >> courseChoice;

        courseChoice--; // Adjusting for zero-based index

        // Step 2: Choose a subject in the selected course
        Course selectedCourse = courses[courseChoice];
        cout << "Subjects and Teachers for " << selectedCourse.courseName << ":\n";
        for (int i = 0; i < selectedCourse.subjects.size(); ++i) {
            // Display the updated teacher's name directly from the subjectTeachers map
            string teacherName = subjectTeachers[selectedCourse.subjects[i]];
            cout << (i + 1) << ". " << selectedCourse.subjects[i] 
                 << " - " << teacherName << endl;
        }
    }

    // Function to mark attendance            
    void markAttendance() {
        // Step 1: Choose a course (IT, CS, SE, AI)
        cout << "Select a course:\n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << (i + 1) << ". " << courses[i].courseName << endl;
        }
        int courseChoice;
        cin >> courseChoice;
        courseChoice--; // Adjusting for zero-based index

        // Step 2: Choose a subject (7 subjects in the selected course)
        Course selectedCourse = courses[courseChoice];
        cout << "Subjects and Teachers for " << selectedCourse.courseName << ":\n";
        for (int i = 0; i < selectedCourse.subjects.size(); ++i) {
            cout << (i + 1) << ". " << selectedCourse.subjects[i] << " - " << selectedCourse.teachers[i] << endl;
        }

        int subjectChoice;
        cout << "Enter subject number to mark attendance: ";
        cin >> subjectChoice;
        subjectChoice--; // Adjusting for zero-based index

        string subject = selectedCourse.subjects[subjectChoice];
        
        // Step 3: Display roll numbers (1 to 20) and mark attendance
        cout << "\nAvailable Roll Numbers (1-20):\n";
        for (int i = 1; i <= 20; ++i) {
            cout << "Roll No: " << i << " - ";
            bool attendance;
            cout << "Enter 1 for present, 0 for absent: ";
            cin >> attendance;

            // Step 4: Iterate through the linked list of students and mark attendance
            StudentNode* temp = studentHead;
            while (temp != nullptr) {
                if (temp->student.rollNo == i) {
                    temp->student.attendance[subject] = attendance;  // Mark attendance for the selected subject
                    break;  // Stop once the correct student is found
                }
                temp = temp->next;
            }
        }

        // Step 5: Display attendance summary for the selected subject
        cout << "\nAttendance Summary for " << subject << ":\n";
        int presentCount = 0, absentCount = 0;
        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            bool isPresent = temp->student.attendance[subject];
            cout << "Roll No: " << temp->student.rollNo
                 << " (" << temp->student.name << ") - "
                 << (isPresent ? "Present" : "Absent") << "\n";
            
            if (isPresent) presentCount++;
            else absentCount++;

            temp = temp->next;
        }

        // Step 6: Display the number of present and absent students
        cout << "\nSummary:\n";
        cout << "Present: " << presentCount << "\n";
        cout << "Absent: " << absentCount << "\n";
    }

    // Function to view attendance
    void viewAttendance() {
        // Step 1: Choose a course (IT, CS, SE, AI)
        cout << "Select a course:\n";
        for (int i = 0; i < courses.size(); ++i) {
            cout << (i + 1) << ". " << courses[i].courseName << endl;
        }
        int courseChoice;
        cin >> courseChoice;
        courseChoice--; // Adjusting for zero-based index

        // Step 2: Choose a subject (7 subjects in the selected course)
        Course selectedCourse = courses[courseChoice];
        cout << "Subjects and Teachers for " << selectedCourse.courseName << ":\n";
        for (int i = 0; i < selectedCourse.subjects.size(); ++i) {
            cout << (i + 1) << ". " << selectedCourse.subjects[i] << " - " << selectedCourse.teachers[i] << endl;
        }

                int subjectChoice;
        cout << "Enter subject number to view attendance: ";
        cin >> subjectChoice;
        subjectChoice--; // Adjusting for zero-based index

        string subject = selectedCourse.subjects[subjectChoice];

        // Step 3: Display roll numbers (1 to 20) and enter roll number to view attendance
        cout << "\nAvailable Roll Numbers (1-20):\n";
        for (int i = 1; i <= 20; ++i) {
            cout << i << " ";
            if (i % 10 == 0) cout << "\n"; // Formatting for readability
        }
        cout << "\nEnter roll number to check attendance: ";
        int rollNo;
        cin >> rollNo;

        if (rollNo < 1 || rollNo > 20) {
            cout << "Invalid roll number! Please enter a number between 1 and 20.\n";
            return;
        }

        // Step 4: Search for the student by roll number and display attendance
        StudentNode* temp = studentHead;
        while (temp != nullptr) {
            if (temp->student.rollNo == rollNo) {
                // Use the subject name (string) as the key for the attendance map
                cout << "Attendance for " << temp->student.name << " in " << subject << ": "
                     << (temp->student.attendance[subject] ? "Present" : "Absent") << "\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Student not found.\n";
    }
};
// Main function
int main() {
    Admin admin;

    while (true) {
        clearScreen(); // Clear the screen at the start of the loop
        int role;
        cout << "\nEnter Role (1. Admin, 2. Teacher, 3. Student, 0. Exit): ";
        cin >> role;

        if (role == 0) {
            cout << "Exiting program.\n";
            break;
        }

        string roleName;
        if (role == 1) roleName = "Admin";
        else if (role == 2) roleName = "Teacher";
        else if (role == 3) roleName = "Student";
        else {
            cout << "Invalid role selected. Please try again.\n";
            continue;
        }

        // Login process
        if (login(roleName)) {  // If login is successful
            while (true) {
                switch (role) {
                    case 1: {  // Admin Menu
                        int action;
                        cout << "\nAdmin Menu:\n";
                        cout << "1. Add Student\n";
                        cout << "2. Update Student\n";
                        cout << "3. Delete Student\n";
                        cout << "4. Search Student\n";
                        cout << "5. Add/Update Teacher\n";
                        cout << "6. View Teachers\n";
                        cout << "7. View Courses\n";
                        cout << "8. View Timetable\n";
                        cout << "9. Assign Grades\n";
                        cout << "10. View Grades\n";
                        cout << "11. Mark Attendance\n";
                        cout << "12. View Attendance\n";
                        cout << "0. Exit Role\n";
                        cout << "Choose an option: ";
                        cin >> action;

                        if (action == 0) break;

                        switch (action) {
                            case 1: admin.addStudent(); break;
                            case 2: admin.updateStudent(); break;
                            case 3: admin.deleteStudent(); break;
                            case 4: admin.searchStudent(); break;
                            case 5: admin.addOrUpdateTeacher(); break;
                            case 6: admin.viewTeachers(); break;
                            case 7: admin.viewCourses(); break;
                            case 8: admin.viewTimetable(); break;
                            case 9: admin.assignGrade(); break;
                            case 10: admin.viewGrades(); break;
                            case 11: admin.markAttendance(); break;
                            case 12: admin.viewAttendance(); break;
                            default: cout << "Invalid option.\n"; break;
                        }
                        break;
                    }
                    case 2: {  // Teacher Menu
                        int action;
                        cout << "\nTeacher Menu:\n";
                        cout << "1. Assign Grades\n";
                        cout << "2. Mark Attendance\n";
                        cout << "3. View Timetable\n";
                        cout << "4. View Courses\n";
                        cout << "0. Exit Role\n";
                        cout << "Choose an option: ";
                        cin >> action;

                        if (action == 0) break;

                        switch (action) {
                            case 1: admin.assignGrade(); break;
                                                        case 2: admin.markAttendance(); break;
                            case 3: admin.viewTimetable(); break;
                            case 4: admin.viewCourses(); break;
                            default: cout << "Invalid option.\n"; break;
                        }
                        break;
                    }
                    case 3: {  // Student Menu
                        int action;
                        cout << "\nStudent Menu:\n";
                        cout << "1. View Grades\n";
                        cout << "2. View Timetable\n";
                        cout << "3. View Courses\n";
                        cout << "4. View Attendance\n";
                        cout << "0. Exit Role\n";
                        cout << "Choose an option: ";
                        cin >> action;

                        if (action == 0) break;

                        switch (action) {
                            case 1: admin.viewGrades(); break;
                            case 2: admin.viewTimetable(); break;
                            case 3: admin.viewCourses(); break;
                            case 4: admin.viewAttendance(); break;
                            default: cout << "Invalid option.\n"; break;
                        }
                        break;
                    }
                }

                // Prompt to reselect role or exit program
                cout << "\nWould you like to continue? Press 1 for Role Selection, 0 for Exit: ";
                int continueChoice;
                cin >> continueChoice;

                if (continueChoice == 1) {
                    cout << "Returning to role selection...\n";
                    break;  // Break the inner loop to reselect role
                } else if (continueChoice == 0) {
                    cout << "Exiting program.\n";
                    return 0;  // Exit the program
                } else {
                    cout << "Invalid choice. Returning to role selection by default.\n";
                    break;  // Default to reselect role
                }
            }
        }
    }

    return 0;
}
