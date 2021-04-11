//
// Created by mikha on 11.04.2021.
//

#ifndef SCHEDULEMAKER__SCHEDULECONVERTER_H_
#define SCHEDULEMAKER__SCHEDULECONVERTER_H_

#include <string>
#include "Schedule.h"
class ScheduleConverter {
 public:
  ScheduleConverter() = default;
  virtual ~ScheduleConverter() = default;
  virtual void save(const std::string& path, const Schedule& schedule) {};
};

#endif //SCHEDULEMAKER__SCHEDULECONVERTER_H_
