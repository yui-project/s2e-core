/**
 * @file sensor.hpp
 * @brief Base class for sensor emulation to add noises
 */

#ifndef S2E_COMPONENTS_BASE_SENSOR_HPP_
#define S2E_COMPONENTS_BASE_SENSOR_HPP_

#include <library/math/matrix.hpp>
#include <library/math/vector.hpp>
#include <library/randomization/normal_randomization.hpp>
#include <library/randomization/random_walk.hpp>

/**
 * @class Sensor
 * @brief Base class for sensor emulation to add noises
 * @note All sensors should inherit this class
 */
template <size_t N>
class Sensor {
 public:
  /**
   * @fn Sensor
   * @brief Constructor
   * @param [in] scale_factor: Scale factor matrix
   * @param [in] range_to_const_c: Output range limit to be constant output value at the component frame
   * @param [in] range_to_zero_c: Output range limit to be zero output value at the component frame
   * @param [in] bias_noise_c: Constant bias noise at the component frame
   * @param [in] normal_random_standard_deviation_c: Standard deviation of normal random noise at the component frame
   * @param [in] random_walk_step_width_s: Step width for random walk calculation [sec]
   * @param [in] random_walk_standard_deviation_c: Standard deviation of random wark at the component frame
   * @param [in] random_walk_limit_c: Limit of random walk at the component frame
   */
  Sensor(const libra::Matrix<N, N>& scale_factor, const libra::Vector<N>& range_to_const_c, const libra::Vector<N>& range_to_zero_c,
         const libra::Vector<N>& bias_noise_c, const libra::Vector<N>& normal_random_standard_deviation_c, const double random_walk_step_width_s,
         const libra::Vector<N>& random_walk_standard_deviation_c, const libra::Vector<N>& random_walk_limit_c);
  /**
   * @fn ~Sensor
   * @brief Destructor
   */
  ~Sensor();

 protected:
  /**
   * @fn Measure
   * @brief Return the observed data after adding the noise
   * @param [in] true_value_c: True value at the component frame
   * @return Observed value with noise at the component frame
   */
  libra::Vector<N> Measure(const libra::Vector<N> true_value_c);

 private:
  libra::Matrix<N, N> scale_factor_;            //!< Scale factor matrix
  libra::Vector<N> range_to_const_c_;           //!< Output range limit to be constant output value at the component frame
  libra::Vector<N> range_to_zero_c_;            //!< Output range limit to be zero output value at the component frame
  libra::Vector<N> bias_noise_c_;               //!< Constant bias noise at the component frame
  libra::NormalRand normal_random_noise_c_[N];  //!< Normal random
  RandomWalk<N> random_walk_noise_c_;           //!< Random Walk

  /**
   * @fn Clip
   * @brief Clipping according to the range information
   * @param [in] input_c: Input value at the component frame
   * @return Clipped value
   */
  libra::Vector<N> Clip(const libra::Vector<N> input_c);
  /**
   * @fn RangeCheck
   * @brief Check the range_to_const_c_ and range_to_zero_c_ is correct and fixed the values
   */
  void RangeCheck(void);
};

#include "./sensor_template_functions.hpp"

#endif  // S2E_COMPONENTS_BASE_SENSOR_HPP_
