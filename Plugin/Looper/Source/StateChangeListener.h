#pragma once
#include "States.h"

/**
 * @brief 
 * This is an interface to be implemented be classes that want to 
 * get notified in case of changes of the application state.
 */

class StateChangeListener
{
public:
    virtual ~StateChangeListener() = default;
    virtual void stateChanged(ApplicationState newState) = 0;
};