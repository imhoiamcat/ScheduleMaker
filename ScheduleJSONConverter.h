//
// Created by mikha on 11.04.2021.
//

#ifndef SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_
#define SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_

#include "Schedule.h"

class ScheduleJSONConverter : public ScheduleConverter {
 public:
  void save(const std::string& path, const Schedule& schedule) const override;
};

#endif //SCHEDULEMAKER__SCHEDULEJSONCONVERTER_H_
