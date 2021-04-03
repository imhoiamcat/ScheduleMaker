#ifndef SCHEDULEMAKER_SCHEDULE_H
#define SCHEDULEMAKER_SCHEDULE_H
#include <string>
#include <map>
#include "Teacher.h"
#include "Lesson.h"

using namespace std;

class Schedule {
public:
    void load(const string& input_name);
    void make();
    void save(const string& output_name);

    int teacherCount() {
        return teachers.size();
    }

    void removeLastTeacher() {
        if (!teachers.empty()) {
            teachers.pop_back();
        }
    }

    Teacher& getTeacher(int n) {
        return teachers.at(n);
    }

    void addTeacher(const string &string);

    const map<string, vector<vector<Lesson>>> &getSchedule() const;

private:
    map<string, vector<vector<Lesson>>> schedule;
    vector<Teacher> teachers;
    map<string, vector<pair<Lesson, int>>> program;
public:
    const map<string, vector<pair<Lesson, int>>> &getProgram() const;
};


#endif //SCHEDULEMAKER_SCHEDULE_H
