#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> // For clearing input buffer

using namespace std;

// ==========================================
// 1. AUTOMATIC GRADING ENGINE
// ==========================================
struct Course {
    string code;
    string title;
    int score;
    int point;      // 0-5
    string grade;   // A-F
    int level;      // 100, 200, or 300

    // Constructor: Automatically converts Score -> Grade & Point
    Course(string c, string t, int s, int l) {
        code = c;
        title = t;
        score = s;
        level = l;

        // The Grading Logic
        if (s >= 70)      { point = 5; grade = "A"; }
        else if (s >= 60) { point = 4; grade = "B"; }
        else if (s >= 50) { point = 3; grade = "C"; }
        else if (s >= 45) { point = 2; grade = "D"; }
        else if (s >= 40) { point = 1; grade = "E"; }
        else              { point = 0; grade = "F"; }
    }
};

// ==========================================
// 2. STUDENT CLASS (Handles Transcript & Math)
// ==========================================
class Student {
private:
    string fullName;
    string matricNo;
    string department;
    vector<Course> transcript; // Stores all courses

public:
    Student(string name, string matric, string dept) {
        fullName = name;
        matricNo = matric;
        department = dept;
    }

    string getName() const { return fullName; }
    string getMatric() const { return matricNo; }

    // Add a single course result
    void addCourse(string code, string title, int score, int level) {
        transcript.push_back(Course(code, title, score, level));
    }

    // This function calculates the Special Weighted CGPA (2, 4, 6)
    // and prints the Professional Transcript.
    void printFullTranscript() {
        double pts100 = 0, pts200 = 0, pts300 = 0;
        double cnt100 = 0, cnt200 = 0, cnt300 = 0;

        cout << "\n================================================================================" << endl;
        cout << "                           OFFICIAL ACADEMIC TRANSCRIPT                         " << endl;
        cout << "================================================================================" << endl;
        cout << " Name:       " << left << setw(30) << fullName << " Matric No: " << matricNo << endl;
        cout << " Department: " << left << setw(30) << department << endl;
        cout << "================================================================================" << endl;
        cout << left << setw(8) << "LVL" << setw(10) << "CODE" << setw(25) << "COURSE TITLE" 
             << setw(8) << "SCORE" << setw(8) << "GRADE" << setw(5) << "GP" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;

        // Loop through courses to print them and sum up points
        if (transcript.empty()) {
            cout << "   [No records found]" << endl;
        } else {
            for (const auto& c : transcript) {
                cout << left << setw(8) << c.level << setw(10) << c.code << setw(25) << c.title 
                     << setw(8) << c.score << setw(8) << c.grade << setw(5) << c.point << endl;

                // Sort points into levels for calculation
                if (c.level == 100)      { pts100 += c.point; cnt100++; }
                else if (c.level == 200) { pts200 += c.point; cnt200++; }
                else if (c.level == 300) { pts300 += c.point; cnt300++; }
            }
        }
        cout << "--------------------------------------------------------------------------------" << endl;

        // --- CALCULATE WEIGHTED CGPA ---
        double gpa100 = (cnt100 > 0) ? pts100 / cnt100 : 0.0;
        double gpa200 = (cnt200 > 0) ? pts200 / cnt200 : 0.0;
        double gpa300 = (cnt300 > 0) ? pts300 / cnt300 : 0.0;

        // Formula: (100L*2 + 200L*4 + 300L*6) / 12
        double weightedSum = (gpa100 * 2.0) + (gpa200 * 4.0) + (gpa300 * 6.0);
        double finalCGPA = weightedSum / 12.0;

        // Determine Class
        string honour;
        if (finalCGPA >= 4.50) honour = "FIRST CLASS HONOURS";
        else if (finalCGPA >= 3.50) honour = "SECOND CLASS UPPER";
        else if (finalCGPA >= 2.40) honour = "SECOND CLASS LOWER";
        else if (finalCGPA >= 1.50) honour = "THIRD CLASS";
        else honour = "FAIL / ADVISE TO WITHDRAW";

        // Display Summary
        cout << " ACADEMIC SUMMARY (Weighted System):" << endl;
        cout << " 100 Level (Weight 2): GPA " << fixed << setprecision(2) << gpa100 << endl;
        cout << " 200 Level (Weight 4): GPA " << gpa200 << endl;
        cout << " 300 Level (Weight 6): GPA " << gpa300 << endl;
        cout << "================================================================================" << endl;
        cout << " FINAL CGPA:     " << finalCGPA << endl;
        cout << " DEGREE STATUS:  " << honour << endl;
        cout << "================================================================================" << endl;
    }
};

