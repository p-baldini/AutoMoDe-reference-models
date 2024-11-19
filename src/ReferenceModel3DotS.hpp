/**
 * @file <src/ReferenceModel3DotS.hpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package demiurge-epuck-dao
 * 
 * @license MIT License
 */
#ifndef REFERENCE_MODEL_3_S_H
#define REFERENCE_MODEL_3_S_H

#include "EpuckDAO.h"
#include "RabMessageBuffer.h"

using namespace argos;

class ReferenceModel3DotS : public EpuckDAO {
    public:
        /**
         * Class constructor.
         */
        ReferenceModel3DotS();

        /**
         * Reset function.
         */
        void Reset();

        /**
         * Return the proximity values perceived by the robot. For each sensor return the angle
         * according to the robot and the intensity of the perceived signal.
         * 
         * @return A vector of 24 proximity values and directions as perceived by the robot.
         */
        CCI_EPuckProximitySensor::TReadings GetProximityInput() const;

        /**
         * Not implemented. Calling the method will cause an argos exception.
         */
        CCI_EPuckProximitySensor::SReading GetProximityReading() override {
            THROW_ARGOSEXCEPTION("Method 'GetProximityReading' not available");
        };

        /**
         * Set the proximity reading of the robot.
         * 
         * @param[in] s_prox_input The vector of 24 proximity values and angles.
         */
        void SetProximityInput(CCI_EPuckProximitySensor::TReadings s_prox_input);

        /**
         * Not implemented as not compatible with the use of the camera. Calling the method will
         * cause an argos exception.
         */
        CCI_EPuckLightSensor::TReadings GetLightInput() const override {
            THROW_ARGOSEXCEPTION("Method 'GetLightInput' not available");
        };

        /**
         * Not implemented as not compatible with the use of the camera. Calling the method will
         * cause an argos exception.
         */
        CCI_EPuckLightSensor::SReading GetLightReading() override {
            THROW_ARGOSEXCEPTION("Method 'GetLightReading' not available");
        };

        /**
         * Return the ground values perceived by the robot. For each sensor return the intensity
         * of the perceived signal.
         * 
         * @return A structure containing 3 ground values as perceived by the robot.
         */
        CCI_EPuckGroundSensor::SReadings GetGroundInput();

        /**
         * Return the ground value perceived by the central ground sensor of the robot.
         * 
         * @return The value perceived by the central ground sensor.
         */
        Real GetGroundReading();

        /**
         * Set the ground reading of the robot.
         * 
         * @param[in] s_prox_input A structure containing the 3 ground values.
         */
        void SetGroundInput(CCI_EPuckGroundSensor::SReadings s_ground_input);

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. Calling
         * the method will cause an argos exception.
         */
        const UInt8 GetNumberNeighbors() const override {
            THROW_ARGOSEXCEPTION("Method 'GetNumberNeighbors' not available");
        };

        /**
         * Getter for the Range and Bearing message to be sent: a byte.
         * 
         * @return The byte to be sent with the RAB.
         */
        const UInt8 GetMessageToSend() const;

        /**
         * The set of messages (bytes) received through the Range and Bearing.
         * 
         * @return The messages received through the RAB.
         */
        std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> GetRangeAndBearingMessages();

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. We
         * imagine the messages to be sent by entities other than the robots. Calling the method
         * will cause an argos exception.
         */
        UInt8 GetNumberMessagingNeighbors(UInt8 un_message) override {
            THROW_ARGOSEXCEPTION("Method 'GetNumberMessagingNeighbors' not available");
        };

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. We
         * imagine the messages to be sent by entities other than the robots. Calling the method
         * will cause an argos exception.
         */
        SInt8 GetDiffMessagingNeighbors(UInt8 un_message, UInt8 un_message2) override {
            THROW_ARGOSEXCEPTION("Method 'GetDiffMessagingNeighbors' not available");
        }

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. Calling
         * the method will cause an argos exception.
         */
        CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetAttractionVectorToNeighbors(
            Real f_alpha_parameter
        ) override {
            THROW_ARGOSEXCEPTION("Method 'GetAttractionVectorToNeighbors' not available");
        }

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. We
         * imagine the messages to be sent by entities other than the robots. Calling the method
         * will cause an argos exception.
         */
        CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetAttractionVectorToMessagingNeighbors(
            Real f_alpha_parameter, UInt8 un_message
        ) override {
            THROW_ARGOSEXCEPTION("Method 'GetAttractionVectorToMessagingNeighbors' not available");
        };

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. Calling
         * the method will cause an argos exception.
         */
        CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetNeighborsCenterOfMass() override {
            THROW_ARGOSEXCEPTION("Method 'GetNeighborsCenterOfMass' not available");
        };

        /**
         * Not implemented as the RM 3.S is though to be used on single robot experiments. We
         * imagine the messages to be sent by entities other than the robots. Calling the method
         * will cause an argos exception.
         */
        CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetMessagingNeighborsCenterOfMass(
            UInt8 un_message
        ) override {
            THROW_ARGOSEXCEPTION("Method 'GetMessagingNeighborsCenterOfMass' not available");
        };

        /**
         * Set the received messages from other entities received through the Range and Bearing.
         * 
         * @param[in] s_packets The byte messages received through the RAB.
         */
        void SetRangeAndBearingMessages(CCI_EPuckRangeAndBearingSensor::TPackets s_packets);

        /**
         * Set the byte message to send through the Range and Bearing.
         * 
         * @param[in] un_message The message to broadcast through the RAB.
         */
        void SetRangeAndBearingMessageToSend(UInt8 un_message);

        /**
         * Return the perceived blob of color perceived through the camera and the time at which
         * they were perceived.
         * 
         * @return A vector of color perception data.
         */
        CCI_EPuckOmnidirectionalCameraSensor::SReadings GetCameraInput() const;

        /**
         * Set the vector containing the perceived colors and the time at which they were
         * perceived.
         * 
         * @param[in] s_cam_input The set of colors perceived by the robot.
         */
        void SetCameraInput(CCI_EPuckOmnidirectionalCameraSensor::SReadings s_cam_input);

        /**
         * Set the color that the RGB LEDs of the robot should assume.
         * 
         * @param[in] c_color The color that the robot must assume.
         */
        void SetLEDsColor(const CColor& c_color);

        /**
         * Return the current color of the robot RGB LEDs.
         * 
         * @return The current color of the robot. 
         */
        const CColor& GetLEDsColor() const;

    private:
        CCI_EPuckProximitySensor::TReadings m_sProximityInput;          ///< The proximity sensors
                                                                        ///< input. Each contains
                                                                        ///< intensity and angle of
                                                                        ///< the signal.
        CCI_EPuckGroundSensor::SReadings m_sGroundInput;                ///< The ground sensors
                                                                        ///< input. Each contains
                                                                        ///< the raw perceived
                                                                        ///< value of the sensors.
        CCI_EPuckOmnidirectionalCameraSensor::SReadings m_sCameraInput; ///< The camera sensor
                                                                        ///< input. Contains the
                                                                        ///< blob of colors
                                                                        ///< perceived and the
                                                                        ///< perception instant.
        CColor m_cLEDsColor;                                            ///< The color of RGB LEDs
                                                                        ///< of the robot. Output
                                                                        ///< variable.
        RabMessageBuffer m_pcRabMessageBuffer;                          ///< Pointer to the RAB
                                                                        ///< messages buffer.
        UInt8 m_cMessage;                                               ///< The message to
                                                                        ///< broadcast with the
                                                                        ///< RAB.
};

#endif /* REFERENCE_MODEL_3_S_H */
