/**
 * @file initialize_local_environment.hpp
 * @brief Initialize functions for local environment classes
 */

#ifndef S2E_ENVIRONMENT_LOCAL_INITIALIZE_LOCAL_ENVIRONMENT_HPP_
#define S2E_ENVIRONMENT_LOCAL_INITIALIZE_LOCAL_ENVIRONMENT_HPP_

#include <environment/local/atmosphere.hpp>
#include <environment/local/geomagnetic_field.hpp>
#include <environment/local/solar_radiation_pressure_environment.hpp>

/**
 * @fn InitMagEnvironment
 * @brief Initialize magnetic field of the earth
 * @param [in] ini_path: Path to initialize file
 */
GeomagneticField InitMagEnvironment(std::string ini_path);
/**
 * @fn InitSRPEnvironment
 * @brief Initialize solar radiation pressure
 * @param [in] ini_path: Path to initialize file
 * @param [in] local_celes_info: Local celestial information
 */
SRPEnvironment InitSRPEnvironment(std::string ini_path, LocalCelestialInformation* local_celes_info);
/**
 * @fn InitAtmosphere
 * @brief Initialize atmospheric density of the earth
 * @param [in] ini_path: Path to initialize file
 */
Atmosphere InitAtmosphere(std::string ini_path);

#endif  // S2E_ENVIRONMENT_LOCAL_INITIALIZE_LOCAL_ENVIRONMENT_HPP_
