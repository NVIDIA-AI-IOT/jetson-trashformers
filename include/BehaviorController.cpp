#include "BehaviorController.h"

BehaviorController::BehaviorController(SerialHandler* serialHandler) {
    m_zigb  = serialHandler->GetZigbController();
    m_serialHandler = serialHandler;
}

BehaviorController::~BehaviorController() {

}

void BehaviorController::ChangeState(ControllerState state) {
    m_serialHandler->OpenZigbPort(); 
    switch(state) {
        default: 
            m_zigb->SendCommand(0);
            break;
        case ControllerState::WALK_FORWARD:
            m_zigb->SendCommand(BUTTON_WALK_FORWARD);
            break;
        case ControllerState::WALK_BACKWARD:
            m_zigb->SendCommand(BUTTON_WALK_BACKWARD);
            break;
        case ControllerState::TURN_RIGHT:
            m_zigb->SendCommand(BUTTON_TURN_RIGHT);
            break;    
        case ControllerState::TURN_LEFT:
            m_zigb->SendCommand(BUTTON_TURN_LEFT);
            break;
    }
}
