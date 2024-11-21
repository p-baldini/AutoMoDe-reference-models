/**
 * @file <src/core/EpuckDAO.h>
 * 
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 * 
 * @brief This class represents the status of the robot.
 *        It contains the input variables (the sensor inputs) and
 *        the output variables (the values for the wheel actuators),
 *        as well as the setters and getters to access them.
 *
 *        Only one object of this class should be instantiated, and
 *        is to be used as a bridge between the AutoMoDeController and
 *        the AutoMoDeFiniteStateMachine classes. In AutoMoDeController,
 *        the variables of the object shall be updated at each time step.
 *        The different modules of the  AutoMoDeFiniteStateMachine will
 *        then use the input variables and update the output variables
 *        accordingly.
 */
#ifndef EPUCK_DAO_H
#define EPUCK_DAO_H

#include <vector>
#include <deque>

#include <argos3/core/utility/math/rng.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wheels_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_range_and_bearing_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_rgb_leds_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_proximity_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_light_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_ground_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_omnidirectional_camera_sensor.h>

namespace argos {
	class EpuckDAO {
		public:

			virtual ~EpuckDAO();

			/*
			 * Reset function.
			 */
			virtual void Reset() = 0;

			/*
			 * Setter for the wheels velocity.
			 */
			void SetWheelsVelocity(const Real& un_left_velocity, const Real& un_right_velocity);

			/*
			 * Setter for the wheels velocity.
			 */
			void SetWheelsVelocity(const CVector2& c_velocity_vector);

			/*
			 * Getter for the right wheel velocity.
			 */
			const Real& GetRightWheelVelocity() const;

			/*
			 * Getter for the left wheel velocity.
			 */
			const Real& GetLeftWheelVelocity() const;

			/*
			 * Setter for the robot identifier.
			 */
			void SetRobotIdentifier(const UInt32& un_robot_id);

			/*
			 * Getter for the robot identifier.
			 */
			const UInt32& GetRobotIdentifier() const;

			/*
			 * Getter for the maximal wheels velocity.
			 */
			const Real& GetMaxVelocity() const;

			/*
			 * Getter for the random number generator.
			 */
			CRandom::CRNG* GetRandomNumberGenerator() const;


			/*************************************************************************************/
			/* Virtual classes                                                                   */
			/*************************************************************************************/

			/**
			 * Getter for the proximity input. Launch a warning if used without proper
			 * implementation. Available for RM 1.1, 2.1, 2.2, 3.s.
			 */
			virtual CCI_EPuckProximitySensor::TReadings GetProximityInput() const {
				LOG << "Method 'GetProximityInput' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				CCI_EPuckProximitySensor::TReadings emptyReadings;
				return emptyReadings;
			};

			/**
			 * Getter for the proximity reading: a single value summarizing the proximity. Launch a
			 * warning if used without proper implementation. Available for RM 1.2, 2.0, 2.3, 3.0.
			 */
			virtual CCI_EPuckProximitySensor::SReading GetProximityReading() {
				LOG << "Method 'GetProximityReading' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckProximitySensor::SReading();
			};

			/**
			 * Setter for the proximity input. If not re-implemented by the subclass it does
			 * nothing.
			 */
			virtual void SetProximityInput(CCI_EPuckProximitySensor::TReadings s_prox_input) {};

			/**
			 * Getter for the light input. Launch a warning if used without proper
			 * implementation. Available for RM 1.1, 2.1, 2.2.
			 */
			virtual CCI_EPuckLightSensor::TReadings GetLightInput() const {
				LOG << "Method 'GetLightInput' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				CCI_EPuckLightSensor::TReadings emptyReadings;
				return emptyReadings;
			};

			/**
			 * Getter for the light input: a single value summarizing the light. Launch a warning
			 * if used without proper implementation. Available for RM 1.2, 2.0, 2.3, 3.0.
			 */
			virtual CCI_EPuckLightSensor::SReading GetLightReading() {
				LOG << "Method 'GetLightReading' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckLightSensor::SReading();
			};

			/**
			 * Setter for the light input. If not re-implemented by the subclass it does nothing.
			 */
			virtual void SetLightInput(CCI_EPuckLightSensor::TReadings s_light_input) {};

			/**
			 * Getter for the ground input. Launch a warning if used without proper
			 * implementation. Available for RM 1.1, 2.1, 2.2, 3.s.
			 */
			virtual CCI_EPuckGroundSensor::SReadings GetGroundInput() { 
				LOG << "Method 'GetGroundInput' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				CCI_EPuckGroundSensor::SReadings emptyReadings;
				return emptyReadings;
			};

			/**
			 * Getter for the ground input: a single value summarizing the ground color. Launch a
			 * warning if used without proper implementation. Available for RM 1.2, 2.0, 2.3, 3.0,
			 * 3.s.
			 */
			virtual Real GetGroundReading() {																 // RM 1.2
				return 0.0f;
			};

			/**
			 * Setter for the ground input. If not re-implemented by the subclass it does nothing.
			 */
			virtual void SetGroundInput(CCI_EPuckGroundSensor::SReadings s_ground_input) {};

			/**
			 * Getter for the number of surrounding robots. Launch a warning if used without proper
			 * implementation. Available for RM 1.1, 1.2, 2.0, 2.1, 2.2, 2.3, 3.0.
			 */
			virtual const UInt8 GetNumberNeighbors() const {
				LOG << "Method 'GetNumberNeighbors' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return 0;
			};

			/**
			 * Getter for the message to send. Launch a warning if used without proper
			 * implementation. Available for RM 2.0, 2.1, 2.2, 2.3, 3.s.
			 */
			virtual const UInt8 GetMessageToSend() const {
				LOG << "Method 'GetMessageToSend' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return 0;
			};

