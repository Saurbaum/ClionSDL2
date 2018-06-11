//
// Created by ian on 26/12/15.
//

#include "StateController.h"

StateController::StateController() = default;

StateController::~StateController() {
    m_machines.clear();
}

void StateController::Update(float updateInterval) {
    for (auto &m_machine : m_machines) {
        m_machine->Update(updateInterval);
    }
}

void StateController::CreateMachine(std::shared_ptr<IStateMachine> machine) {
    m_machines.push_back(machine);
}

void StateController::Render() {
    for (auto &m_machine : m_machines) {
        m_machine->Render();
    }
}