// ==========================================
// 3. MAIN PORTAL (Dashboard & Logic)
// ==========================================
class Portal {
private:
    vector<Student> db;

public:
    // Constructor: Pre-loads the "Database" with students
    Portal() {
        // --- STUDENT 1: HENRY ---
        Student s1("Henry Ehindero", "22N02123", "Computer Science");
        // Pre-loaded grades
        s1.addCourse("CSC101", "Intro to Comp Sci", 80, 100); // A
        s1.addCourse("MTH101", "General Maths", 75, 100);     // A
        s1.addCourse("CSC201", "C++ Programming", 90, 200);   // A
        s1.addCourse("CSC202", "Data Structures", 85, 200);   // A
        db.push_back(s1);

        // --- STUDENT 2: KELLY ---
        Student s2("Kelly Johnson", "22N02322", "Software Engineering");
        s2.addCourse("CSC101", "Intro to Comp Sci", 65, 100); // B
        s2.addCourse("MTH101", "General Maths", 55, 100);     // C
        db.push_back(s2);

        // --- STUDENT 3: SOLA ---
        Student s3("Sola Adebayo", "22N02144", "Info Technology");
        s3.addCourse("CSC101", "Intro to Comp Sci", 45, 100); // D
        db.push_back(s3);
    }

    // --- LOGIN SCREEN ---
    bool login() {
        string u, p;
        cout << "\n\n";
        cout << "################################################" << endl;
        cout << "#         UNIVERSITY LECTURER PORTAL           #" << endl;
        cout << "################################################" << endl;
        cout << "Username: "; cin >> u;
        cout << "Password: "; cin >> p;
        if (u == "admin" && p == "password") return true;
        return false;
    }

    // --- ADD GRADES FUNCTION ---
    void addGradeRoutine() {
        string matricKey;
        cout << "\n[INPUT MODE] Enter Student Matric No (e.g., 22N02123): ";
        cin >> matricKey;

        // Find Student
        int index = -1;
        for (int i = 0; i < db.size(); i++) {
            if (db[i].getMatric() == matricKey) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << ">> Error: Student not found in database.\n";
            return;
        }

        cout << ">> Student Found: " << db[index].getName() << endl;
        
        // Loop to add multiple courses
        while (true) {
            int level, score;
            string code, title;

            cout << "\n--------------------------------------------" << endl;
            cout << "Enter Course Level (100, 200, 300) or 0 to finish: ";
            cin >> level;
            if (level == 0) break;

            cout << "Enter Course Code (e.g. CSC301): "; cin >> code;
            cout << "Enter Course Title (Use_Underscores): "; cin >> title;
            cout << "Enter Raw Score (0-100): "; cin >> score;

            // *** AUTOMATIC FEEDBACK ***
            // Shows the Grade/Point immediately before saving
            Course temp(code, title, score, level); 
            cout << "   >>> AUTO-GRADE: " << temp.grade << " (" << temp.point << " pts) <<<" << endl;
            
            // Save to DB
            db[index].addCourse(code, title, score, level);
            cout << "   [Saved Successfully]" << endl;
        }
    }

    // --- SEARCH & VIEW TRANSCRIPT ---
    void viewTranscriptRoutine() {
        string searchKey;
        cout << "\n[SEARCH MODE] Enter Name or Matric: ";
        cin.ignore();
        getline(cin, searchKey);

        bool found = false;
        for (int i = 0; i < db.size(); i++) {
            // Checks if searchKey is part of Name OR matches Matric exactly
            if (db[i].getName().find(searchKey) != string::npos || db[i].getMatric() == searchKey) {
                db[i].printFullTranscript();
                found = true;
            }
        }
        if (!found) cout << ">> No matching records found." << endl;
    }

    // --- MAIN DASHBOARD LOOP ---
    void run() {
        if (!login()) {
            cout << "Access Denied.\n";
            return;
        }

        int choice;
        while (true) {
            cout << "\n\n";
            cout << "================ LECTURER DASHBOARD ================" << endl;
            cout << " 1. View All Students List" << endl;
            cout << " 2. Search & Generate Transcript (Auto-CGPA)" << endl;
            cout << " 3. Input New Student Grades" << endl;
            cout << " 4. Exit System" << endl;
            cout << "====================================================" << endl;
            cout << "Select Action: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    cout << "\n--- CLASS LIST ---" << endl;
                    for (auto& s : db) {
                        cout << " - " << left << setw(20) << s.getName() << " [" << s.getMatric() << "]" << endl;
                    }
                    break;
                case 2:
                    viewTranscriptRoutine();
                    break;
                case 3:
                    addGradeRoutine();
                    break;
                case 4:
                    cout << "Logging out... Goodbye." << endl;
                    return;
                default:
                    cout << "Invalid option." << endl;
            }
        }
    }
};

// ==========================================
// 4. ENTRY POINT
// ==========================================
int main() {
    Portal app;
    app.run();
    return 0;
}
