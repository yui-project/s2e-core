/**
 * @file simple_disturbance.hpp
 * @brief Abstract class for a disturbance
 * @note It is better to use this abstract class for all disturbances, but it is difficult. (e.g. Gravity between spacecraft.)
 * In the difficult case, users need to use the Disturbance class directory.
 */

#ifndef S2E_DISTURBANCES_SIMPLE_DISTURBANCE_HPP_
#define S2E_DISTURBANCES_SIMPLE_DISTURBANCE_HPP_

#include "../dynamics/dynamics.hpp"
#include "../environment/local/local_environment.hpp"
#include "disturbance.hpp"

/**
 * @class SimpleDisturbance
 * @brief Abstract class for a disturbance
 */
class SimpleDisturbance : public Disturbance, public ILoggable {
 public:
  /**
   * @fn SimpleDisturbance
   * @brief Constructor
   * @param [in] is_calc_enabled: Calculation flag
   */
  SimpleDisturbance(const bool is_calc_enabled = true) : Disturbance(is_calc_enabled) {}

  /**
   * @fn ~SimpleDisturbance
   * @brief Destructor
   */
  virtual ~SimpleDisturbance() {}

  /**
   * @fn UpdateIfEnabled
   * @brief Update calculated disturbance when the calculation flag is true
   */
  virtual inline void UpdateIfEnabled(const LocalEnvironment& local_env, const Dynamics& dynamics) {
    if (is_calc_enabled_) {
      Update(local_env, dynamics);
    } else {
      force_b_N_ *= 0;
      torque_b_Nm_ *= 0;
    }
  }

  /**
   * @fn Update
   * @brief Pure virtual function to define the disturbance calculation
   */
  virtual void Update(const LocalEnvironment& local_env, const Dynamics& dynamics) = 0;
};

#endif  // S2E_DISTURBANCES_SIMPLE_DISTURBANCE_HPP_
