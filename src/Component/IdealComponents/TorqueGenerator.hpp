/*
 * @file TorqueGenerator.hpp
 * @brief Ideal component which can generate for control algorithm test
 */
#pragma once

#include <Component/Abstract/ComponentBase.h>
#include <Dynamics/Dynamics.h>
#include <Interface/LogOutput/Logger.h>

#include <Library/math/NormalRand.hpp>
#include <Library/math/Vector.hpp>

/*
 * @class TorqueGenerator
 * @brief Ideal component which can generate for control algorithm test
 */
class TorqueGenerator : public ComponentBase, public ILoggable {
 public:
  /**
   * @fn TorqueGenerator
   * @brief Constructor
   * @param [in] prescaler: Frequency scale factor for update
   * @param [in] clock_gen: Clock generator
   * @param [in] magnitude_error_standard_deviation_N: Standard deviation of magnitude error [N]
   * @param [in] direction_error_standard_deviation_rad: Standard deviation of direction error [rad]
   * @param [in] dynamics: Dynamics information
   */
  TorqueGenerator(const int prescaler, ClockGenerator* clock_gen, const double magnitude_error_standard_deviation_N,
                 const double direction_error_standard_deviation_rad, const Dynamics* dynamics);
  /**
   * @fn ~TorqueGenerator
   * @brief Destructor
   */
  ~TorqueGenerator();

  // Override functions for ComponentBase
  /**
   * @fn MainRoutine
   * @brief Main routine to calculate torque generation
   */
  void MainRoutine(int count);
  /**
   * @fn PowerOffRoutine
   * @brief Power off routine to stop torque generation
   */
  void PowerOffRoutine();

  // Override ILoggable
  /**
   * @fn GetLogHeader
   * @brief Override GetLogHeader function of ILoggable
   */
  virtual std::string GetLogHeader() const;
  /**
   * @fn GetLogValue
   * @brief Override GetLogValue function of ILoggable
   */
  virtual std::string GetLogValue() const;

  // Getter
  /**
   * @fn GetGeneratedTorque_b_N
   * @brief Return generated torque in the body fixed frame [N]
   */
  inline const Vector<3> GetGeneratedTorque_b_N() const { return generated_torque_b_N_; };
  /**
   * @fn GetGeneratedTorque_i_N
   * @brief Return generated torque in the inertial frame [N]
   */
  inline const Vector<3> GetGeneratedTorque_i_N() const { return generated_torque_i_N_; };
  /**
   * @fn GetGeneratedTorque_rtn_N
   * @brief Return generated torque in the RTN frame [N]
   */
  inline const Vector<3> GetGeneratedTorque_rtn_N() const { return generated_torque_rtn_N_; };

  // Setter
  /**
   * @fn SetTorque_b_N
   * @brief Set ordered torque in the body fixed frame [N]
   */
  inline void SetTorque_b_N(const libra::Vector<3> torque_b_N) { ordered_torque_b_N_ = torque_b_N; };
  /**
   * @fn SetTorque_i_N
   * @brief Set ordered torque in the inertial frame [N]
   */
  void SetTorque_i_N(const libra::Vector<3> torque_i_N);
  /**
   * @fn SetTorque_rtn_N
   * @brief Set ordered torque in the RTN frame [N]
   */
  void SetTorque_rtn_N(const libra::Vector<3> torque_rtn_N);

 protected:
  libra::Vector<3> ordered_torque_b_N_{0.0};      //!< Ordered torque in the body fixed frame [N]
  libra::Vector<3> generated_torque_b_N_{0.0};    //!< Generated torque in the body fixed frame [N]
  libra::Vector<3> generated_torque_i_N_{0.0};    //!< Generated torque in the inertial frame [N]
  libra::Vector<3> generated_torque_rtn_N_{0.0};  //!< Generated torque in the RTN frame [N]

  // Noise
  libra::NormalRand magnitude_noise_;              //!< Normal random for magnitude noise
  libra::NormalRand direction_noise_;              //!< Normal random for direction noise
  double direction_error_standard_deviation_rad_;  //!< Standard deviation of direction error [rad]

  /**
   * @fn GenerateDirectionNoiseQuaternion
   * @brief Generate direction noise quaternion
   * @param [in] true_direction: True direction
   * @param [in] error_standard_deviation_rad: Standard deviation of direction error [rad]
   */
  libra::Quaternion GenerateDirectionNoiseQuaternion(libra::Vector<3> true_direction, const double error_standard_deviation_rad);

  const Dynamics* dynamics_;  //!< Spacecraft dynamics information
};