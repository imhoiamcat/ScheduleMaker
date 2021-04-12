//
// Created by mikha on 11.04.2021.
//

#include <fstream>
#include "ScheduleJSONConverter.h"
void ScheduleJSONConverter::save(const string &path, const Schedule &schedule) const {
  std::ofstream output(path);
  output << "{" << endl;
  int level = 2;
  output << string(level, ' ') << "\"Grades\": [" << endl;
  auto it = schedule.getSchedule().begin();
  level += 2;
  for (int k = 0; k < schedule.getSchedule().size(); k++) {
    pair<string, vector<vector<Lesson>>> s = make_pair(it->first, it->second);
    it++;
    output << string(level, ' ') << "{" << endl;
    level += 2;
    output << string(level, ' ') << "\"grade\": " << "\"" << s.first << "\"" << "," << endl;
    output << string(level, ' ') << "\"WeekSchedule\": " << "[" << endl;
    level += 2;
    for (int i = 0; i < 6; i++) {
      output << string(level, ' ') << "{" << endl;
      level += 2;
      output << string(level, ' ') << "\"Day\": " << "\"" << i << "\"," << endl;
      output << string(level, ' ') << "\"Classes\": " << "[" << endl;
      level += 2;
      for (int j = 0; j < 8; j++) {
        output << string(level, ' ') << "{" << endl;
        level += 2;
        output << string(level, ' ') << "\"ClassNumber\": " << "\"" << j << "\"";
        if (s.second[i][j].getTeacher() != -1) {
          output << "," << endl;
          output << string(level, ' ') << "\"SubjectName\": " << "\"" << s.second[i][j].getSubj() << "\"," << endl;
          output << string(level, ' ') << "\"Teacher\": " << endl << schedule.getTeacher(s.second[i][j].getTeacher()).toJSON(level);
        } else {
          output << endl;
        }
        level -= 2;
        if (j < 7) {
          output << string(level, ' ') << "}," << endl;
        } else {
          output << string(level, ' ') << "}" << endl;
        }
      }
      level -= 2;
      output << string(level, ' ') << "]" << endl;
      level -= 2;
      if (i < 5) {
        output << string(level, ' ') << "}," << endl;
      } else {
        output << string(level, ' ') << "}" << endl;
      }
    }
    level -= 2;
    output << string(level, ' ') << "]" << endl;
    level -= 2;
    if (k < schedule.getSchedule().size() - 1) {
      output << string(level, ' ') << "}," << endl;
    } else {
      output << string(level, ' ') << "}" << endl;
    }
  }
  level -= 2;
  output << string(level, ' ') << "]" << endl;
  level -= 2;
  output << string(level, ' ') << "}" << endl;
  output.close();
}
