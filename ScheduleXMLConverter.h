//
// Created by mikha on 11.04.2021.
//

#ifndef SCHEDULEMAKER__SCHEDULEXMLCONVERTER_H_
#define SCHEDULEMAKER__SCHEDULEXMLCONVERTER_H_

#include "Schedule.h"
class ScheduleXMLConverter : public ScheduleConverter{
 public:
  void save(const std::string& path, const Schedule& schedule) const override;
 private:
  int FORMATTER_STEP = 4;
};

#endif //SCHEDULEMAKER__SCHEDULEXMLCONVERTER_H_
