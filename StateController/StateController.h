//
// Created by ian on 26/12/15.
//

#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include <memory>
#include <vector>
#include "../Interface/IStateMachine.h"

class StateController {
public:
    StateController();
    ~StateController();

    void Update(float updateInterval);
    void CreateMachine(std::shared_ptr<IStateMachine> machine);
    void Render();

private:
    std::vector<std::shared_ptr<IStateMachine>> m_machines;
};


#endif //STATE_CONTROLLER_H
