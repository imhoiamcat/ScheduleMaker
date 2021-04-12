//
// Created by mikha on 11.04.2021.
//

#include <fstream>
#include "ScheduleXMLConverter.h"
void ScheduleXMLConverter::save(const string &path, const Schedule &schedule) const {
  std::ofstream output(path);
  output << "<?xml version=\"1.0\"?>" << endl;
  int level = 0;
  output << string(level, ' ') << "<Grades>" << endl;
  auto it = schedule.getSchedule().begin();
  level += FORMATTER_STEP;
  for (int k = 0; k < schedule.getSchedule().size(); k++) {
    pair<string, vector<vector<Lesson>>> s = make_pair(it->first, it->second);
    it++;
    output << string(level, ' ') << "<Grade>" << endl;
    level += FORMATTER_STEP;
    output << string(level, ' ') << "<Name>" << "\"" << s.first << "\"" << "</Name>" << endl;
    output << string(level, ' ') << "<WeekSchedule>" << endl;
    level += FORMATTER_STEP;
    for (int i = 0; i < 6; i++) {
      output << string(level, ' ') << "<Schedule>" << endl;
      level += FORMATTER_STEP;
      output << string(level, ' ') << "<Day>" << "\"" << i << "\"" << "</Day>" << endl;
      output << string(level, ' ') << "<Classes>" << endl;
      level += FORMATTER_STEP;
      for (int j = 0; j < 8; j++) {
        output << string(level, ' ') << "<Class>" << endl;
        level += FORMATTER_STEP;
        output << string(level, ' ') << "<ClassNumber>" << "\"" << j << "\"" << "</ClassNumber>";
        if (s.second[i][j].getTeacher() != -1) {
          output << "," << endl;
          output << string(level, ' ') << "<SubjectName>" << "\"" << s.second[i][j].getSubj() << "\""  << "</SubjectName>" << endl;
          output << string(level, ' ') << endl << schedule.getTeacher(s.second[i][j].getTeacher()).toXML(level);
        } else {
          output << endl;
        }
        level -= FORMATTER_STEP;
        output << string(level, ' ') << "</Class>" << endl;
      }
      level -= FORMATTER_STEP;
      output << string(level, ' ') << "</Classes>" << endl;
      level -= FORMATTER_STEP;
      output << string(level, ' ') << "</Schedule>" << endl;
    }
    level -= FORMATTER_STEP;
    output << string(level, ' ') << "</WeekSchedule>" << endl;
    level -= FORMATTER_STEP;
    output << string(level, ' ') << "</Grade>" << endl;
  }
  level -= FORMATTER_STEP;
  output << string(level, ' ') << "</Grades>" << endl;
  output.close();
}
