/**
 * @file sample_components.hpp
 * @brief An example of user side components management installed on a spacecraft
 */

#ifndef S2E_SIMULATION_SPACECRAFT_SAMPLE_SPACECRAFT_SAMPLE_COMPONENTS_H_
#define S2E_SIMULATION_SPACECRAFT_SAMPLE_SPACECRAFT_SAMPLE_COMPONENTS_H_

#include <components/cdh/OBC.h>
#include <components/power/PCU.h>

#include <Library/math/Vector.hpp>
#include <components/communication/InitAntenna.hpp>
#include <components/ideal_components/InitializeForceGenerator.hpp>
#include <components/ideal_components/InitializeTorqueGenerator.hpp>
#include <components/propulsion/InitSimpleThruster.hpp>
#include <components/aocs/initialize_gnss_receiver.hpp>
#include <components/aocs/initialize_gyro_sensor.hpp>
#include <components/aocs/initialize_magnetometer.hpp>
#include <components/aocs/initialize_magnetorquer.hpp>
#include <components/aocs/InitRwModel.hpp>
#include <components/aocs/InitStt.hpp>
#include <components/aocs/InitSunSensor.hpp>
#include <components/examples/example_change_structure.hpp>
#include <components/examples/example_i2c_controller_for_hils.hpp>
#include <components/examples/example_i2c_target_for_hils.hpp>
#include <components/examples/example_serial_communication_for_hils.hpp>
#include <dynamics/dynamics.hpp>
#include <interface/hils/hils_port_manager.hpp>
#include <simulation/spacecraft/structure/structure.hpp>

#include "../installed_components.hpp"

class OBC;
class PCU;
class Gyro;
class MagSensor;
class STT;
class SunSensor;
class GNSSReceiver;
class MagTorquer;
class RWModel;
class SimpleThruster;
class ForceGenerator;
class TorqueGenerator;

/**
 * @class SampleComponents
 * @brief An example of user side components management class
 */
class SampleComponents : public InstalledComponents {
 public:
  /**
   * @fn SampleComponents
   * @brief Constructor
   */
  SampleComponents(const Dynamics* dynamics, Structure* structure, const LocalEnvironment* local_env, const GlobalEnvironment* glo_env,
                   const SimulationConfig* config, ClockGenerator* clock_gen, const int sat_id);
  /**
   * @fn ~SampleComponents
   * @brief Destructor
   */
  ~SampleComponents();

  // Override functions for InstalledComponents
  /**
   * @fn GenerateForce_N_b
   * @brief Return force generated by components in unit Newton in body fixed frame
   */
  libra::Vector<3> GenerateForce_N_b();
  /**
   * @fn GenerateTorque_Nm_b
   * @brief Return torque generated by components in unit Newton-meter in body fixed frame
   */
  libra::Vector<3> GenerateTorque_Nm_b();
  /**
   * @fn LogSetup
   * @brief Setup the logger for components
   */
  void LogSetup(Logger& logger);

  // Getter
  inline Antenna& GetAntenna() const { return *antenna_; }

 private:
  PCU* pcu_;                            //!< Power Control Unit
  OBC* obc_;                            //!< Onboard Computer
  HilsPortManager* hils_port_manager_;  //!< Port manager for HILS test

  // AOCS
  Gyro* gyro_;                         //!< Gyro sensor
  MagSensor* mag_sensor_;              //!< Magnetmeter
  STT* stt_;                           //!< Star sensor
  SunSensor* sun_sensor_;              //!< Sun sensor
  GNSSReceiver* gnss_;                 //!< GNSS receiver
  MagTorquer* mag_torquer_;            //!< Magnetorquer
  RWModel* rw_;                        //!< Reaction Wheel
  SimpleThruster* thruster_;           //!< Thruster
  ForceGenerator* force_generator_;    //!< Ideal Force Generator
  TorqueGenerator* torque_generator_;  //!< Ideal Torque Generator

  // CommGs
  Antenna* antenna_;  //!< Antenna

  // Examples
  // ExampleChangeStructure* change_structure_;  //!< Change structure
  /*
  ExampleSerialCommunicationForHils* exp_hils_uart_responder_;  //!< Example of HILS UART responder
  ExampleSerialCommunicationForHils* exp_hils_uart_sender_;     //!< Example of HILS UART sender
  ExampleI2cControllerForHils* exp_hils_i2c_controller_;        //!< Example of HILS I2C controller
  ExampleI2cTargetForHils* exp_hils_i2c_target_;                //!< Example of HILS I2C target
  */

  // States
  const SimulationConfig* config_;     //!< Simulation settings
  const Dynamics* dynamics_;           //!< Dynamics information of the spacecraft
  Structure* structure_;               //!< Structure information of the spacecraft
  const LocalEnvironment* local_env_;  //!< Local environment information around the spacecraft
  const GlobalEnvironment* glo_env_;   //!< Global environment information
};

#endif  // S2E_SIMULATION_SPACECRAFT_SAMPLE_SPACECRAFT_SAMPLE_COMPONENTS_H_
