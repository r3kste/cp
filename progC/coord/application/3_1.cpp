#include<bits/stdc++.h>

class Person {
public:
    std::string name;
    int age;
    std::string id;
    std::string department;
    Person(std::string name, int age, std::string id, std::string department) {
        this->name = name;
        this->age = age;
        this->id = id;
        this->department = department;
    }

    void next_year() {
        this->set_age(this->age + 1);
    }

    void set_age(int new_age) {
        this->age = new_age;
    }
};

class Student;
class Teacher;
class Marks;

class Student: public Person {
public:
    Student(std::string name = "", int age = -1, std::string id = "", std::string department = ""): Person(name, age, id, department) {}

    int get_mark(Marks& marks);
};

class Teacher: public Person {
public:
    Teacher(std::string name = "", int age = -1, std::string id = "", std::string department = ""): Person(name, age, id, department) {}

    bool check_auth(Student& student) {
        if (this->department != student.department) {
            std::cerr << "Error: Department mismatch!\n";
            std::cerr << "Student department: " << student.department << "\n";
            std::cerr << "Teacher department: " << this->department << "\n";
            return false;
        }

        return true;
    }

    void set_mark(Marks& marks, Student& student, int new_mark);
    int get_mark(Marks& marks, Student& student);
};

class Marks {
    friend class Teacher;

private:
    std::map<std::string, int> marks;
    void set_mark(Teacher& teacher, Student& student, int new_mark);

public:
    int get_mark(Student& student);
};

void Marks::set_mark(Teacher& teacher, Student& student, int new_mark) {
    if (teacher.check_auth(student)) {
        marks[student.id] = new_mark;
    }
}

int Marks::get_mark(Student& student) {
    if (marks.find(student.id) == marks.end()) {
        std::cerr << "Error: Marks not found! for student\n";
        return -1;
    }

    return marks[student.id];
}

int Student::get_mark(Marks& marks) {
    return marks.get_mark(*this);
}

int Teacher::get_mark(Marks& marks, Student& student) {
    return marks.get_mark(student);
}

void Teacher::set_mark(Marks& marks, Student& student, int new_mark) {
    marks.set_mark(*this, student, new_mark);
}

struct database {
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    Marks marks;

    void add_student(Student student) {
        students.push_back(student);
    }

    void add_teacher(Teacher teacher) {
        teachers.push_back(teacher);
    }
};

int main() {
    database db;
    db.add_student(Student("Anton", 18, "me23b015", "ME"));
    db.add_teacher(Teacher("Prof. Jack", 44, "john", "ME"));
    db.add_teacher(Teacher("Dr. Will", 46, "smith", "CS"));
    Teacher& teacher0 = db.teachers[0];
    Teacher& teacher1 = db.teachers[1];
    Student& student0 = db.students[0];
    teacher0.set_mark(db.marks, student0, 93);
    std::cout << student0.get_mark(db.marks) << "\n";
    teacher1.set_mark(db.marks, student0, 95);
    std::cout << student0.get_mark(db.marks) << "\n";
}