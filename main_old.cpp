#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "teacher_class.h"
#include "lesson_class.h"

using namespace std;

map<string, vector<vector<Lesson>>> schedule;
vector<Teacher> teachers;
map<string, vector<pair<Lesson, int>>> program;

bool cmp(int i, int j, int d) {
    return teachers[i].can(d) > teachers[j].can(d);
}

void makeSchedule() {
    Lesson none = Lesson();

    for (pair<string, vector<pair<Lesson, int>>> i: program) {
        vector<vector<Lesson>> sched;
        sched.resize(6);
        vector<pair<Lesson, int>> tmp = i.second;
        for (pair<Lesson, int> j: tmp) {
            for (int d = 0; d < 6; d++) {
                sched[d].resize(8, none);
                for (int l = 0; l < 8; l++) {
                    if (teachers[j.first.getTeacher()].getTime()[d][l] && j.second > 0) {
                        sched[d][l] = j.first;
                        j.second--;
                    }
                }
            }

        }
        schedule[i.first] = sched;
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    //0. Enter number of teachers
    int n, m;
    fin >> n;
    teachers.resize(n);

    //1. Enter list of teachers
    string tmp_name;
    vector<vector<int>> tmp_time;
    for (int i = 0; i < n; i++) {
        fin >> tmp_name;
        tmp_time.resize(6);
        for (int k = 0; k < 6; k++) {
            tmp_time[k].resize(8);
            for (int j = 0; j < 8; j++) {
                fin >> tmp_time[k][j];
            }
        }
        teachers[i] = Teacher(tmp_name, tmp_time);
    }

    //2. Print list of teachers
    for (int i = 0; i < n; i++) {
        fout << teachers[i].getName() << endl;
        for (int k = 0; k < 6; k++) {
            for (int j: teachers[i].getTime()[k]) {
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
    Lesson tmp_lesson = Lesson();
    string tmp_subj;
    int tmp_teacher;
    int sub, c;
    for (int i = 0; i < g; i++) {
        fin >> s >> sub;
        for (int j = 0; j < sub; j++) {
            fin >> tmp_subj >> tmp_teacher >> c;
            tmp_lesson = Lesson(tmp_teacher, tmp_subj);
            program[s].push_back({tmp_lesson, c});
        }
    }

    //5. Print program for each grade
    for (pair<string, vector<pair<Lesson, int>>> i: program) {
        fout << i.first << endl;
        for (pair<Lesson, int> j: i.second) {
            fout << j.first.getSubj() << " " << teachers[j.first.getTeacher()].getName() << " " << j.second << endl;
        }
    }

    makeSchedule();

    for (pair<string, vector<vector<Lesson>>> s: schedule) {
        fout << s.first << endl;
        for (int i = 0; i < 6; i++) {
            fout << "Day " << i << endl;
            for (int j = 0; j < 8; j++) {
                fout << j << ": ";
                if (s.second[i][j].getTeacher() != -1) {
                    fout << s.second[i][j].getSubj() << " " << teachers[s.second[i][j].getTeacher()].getName();
                }
                fout << endl;
            }
        }
        fout << endl;
    }
    fout.close();
    return 0;
}
