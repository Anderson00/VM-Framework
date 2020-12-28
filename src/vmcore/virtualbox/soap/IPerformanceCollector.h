#ifndef IPERFORMACE_COLLECTOR_H
#define IPERFORMACE_COLLECTOR_H

#include "IObject.h"

class IPerformanceCollector : public IObject{
public:
    IPerformanceCollector(std::string key) : IObject(key){}
private:
    
};

#endif