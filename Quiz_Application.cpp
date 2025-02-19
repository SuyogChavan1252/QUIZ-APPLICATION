#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int getopt(char c);

class Question {
public:
    string q;
    string opt[4];
    char inputAns;
    char ans;
};

class Quiz {
public:
    int n, totalMarks, pts;
    vector<Question> que;
    vector<Question> v;
    
    Quiz() {
        totalMarks = 0;
    }

    void getQue() {
        Question a;
        cout << "Enter number of questions: ";
        cin >> n;
        cout << "Enter marks for each question: ";
        cin >> pts;
        cin.ignore(); 

        for (int i = 0; i < n; i++) {
            cout << "Question " << i + 1 << ": ";
            getline(cin, a.q);
            cout << "Options:\n";
            for (int j = 0; j < 4; j++) {
                getline(cin, a.opt[j]);
            }
            cout << "Correct Option (a/b/c/d): ";
            cin >> a.ans;
            cin.ignore();
            que.push_back(a);
        }

        ofstream fileout("quiz.txt");
        fileout << n << " " << pts << endl;
        for (int i = 0; i < n; i++) {
            fileout << que[i].q << endl;
            for (int j = 0; j < 4; j++) {
                fileout << que[i].opt[j] << endl;
            }
            fileout << que[i].ans << endl;
        }
        fileout.close();
        cout << "Quiz saved successfully!\n";
    }

    void startQuiz() {
        Question a;
        ifstream filein("quiz.txt");

        if (!filein) {
            cout << "No quiz found. Please create one first.\n";
            return;
        }

        int p;
        filein >> p >> pts;
        filein.ignore();

        for (int j = 0; j < p; j++) {
            getline(filein, a.q);
            cout << "\n" << a.q << endl;
            for (int i = 0; i < 4; i++) {
                getline(filein, a.opt[i]);
            }
            cout << "a) " << a.opt[0] << "\tb) " << a.opt[1] << "\n";
            cout << "c) " << a.opt[2] << "\td) " << a.opt[3] << "\n";

            filein >> a.ans;
            filein.ignore();

            cout << "Enter your answer (a/b/c/d): ";
            cin >> a.inputAns;
            while (a.inputAns < 'a' || a.inputAns > 'd') {
                cout << "Invalid input! Please enter a, b, c, or d: ";
                cin >> a.inputAns;
            }

            if (a.inputAns == a.ans) {
                totalMarks += pts;
            }
            v.push_back(a);
        }
        filein.close();
    }

    void displayResults() {
        cout << "\n--- Quiz Results ---\n";
        for (const auto& q : v) {
            cout << q.q << endl;
            cout << "Correct Answer: " << q.ans << ") " << q.opt[getopt(q.ans)] << endl;
            cout << "Your Answer: " << q.inputAns << ") " << q.opt[getopt(q.inputAns)] << endl;
        }
        cout << "TOTAL SCORE: " << totalMarks << " / " << (v.size() * pts) << "\n";
    }
};

int getopt(char c) {
    return (c >= 'a' && c <= 'd') ? c - 'a' : -1;
}

int main() {
    Quiz quiz;
    int ch;
    char garbage;

    while (true) {
        cout << "\n1) Make Quiz\n2) Start Quiz\n3) Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                quiz.getQue();
                break;
            case 2:
                quiz.startQuiz();
                cout << "Press any key to view score: ";
                cin >> garbage;
                quiz.displayResults();
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}