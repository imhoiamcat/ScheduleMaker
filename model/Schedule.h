#ifndef SCHEDULEMAKER_SCHEDULE_H
#define SCHEDULEMAKER_SCHEDULE_H
#include <string>
#include <map>
#include "Teacher.h"
#include "model/Lesson.h"

using namespace std;

class ScheduleConverter;

class Schedule {
public:
    void load(const string& input_name);
    void make();
    void save(const string& output_name) const;
    void save(const string& output_name, const ScheduleConverter& converter) const;

    int teacherCount() {
        return teachers.size();
    }

    void removeLastTeacher() {
        for (auto &i: program) {
           auto j = i.second.begin();
           while (j!= i.second.end()) {
               if ((*j).first.getTeacher() == teacherCount()-1) {
                   j = i.second.erase(j);
               } else {
                   j++;
               }
           }
        }
        if (!teachers.empty()) {
            teachers.pop_back();
        }
    }

    Teacher & getTeacher(int n) const {
        return const_cast<Teacher &>(teachers.at(n));
    }

    void addTeacher(const string &string);

    void deleteTeacher(const string &string);

    const map<string, vector<vector<Lesson>>> &getSchedule() const;

private:
    map<string, vector<vector<Lesson>>> schedule;
    vector<Teacher> teachers;
    map<string, vector<pair<Lesson, int>>> program;
public:
    map<string, vector<pair<Lesson, int>>> &getProgram();
};

class ScheduleConverter {
public:
    ScheduleConverter() = default;
    virtual ~ScheduleConverter() = default;
    virtual void save(const std::string& path, const Schedule& schedule) const {};
};
#endif //SCHEDULEMAKER_SCHEDULE_H
