#include <fstream>
#include <vector>
#include <string>
#include "Schedule.h"
#include "Teacher.h"

using namespace std;

void Schedule::load(const string &input_name) {
    ifstream fin(input_name);
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

    //3. Enter number of grades
    int g;
    fin >> g;

    //4. Enter program for each grade
    string s;
    Lesson tmp_lesson = Lesson();
    string tmp_subj;
    int tmp_teacher;
    int sub, c, tech, eng;
    for (int i = 0; i < g; i++) {
        fin >> s >> sub;
        for (int j = 0; j < sub; j++) {
            fin >> tmp_subj >> tmp_teacher >> c;
            tmp_lesson = Lesson(tmp_teacher, tmp_subj, 0, 0);
//            if (tech || eng) c*=2;
            program[s].push_back({tmp_lesson, c});
        }
    }

}

void Schedule::make() {
    Lesson none = Lesson();

    for (pair<string, vector<pair<Lesson, int>>> i: program) {
        vector<vector<Lesson>> sched;
        sched.resize(6);
        for (int d = 0; d < 6; d++) {
            sched[d].resize(8, none);
        }
        vector<pair<Lesson, int>> tmp = i.second;
        for (pair<Lesson, int> j : tmp) {
            for (int d = 0; d < 6; d++) {
                int cnt = 0;
                for (int l = 0; l < 8; l++) {
                    if (teachers[j.first.getTeacher()].getTime()[d][l] && j.second > 0 &&
                        sched[d][l].getSubj() == "" && cnt < 2) {
                        sched[d][l] = j.first;
                        j.second--;
                        cnt++;
                    }
                }
            }
        }
        schedule[i.first] = sched;
    }
}

void Schedule::save(const string &output_name) const {
    ofstream fout(output_name);
    fout << teachers.size() << endl;
    for (Teacher t: teachers) {
        fout << t.getName() << endl;
        for (int d = 0; d < 6; d++) {
            for (int l = 0; l < 8; l++) {
                fout << t.getTime()[d][l] << " ";
            }
            fout << endl;
        }
    }
    fout << program.size() << endl;
    for (pair<string, vector<pair<Lesson, int>>> grade: program) {
        fout << grade.first << endl;
        fout << grade.second.size() << endl;
        for (pair<Lesson, int> subj: grade.second) {
            fout << subj.first.getSubj() << " " << subj.first.getTeacher()
                 << " " << subj.second << endl;
        }
    }
    fout.close();
}

void Schedule::save(const string &output_name, const ScheduleConverter &converter) const {
    converter.save(output_name, *this);
}

void Schedule::addTeacher(const string &name) {
    Teacher t(name);
    teachers.push_back(t);
}

void Schedule::deleteTeacher(const string &name) {
    int i = 0;
    while (teachers[i].getName() != name && i < teachers.size()) {
        i++;
    }
    if (i < teachers.size()) {
        teachers.erase(teachers.begin() + i);
    }
}

map<string, vector<pair<Lesson, int>>> &Schedule::getProgram() {
    return program;
}

const map<string, vector<vector<Lesson>>> &Schedule::getSchedule() const {
    return schedule;
}
