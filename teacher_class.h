//
// Created by masha on 06.03.2021.
//

#ifndef SCHEDULEMAKER_TEACHER_CLASS_H
#define SCHEDULEMAKER_TEACHER_CLASS_H
#include <iostream>
#include <utility>

using namespace std;

class Teacher {
private:
    string name_;
    vector<vector<int>> time_;
public:
    Teacher() {
        setName("");
        vector<vector<int>> tmp;
        setTime(tmp);
    }
    Teacher(string name, vector<vector<int>> time) {
        setName(std::move(name));
        setTime(std::move(time));
    }
    ~Teacher() = default;
    void setName(string name) {
        name_ = std::move(name);
    }
    void setTime(vector<vector<int>> time) {
        time_ = std::move(time);
    }
    string getName() {
        return name_;
    }
    vector<vector<int>>&  getTime(){
        return time_;
    }
};

#endif //SCHEDULEMAKER_TEACHER_CLASS_H
