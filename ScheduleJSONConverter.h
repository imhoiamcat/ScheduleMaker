//
// Created by mikha on 11.04.2021.
//

#ifndef SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_
#define SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_

#include "ScheduleConverter.h"
#include "Schedule.h"
class ScheduleJSONConverter : ScheduleConverter {
 public:
  void save(const std::string& path, const Schedule& schedule) override;
};

#endif //SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_
