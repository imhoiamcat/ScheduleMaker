//
// Created by mikha on 11.04.2021.
//

#include "ScheduleXLSXConverter.h"
#include <lib/headers/XLDocument.hpp>
#include <OpenXLSX.hpp>

using namespace OpenXLSX;

void ScheduleXLSXConverter::save(const string &path, const Schedule &schedule) const {
  XLDocument doc;
  doc.create(path);
  auto wks = doc.workbook().worksheet("Sheet1");
  int x = 1;
  int y = 1;
  for (int i = 0; i < 6; i++) {
    auto day = get_day(i);
    wks.cell(XLCellReference(get_coord(x, y))).value() = day.first;
    y++;
    wks.cell(XLCellReference(get_coord(x, y))).value() = "время";
    x += 3;
    wks.cell(XLCellReference(get_coord(x, y))).value() = day.second;
    x -= 3;
    y++;
    for (int j = 0; j < 8; j++) {
      auto time = get_class_time(j);
      wks.cell(XLCellReference(get_coord(x, y))).value() = time.first;
      x++;
      wks.cell(XLCellReference(get_coord(x, y))).value() = "-";
      x++;
      wks.cell(XLCellReference(get_coord(x, y))).value() = time.second;
      x++;
      wks.cell(XLCellReference(get_coord(x, y))).value() = j + 1;
      x -= 3;
      y++;
    }
    int old_y = y;
    int old_x = x;
    x += 3;
    y -= 8;
    auto it = schedule.getSchedule().begin();
    for (int k = 0; k < schedule.getSchedule().size(); k++) {
      pair<string, vector<vector<Lesson>>> s = make_pair(it->first, it->second);
      x++;
      for (int j = 0; j < 8; j++) {
        if (s.second[i][j].getTeacher() != -1) {
          auto teacher = schedule.getTeacher(s.second[i][j].getTeacher());
          string class_info = s.second[i][j].getSubj() + ", " + teacher.getFullName();
          wks.cell(XLCellReference(get_coord(x, y))).value() = class_info;
        }
        y++;
      }
      y -= 9;
      wks.cell(XLCellReference(get_coord(x, y))).value() = s.first;
      y++;
      x++;
      if (k < schedule.getSchedule().size() - 1) {
        for (int j = 0; j < 8; j++) {
          wks.cell(XLCellReference(get_coord(x, y))).value() = j + 1;
          y++;
        }
        it++;
        y -= 9;
        wks.cell(XLCellReference(get_coord(x, y))).value() = day.second;
        y++;
      }
    }
    x = old_x;
    y = old_y;
  }
  doc.save();
}

pair<string, string> ScheduleXLSXConverter::get_day(int day) {
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

string ScheduleXLSXConverter::get_coord(int x, int y) {
  stringstream out;
  while (x > 0) {
    out << (char)('A' + x % 27 - 1);
    x /= 27;
  }
  out << to_string(y);
  out.flush();
  return out.str();
}
pair<string, string> ScheduleXLSXConverter::get_class_time(int class_num) {
  switch (class_num) {
    case 0:
      return make_pair("8:30", "9:10");
    case 1:
      return make_pair("9:15", "9:55");
    case 2:
      return make_pair("10:05", "10:45");
    case 3:
    case 4:
    case 5:
    case 6:
      return make_pair(to_string(class_num + 7) + ":55", to_string(class_num + 8) + ":35");
    case 7:
      return make_pair("14:50", "15:30");
    case 8:
      return make_pair("15:35", "16:15");
    default:
      return make_pair("", "");
  }
}
