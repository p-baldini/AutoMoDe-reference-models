/**
 * @file <src/ReferenceModel3DotS.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package demiurge-epuck-dao
 * 
 * @license MIT License
 */
#include "ReferenceModel3DotS.hpp"

/***********************************************/
/***********************************************/

ReferenceModel3DotS::ReferenceModel3DotS() {
    m_pcRng = CRandom::CreateRNG("argos");
    m_fMaxVelocity = 12;
    m_fLeftWheelVelocity = 0;
    m_fRightWheelVelocity = 0;
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::Reset() {
    m_fLeftWheelVelocity = 0;
    m_fRightWheelVelocity = 0;

    // empty the data structures used until now
    m_sProximityInput.empty();
    m_sGroundInput = CCI_EPuckGroundSensor::SReadings();
    m_sCameraInput = CCI_EPuckOmnidirectionalCameraSensor::SReadings();
}

/***********************************************/
/***********************************************/

CCI_EPuckProximitySensor::TReadings ReferenceModel3DotS::GetProximityInput() const {
    return m_sProximityInput;
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::SetProximityInput(CCI_EPuckProximitySensor::TReadings s_prox_input) {
    m_sProximityInput = s_prox_input;
}

/***********************************************/
/***********************************************/

CCI_EPuckGroundSensor::SReadings ReferenceModel3DotS::GetGroundInput() {
    return m_sGroundInput;
}

/***********************************************/
/***********************************************/

Real ReferenceModel3DotS::GetGroundReading() {
    return m_sGroundInput.Center;
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::SetGroundInput(CCI_EPuckGroundSensor::SReadings s_ground_input) {
    m_sGroundInput = s_ground_input;
}

/***********************************************/
/***********************************************/

const UInt8 ReferenceModel3DotS::GetMessageToSend() const {
    return m_cMessage;
}

/***********************************************/
/***********************************************/

std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*>
ReferenceModel3DotS::GetRangeAndBearingMessages() {
    return m_pcRabMessageBuffer.GetMessages();
}

void ReferenceModel3DotS::SetRangeAndBearingMessages(
    CCI_EPuckRangeAndBearingSensor::TPackets s_packets
) {
    std::map<UInt32, CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> mapRemainingMessages;
    for (auto& it : s_packets) {
        if (it->Data[0] != m_unRobotIdentifier) {
            if (mapRemainingMessages.find(it->Data[0]) != mapRemainingMessages.end()) {  // If ID not in map, add message.
                mapRemainingMessages[it->Data[0]] = it;
            }
            else
            if (it->Bearing != CRadians::ZERO){  // If ID there, overwrite only if the message is valid (correct range and bearing information)
                mapRemainingMessages[it->Data[0]] = it;
            }
        }
    }
    for (auto& it : mapRemainingMessages) {
        m_pcRabMessageBuffer.AddMessage(it.second);
    }
    m_pcRabMessageBuffer.Update();
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::SetRangeAndBearingMessageToSend(UInt8 un_message) {
    m_cMessage = un_message;
}

/***********************************************/
/***********************************************/

CCI_EPuckOmnidirectionalCameraSensor::SReadings ReferenceModel3DotS::GetCameraInput() const {
    return m_sCameraInput;
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::SetCameraInput(
    CCI_EPuckOmnidirectionalCameraSensor::SReadings s_cam_input
) {
    m_sCameraInput = s_cam_input;
}

/***********************************************/
/***********************************************/

void ReferenceModel3DotS::SetLEDsColor(const CColor& c_color) {
    m_cLEDsColor = c_color;
}

/***********************************************/
/***********************************************/

const CColor& ReferenceModel3DotS::GetLEDsColor() const {
    return m_cLEDsColor;
}
