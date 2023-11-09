#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class Student {
public:
    std::string name;
    std::vector<int> grades;

    Student(const std::string& studentName) : name(studentName) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    double getAverageGrade() {
        if (grades.empty()) {
            return 0.0;
        }

        int sum = 0;
        for (int grade : grades) {
            sum += grade;
        }

        return static_cast<double>(sum) / grades.size();
    }

    std::string toCSV() const {
        std::stringstream ss;
        ss << name << ",";
        for (int grade : grades) {
            ss << grade << ",";
        }
        return ss.str();
    }

    void fromCSV(const std::string& csvData) {
        std::istringstream ss(csvData);
        std::getline(ss, name, ',');
        int grade;
        while (ss >> grade) {
            grades.push_back(grade);
            char comma;
            ss >> comma;
        }
    }
};

int main() {
    std::vector<Student> students;

    // Load student data from a CSV file at the beginning
    std::ifstream inputFile("C:\\Users\\avila\\OneDrive\\10 - Fall 2023\\CSE 310\\StudentGradeTracker\\student_data.csv");
    std::string line;
    while (std::getline(inputFile, line)) {
        Student student("");
        student.fromCSV(line);
        students.push_back(student);
    }
    inputFile.close();

    while (true) {
        std::cout << "Options:\n";
        std::cout << "1. Add a student\n";
        std::cout << "2. Add a grade for a student\n";
        std::cout << "3. Display average grade for a student\n";
        std::cout << "4. Display all students and their average grades\n";
        std::cout << "5. Save and exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cout << "Enter student name: ";
            std::cin >> name;
            students.push_back(Student(name));
            std::cout << "Student added.\n";
        } else if (choice == 2) {
            if (students.empty()) {
                std::cout << "No students added yet.\n";
            } else {
                std::string name;
                int grade;
                std::cout << "Enter student name: ";
                std::cin >> name;

                bool found = false;
                for (Student& student : students) {
                    if (student.name == name) {
                        std::cout << "Enter the grade: ";
                        std::cin >> grade;
                        student.addGrade(grade);
                        found = true;
                        std::cout << "Grade added.\n";
                        break;
                    }
                }

                if (!found) {
                    std::cout << "Student not found.\n";
                }
            }
        } else if (choice == 3) {
            if (students.empty()) {
                std::cout << "No students added yet.\n";
            } else {
                std::string name;
                std::cout << "Enter student name: ";
                std::cin >> name;

                bool found = false;
                for (Student student : students) {
                    if (student.name == name) {
                        double averageGrade = student.getAverageGrade();
                        std::cout << "Average grade for " << name << " is: " << averageGrade << "\n";
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cout << "Student not found.\n";
                }
            }
        } else if (choice == 4) {
            if (students.empty()) {
                std::cout << "No students added yet.\n";
            } else {
                std::cout << "Students and their average grades:\n";
                for (Student student : students) {
                    double averageGrade = student.getAverageGrade();
                    std::cout << "Student: " << student.name << ", Average Grade: " << averageGrade << "\n";
                }
            }
        } else if (choice == 5) {
            // Save student data to the CSV file and exit
            std::ofstream outputFile("C:\\Users\\avila\\OneDrive\\10 - Fall 2023\\CSE 310\\StudentGradeTracker\\student_data.csv");
            for (const Student& student : students) {
                outputFile << student.toCSV() << "\n";
            }
            outputFile.close();
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}