#include <iostream>
#include <vector>
#include <string>

class Task {
public:
    std::string description;
    int maxScore;

    Task(const std::string& desc, int max)
        : description(desc), maxScore(max) {}
};

class Student {
public:
    std::string name;
    int id;
    std::string information;
    std::vector<std::string> assignments;
    std::vector<int> examScores;

    // Constructor
    Student(const std::string& studentName, int studentId, const std::string& info)
        : name(studentName), id(studentId), information(info) {}

    // Function to submit an assignment
    void submitAssignment(const std::string& assignment) {
        assignments.push_back(assignment);
        std::cout << "Assignment submitted successfully." << std::endl;
    }

    // Function to take an exam
    void takeExam(int score) {
        examScores.push_back(score);
        std::cout << "Exam taken successfully." << std::endl;
    }

    // Function to change student information
    void changeInformation(const std::string& newInfo) {
        information = newInfo;
        std::cout << "Information updated successfully." << std::endl;
    }
};

class Teacher {
public:
    std::string name;
    std::vector<Student>& students;

    // Constructor
    Teacher(const std::string& teacherName, std::vector<Student>& studentList)
        : name(teacherName), students(studentList) {}

    // Function to assign a task to a student
    void assignTask(Student& student, const Task& task) {
        std::cout << "Task assigned to student " << student.name << ": " << task.description << std::endl;
    }

    // Function to grade a student
    void gradeStudent(Student& student, int score) {
        student.takeExam(score);
        std::cout << "Student " << student.name << " graded successfully." << std::endl;
    }

    // Function to add or edit student information
    void addOrEditStudentInformation(Student& student, const std::string& newInfo) {
        student.changeInformation(newInfo);
        std::cout << "Student information updated successfully." << std::endl;
    }
};

int main() {
    // Creating students
    std::vector<Student> students;
    students.push_back(Student("John Doe", 1, "Computer Science"));
    students.push_back(Student("Jane Smith", 2, "Physics"));

    // Creating teacher
    Teacher teacher("Dr. Johnson", students);

    // Assigning a task to a student
    Task task("Write a research paper", 100);
    teacher.assignTask(students[0], task);

    // Student submits an assignment
    students[0].submitAssignment("Research Paper Draft");

    // Teacher grades the student
    teacher.gradeStudent(students[0], 90);

    // Changing student information
    teacher.addOrEditStudentInformation(students[1], "Mathematics");

    return 0;
}
