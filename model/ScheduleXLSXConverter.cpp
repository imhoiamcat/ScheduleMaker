//
// Created by masha on 08.05.2021.
//

#include <headers/XLDocument.hpp>
#include <headers/XLSheet.hpp>
#include "ScheduleXLSXConverter.h"

using namespace OpenXLSX;

void ScheduleXLSXConverter::save(const string &path, const Schedule &schedule) const {
    XLDocument doc;
    doc.create(path);
    auto wks = doc.workbook().worksheet("Расписание");
    int x = 1;
    int y = 1;
    for (int d = 0; d < DAYS; d++) {
        auto day = get_day(d);
        wks.cell(XLCellReference(get_excel_coord(x, y))).value() = day.first;
        y++;
        wks.cell(XLCellReference(get_excel_coord(x, y))).value() = "время";
        x += 3;
        wks.cell(XLCellReference(get_excel_coord(x, y))).value() = day.second;
        x -= 3;
        y++;
        for (int l = 0; l < LESSONS; l++) {
            auto time = get_lesson_time(l);
            wks.cell(XLCellReference(get_excel_coord(x, y))).value() = time.first;
            x++;
            wks.cell(XLCellReference(get_excel_coord(x, y))).value() = "-";
            x++;
            wks.cell(XLCellReference(get_excel_coord(x, y))).value() = time.second;
            x++;
            wks.cell(XLCellReference(get_excel_coord(x, y))).value() = l + 1;
            x -= 3;
            y++;
        }
        int old_y = y;
        int old_x = x;
        x += 3;
        y -= LESSONS;
        auto it = schedule.getSchedule().begin();
        for (int k = 0; k < schedule.getSchedule().size(); k++) {
            pair<string, vector<vector<Lesson>>> current_class = {it->first, it->second};
            x++;
            for (int l = 0; l < LESSONS; l++) {
                if (current_class.second[d][l].getTeacher() != -1) {
                    auto teacher = schedule.getTeacher(current_class.second[d][l].getTeacher());
                    string class_info = current_class.second[d][l].getSubj() + ", " + teacher.getName();
                    wks.cell(XLCellReference(get_excel_coord(x, y))).value() = class_info;
                }
                y++;
            }
            y -= (LESSONS + 1);
            wks.cell(XLCellReference(get_excel_coord(x, y))).value() = current_class.first;
            y++;
            x++;
            if (k < schedule.getSchedule().size() - 1) {
                for (int j = 0; j < 8; j++) {
                    wks.cell(XLCellReference(get_excel_coord(x, y))).value() = j + 1;
                    y++;
                }
                it++;
                y -= 9;
                wks.cell(XLCellReference(get_excel_coord(x, y))).value() = day.second;
                y++;
            }
        }
        x = old_x;
        y = old_y;
    }
    doc.save();
}

string ScheduleXLSXConverter::get_excel_coord(int x, int y) const {
    stringstream out;
    while (x > 0) {
        out << (char)('A' + x % 27 - 1);
        x /= 27;
    }
    out << to_string(y);
    out.flush();
    return out.str();
}

pair<string, string> ScheduleXLSXConverter::get_lesson_time(int lesson_num) const {
    switch (lesson_num) {
        case 0:
            return {"8:30", "9:10"};
        case 1:
            return {"9:15", "9:55"};
        case 2:
            return {"10:05", "10:45"};
        case 3:
        case 4:
        case 5:
        case 6:
            return {to_string(lesson_num + 7) + ":55", to_string(lesson_num + 8) + ":35"};
        case 7:
            return {"14:50", "15:30"};
        case 8:
            return {"15:35", "16:15"};
        default:
            return {"", ""};
    }
}

pair<string, string> ScheduleXLSXConverter::get_day(int day) const {
    switch (day) {
        case 0:
            return make_pair("Понедельник", "Пн");
        case 1:
            return make_pair("Вторник", "Вт");
        case 2:
            return make_pair("Среда", "Ср");
        case 3:
            return make_pair("Четверг", "Чт");
        case 4:
            return make_pair("Пятница", "Пт");
        case 5:
            return make_pair("Суббота", "Сб");
        case 6:
            return make_pair("Воскресенье", "Вс");
        default:
            return make_pair("", "");
    }
}
