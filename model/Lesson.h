//
// Created by masha on 06.03.2021.
//

#ifndef SCHEDULEMAKER_LESSON_CLASS_H
#define SCHEDULEMAKER_LESSON_CLASS_H

class Lesson{
private:
    int teacher_;
    string subj_;
    bool tech_;
    bool eng_;
public:
    Lesson() {
        teacher_ = -1;
        subj_ = "";
        tech_ = false;
        eng_ = false;
    }
    Lesson(int teacher, string subj, bool tech, bool eng) {
        setTeacher(teacher);
        setSubj(subj);
        tech_ = tech;
        eng_ = eng;
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
    bool getTech() {
        return tech_;
    }
    bool getEng() {
        return eng_;
    }
};

#endif //SCHEDULEMAKER_LESSON_CLASS_H
