//
// Created by mikha on 11.04.2021.
//

#ifndef SCHEDULEMAKER__SCHEDULEXLSXCONVERTER_H_
#define SCHEDULEMAKER__SCHEDULEXLSXCONVERTER_H_

#include <string>
#include "Schedule.h"
class ScheduleXLSXConverter: public ScheduleConverter {
 public:
  void save(const std::string& path, const Schedule& schedule) const override;
 private:
  static string get_day(int day);
  static string get_coord(int x, int y);
  static pair<string, string> get_class_time(int class_num);
};

#endif //SCHEDULEMAKER__SCHEDULEXLSXCONVERTER_H_
