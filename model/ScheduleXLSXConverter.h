//
// Created by masha on 08.05.2021.
//

#ifndef SCHEDULEMAKER_SCHEDULEXLSXCONVERTER_H
#define SCHEDULEMAKER_SCHEDULEXLSXCONVERTER_H


#include "Schedule.h"

class ScheduleXLSXConverter: public ScheduleConverter {
public:
    void save(const std::string& path, const Schedule& schedule) const override;
private:
    const int DAYS = 6;
    const int LESSONS = 8;
    string get_excel_coord(int x, int y) const;
    pair<string, string> get_lesson_time(int lesson_num) const;
    pair<string, string> get_day(int day) const;
};


#endif //SCHEDULEMAKER_SCHEDULEXLSXCONVERTER_H
