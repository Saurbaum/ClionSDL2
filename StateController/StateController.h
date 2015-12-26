//
// Created by ian on 26/12/15.
//

#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include <vector>
#include "../Interface/IStateMachine.h"

class StateController {
public:
    StateController();
    ~StateController();

    void Update(float updateInterval);
    void CreateMachine(IStateMachine* machine);
    void Render();

private:
    std::vector<IStateMachine*> m_machines;
};


#endif //STATE_CONTROLLER_H
