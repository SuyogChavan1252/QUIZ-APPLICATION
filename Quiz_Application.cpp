#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int getopt(char c);

class question
{
public:
    string q;
    string opt[4];
    char inputans;
    char ans;
    //int pts;
    /*question()
    {
        q = "";
        for (int i = 0; i < 4; i++)
        {
            opt[i] = "";
        }
    }*/
};

class quiz
{
public:
    int n,iMarks,pts;
    vector<question> que;
    vector<question> v;
    quiz()
    {
    	iMarks = 0;
	}
    void getque()
    {
        question a;
        cout << "Enter number of Question: ";
        cin >> n;
        cout<<"Enter marks for each question : ";
        cin>>pts;
        for (int i = 0; i < n; i++)
        {
            cout << "Question " << i + 1 << " : ";
            cin.ignore(); 
            getline(cin, a.q);
            cout << "Options :" << endl;
            for (int j = 0; j < 4; j++)
            {
                getline(cin, a.opt[j]);
            }
            cout << "Correct Option : ";
            cin >> a.ans;
            //cout << "Points : ";
            //cin >> pts;
            cout << endl;
            que.push_back(a);
        }
        cout << endl;
        ofstream fileout;
        fileout.open("quiz.txt");
        fileout << n << endl;
        for (int i = 0; i < n; i++)
        {
            fileout << "Question " << i + 1 << " : ";
            fileout << que[i].q << endl;
            for (int j = 0; j < 4; j++)
            {
                fileout << que[i].opt[j] << endl;
            }
            fileout << que[i].ans << endl;
            fileout << pts << endl;
            cout << endl;
        }
        fileout.close();
    }

    void startquiz()
    {
    	question a;
        ifstream filein;
        filein.open("quiz.txt");
        int p;
        filein >> p;
        filein.ignore();
        for (int j = 0; j < p; j++)
        {
            getline(filein, a.q);
            cout << a.q << endl;
            for (int i = 0; i < 4; i++)
            {
                getline(filein, a.opt[i]);
            }
            cout << "a) " << a.opt[0] << "		" << "b) " << a.opt[1] << endl << "c) " << a.opt[2] << "		" << "d) " << a.opt[3] << endl;
            filein >> a.ans;
            filein.ignore();
            cout << "Enter correct Option : ";
            cin >> a.inputans;
            filein >> pts;
            filein.ignore();
            if (a.inputans == a.ans)
            {
                iMarks = iMarks + pts;
            }
            v.push_back(a);
        }
        filein.close();
    }

    void display()
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout<< v[i].q<<endl;
            cout << "a) " << v[i].opt[0] << "       " << "b) " << v[i].opt[1] << endl << "c) " << v[i].opt[2] << "       " << "d) " << v[i].opt[3] << endl;
            cout << "Correct Answer : " << v[i].ans << ") " << v[i].opt[getopt(v[i].ans)] << endl;
            cout << "Your Answer : " << v[i].inputans << ") " << v[i].opt[getopt(v[i].inputans)] << endl;
        }
        cout << "TOTAL SCORE : " << iMarks << endl;
    }
};

int getopt(char c)
{
    if (c == 'a')
        return 0;
    if (c == 'b')
        return 1;
    if (c == 'c')
        return 2;
    if (c == 'd')
        return 3;
    return -1;
}

int main()
{
    quiz z;
    int ch;
    char garbage;
    cout << "Enter the Command." << endl
         << "1) Make Quiz." << endl
         << "2) Start Quiz." << endl
         << "3) Exit." << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
        z.getque();
        break;
    case 2:
        z.startquiz();
        cout<<"PRESS any key to view score.   ";
        cin>>garbage;
        cout<<endl<<endl;
    	z.display();
        break;
    case 3:
        return 0;
    default:
        cout << "Invalid Input." << endl;
        break;
    }
    return 0;
}