			/**
			 * Getter for the range-and-bearing messages. Launch a warning if used without proper
			 * implementation. Available for RM 1.1, 1.2, 2.0, 2.1, 2.2, 2.3, 3.0, 3.s.
			 */
			virtual std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*>
			GetRangeAndBearingMessages() {
				LOG << "Method 'GetRangeAndBearingMessages' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*>();
			};

			/**
			 * Getter for the number of messaging neighbors. Launch a warning if used without
			 * proper implementation. Available for RM 2.0, 2.1, 2.2, 2.3.
			 */
			virtual UInt8 GetNumberMessagingNeighbors(UInt8 un_message) {
				LOG << "Method 'GetNumberMessagingNeighbors' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return 0;
			};

			/**
			 * Getter for the difference of number between the messages that the robot got. Launch
			 * a warning if used without proper implementation. Available for RM 2.0, 2.1, 2.2, 2.3.
			 */
			virtual SInt8 GetDiffMessagingNeighbors(UInt8 un_message, UInt8 un_message2) {
				LOG << "Method 'GetDiffMessagingNeighbors' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return 0;
			};

			/**
			 * Getter for attraction force to the neighbors computed with RaB messages. Launch a
			 * warning if used without proper implementation. Available for RM 1.2, 2.0, 2.1, 2.2,
			 * 2.3, 3.0.
			 */
			virtual CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetAttractionVectorToNeighbors(
				Real f_alpha_parameter
			) {
				LOG << "Method 'GetAttractionVectorToNeighbors' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckRangeAndBearingSensor::SReceivedPacket();
			};

			/**
			 * Getter for the vector representing the attraction force to the neighbors that are
			 * sending a message computed with RaB messages. Launch a warning if used without
			 * proper implementation. Available for RM 2.0, 2.1, 2.2, 2.3.
			 */
			virtual CCI_EPuckRangeAndBearingSensor::SReceivedPacket
			GetAttractionVectorToMessagingNeighbors(Real f_alpha_parameter, UInt8 un_message) {
				LOG << "Method 'GetAttractionVectorToMessagingNeighbors' of "
					<< typeid(*this).name() << " not properly implemented." << std::endl;
				return CCI_EPuckRangeAndBearingSensor::SReceivedPacket();
			};

			/**
			 * Getter for the center of mass of neighbors computed with RaB messages. Launch a
			 * warning if used without proper implementation. Available for RM 1.1, 2.1.
			 */
			virtual CCI_EPuckRangeAndBearingSensor::SReceivedPacket GetNeighborsCenterOfMass() {
				LOG << "Method 'GetNeighborsCenterOfMass' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckRangeAndBearingSensor::SReceivedPacket();
			};

			/**
			 * Getter for the center of mass of messaging neighbors computed with RaB messages.
			 * Launch a warning if used without proper implementation. No RMs currently implements
			 * it.
			 */
			virtual CCI_EPuckRangeAndBearingSensor::SReceivedPacket
			GetMessagingNeighborsCenterOfMass(UInt8 un_message) {
				LOG << "Method 'GetMessagingNeighborsCenterOfMass' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckRangeAndBearingSensor::SReceivedPacket();
			};

			/**
			 * Setter for the number of surrounding robots. If not re-implemented by the subclass
			 * it does nothing.
			 */
			virtual void SetNumberNeighbors(const UInt8& un_number_neighbors) {};

			/**
			 * Setter for the range-and-bearing input. If not re-implemented by the subclass it
			 * does nothing.
			 */
			virtual void SetRangeAndBearingMessages(CCI_EPuckRangeAndBearingSensor::TPackets s_packets) {};

			/** 
			 * Setter for the message to send with range and bearing. If not re-implemented by the
			 * subclass it does nothing.
			 */
			virtual void SetRangeAndBearingMessageToSend(UInt8 un_message) {};

			/**
			 * Getter for the camera input. Launch a warning if used without proper implementation.
			 * Available for RM 3.0, 3.s.
			 */
			virtual CCI_EPuckOmnidirectionalCameraSensor::SReadings GetCameraInput() const {
				LOG << "Method 'GetCameraInput' of " << typeid(*this).name()
					<< " not properly implemented." << std::endl;
				return CCI_EPuckOmnidirectionalCameraSensor::SReadings();
			}

			/**
			 * Setter for the camera input. If not re-implemented by the subclass it does nothing.
			 */
			virtual void SetCameraInput(
				CCI_EPuckOmnidirectionalCameraSensor::SReadings s_cam_input
			) {};

			/**
			 * Setter for the RGB LEDs color. If not re-implemented by the subclass it does
			 * nothing.
			 */
			virtual void SetLEDsColor(const CColor& c_color) {};

			/**
			 * Getter for the RGB LEDs color. As it is the output to control an actuator, it has a
			 * default value set to BLACK.
			 */
			virtual const CColor& GetLEDsColor() const {
				return CColor::BLACK;
			}

		protected:
			/**
			 * The left wheel velocity (output variable).
			 */
			Real m_fLeftWheelVelocity;

			/**
			 * The right wheel velocity (output variable).
			 */
			Real m_fRightWheelVelocity;

			/**
			 * The maximal wheels velocity.
			 */
			Real m_fMaxVelocity;

			/**
			 * The robot identifier.
			 */
			UInt32 m_unRobotIdentifier;

			/**
			 * Pointer to the random number generator.
			 */
			CRandom::CRNG* m_pcRng;
	};
}

#endif /* EPUCK_DAO_H */
