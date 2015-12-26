//
// Created by ian on 26/12/15.
//

#ifndef I_STATE_MACHINE_H
#define I_STATE_MACHINE_H

class IStateMachine {
public:
    virtual void Update(float updateInterval) = 0;

    virtual void Render() = 0;
};


#endif //I_STATE_MACHINE_H
