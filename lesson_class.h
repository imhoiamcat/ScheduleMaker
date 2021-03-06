//
// Created by masha on 06.03.2021.
//

#ifndef SCHEDULEMAKER_LESSON_CLASS_H
#define SCHEDULEMAKER_LESSON_CLASS_H

class Lesson{
private:
    int teacher_;
    string subj_;
public:
    Lesson() {
        teacher_ = -1;
        subj_ = "";
    }
    Lesson(int teacher, string subj) {
        setTeacher(teacher);
        setSubj(subj);
    }
    ~Lesson() = default;
    void setTeacher(int teacher) {
        teacher_ = teacher;
    }
    void setSubj(string subj) {
        subj_ = subj;
    }
    int getTeacher() {
        return teacher_;
    }
    string getSubj() {
        return subj_;
    }
};

#endif //SCHEDULEMAKER_LESSON_CLASS_H
