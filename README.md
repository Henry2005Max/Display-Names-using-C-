 🎓 Enterprise University Grading System (C++)

A professional command-line interface (CLI) portal designed for university lecturers to manage academic records efficiently.

 🚀 Key Features
- **Lecturer Authentication:** Secure login system for staff access.
- **Searchable Database:** Instantly fetch student records by Name or Matric Number.
- **Automatic Grading Engine:** Input raw scores (0-100) and the system automatically assigns Letter Grades (A-F) and Grade Points (0-5).
- **Semester-Wise Tracking:** Separates First and Second-semester results for 100L, 200L, and 300L.
- **Weighted CGPA Logic:** Implements a custom academic weight system (2:4:6 ratio) to determine the Final Class of Honour.
- **Professional Transcripts:** Generates a structured academic summary including Level GPAs and Degree Status.

## 🛠️ Tech Stack
- **Language:** C++11 or higher
- **Library:** Standard Template Library (STL)
- **Compiler:** GCC / G++

## 📊 How It Works
The system follows the standard academic progression:
1. **Input:** Lecturer enters raw course scores via the dashboard.
2. **Processing:** The `Student` class calculates semester averages.
3. **Weighting:** The system applies weights to different levels (Year 3 carries 3x the weight of Year 1).
4. **Output:** A formatted transcript is generated showing if the student graduated with First Class, Second Class, etc.

## 📖 Usage
1. Clone the repository.
2. Compile the code: `g++ main.cpp -o portal`
3. Run the application: `./portal`
4. Use credentials: **admin / password**
