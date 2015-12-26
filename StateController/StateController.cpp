//
// Created by ian on 26/12/15.
//

#include "StateController.h"

StateController::StateController() {

}

StateController::~StateController() {
    for(auto iterator = m_machines.begin(); iterator != m_machines.end(); ++iterator) {
        delete (*iterator);
    }
    m_machines.clear();
}

void StateController::Update(float updateInterval) {
    for(auto iterator = m_machines.begin(); iterator != m_machines.end(); ++iterator) {
        (*iterator)->Update(updateInterval);
    }
}

void StateController::CreateMachine(IStateMachine* machine) {
    m_machines.push_back(machine);
}

void StateController::Render() {
    for(auto iterator = m_machines.begin(); iterator != m_machines.end(); ++iterator) {
        (*iterator)->Render();
    }
}
