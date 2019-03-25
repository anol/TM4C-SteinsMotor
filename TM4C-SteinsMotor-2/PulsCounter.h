/*
 * PulsCounter.h
 *
 *  Created on: 25. mar. 2019
 *      Author: Drift
 */

#ifndef PULSCOUNTER_H_
#define PULSCOUNTER_H_

#include <string>

class PulsCounter
{
public:
    PulsCounter(const std::string& name);
    virtual ~PulsCounter();
    void Initialize();
    uint32_t GetCount();
};

#endif /* PULSCOUNTER_H_ */
