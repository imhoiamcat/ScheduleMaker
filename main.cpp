#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Teacher {
    string name;
    vector<vector<int>> time;
};

struct Lesson {
    int teacher;
    string sub;
};

map<string, vector<vector<pair<int, Lesson>>>> schedule;
vector<Teacher> teachers;
map<string, vector<pair<Lesson, int>>> program;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    //0. Enter number of teachers
    int n, m;
    fin >> n;
    teachers.resize(n);

    //1. Enter list of teachers
    for (int i = 0; i < n; i++) {
        fin >> teachers[i].name;
        teachers[i].time.resize(6);
        for (int k = 0; k < 6; k++) {
            teachers[i].time[k].resize(8);
            for (int j = 0; j < 8; j++) {
                fin >> teachers[i].time[k][j];
            }
        }
    }

    //2. Print list of teachers
    for (int i = 0; i < n; i++) {
        fout << teachers[i].name << endl;
        for (int k = 0; k < 6; k++) {
            for (int j: teachers[i].time[k]) {
                fout << j << " ";
            }
            fout << endl;
        }
    }

    //3. Enter number of grades
    int g;
    fin >> g;

    //4. Enter program for each grade
    string s;
    Lesson tmp;
    int sub, c;
    for (int i = 0; i < g; i++) {
        fin >> s >> sub;
        for (int j = 0; j < sub; j++) {
            fin >> tmp.sub >> tmp.teacher >> c;
            program[s].push_back({tmp, c});
        }
    }

    //5. Print program for each grade
    for (pair<string, vector<pair<Lesson, int>>> i: program) {
        fout << i.first << endl;
        for (pair<Lesson, int> j: i.second) {
            fout << j.first.sub << " " << teachers[j.first.teacher].name << " " << j.second << endl;
        }
    }

    for (pair<string, vector<pair<Lesson, int>>> i: program) {
        vector<vector<pair<int, Lesson>>> sched;

        for (pair<Lesson, int> j: i.second) {
            for (int d = 0; d < 6; d++) {
                for (int l = 0; l < 8; l++) {
                    if (teachers[j.second].time[d][l]) {
 //                       sched.push_back();
                    }
                }
            }

        }

        schedule[i.first] = sched;
    }

    fout.close();
    return 0;
}
