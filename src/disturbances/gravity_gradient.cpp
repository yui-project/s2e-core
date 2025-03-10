/**
 * @file gravity_gradient.cpp
 * @brief Class to calculate the gravity gradient torque
 */

#include "gravity_gradient.hpp"

#include <cmath>
#include <environment/global/physical_constants.hpp>

#include "../library/logger/log_utility.hpp"

GravityGradient::GravityGradient(const bool is_calculation_enabled)
    : GravityGradient(environment::earth_gravitational_constant_m3_s2, is_calculation_enabled) {}

GravityGradient::GravityGradient(const double gravity_constant_m3_s2, const bool is_calculation_enabled)
    : Disturbance(is_calculation_enabled, true), gravity_constant_m3_s2_(gravity_constant_m3_s2) {}

void GravityGradient::Update(const LocalEnvironment& local_environment, const Dynamics& dynamics) {
  // TODO: use structure information to get inertia tensor
  CalcTorque_b_Nm(local_environment.GetCelestialInformation().GetCenterBodyPositionFromSpacecraft_b_m(),
                  dynamics.GetAttitude().GetInertiaTensor_b_kgm2());
}

libra::Vector<3> GravityGradient::CalcTorque_b_Nm(const libra::Vector<3> earth_position_from_sc_b_m,
                                                  const libra::Matrix<3, 3> inertia_tensor_b_kgm2) {
  double r_norm_m = earth_position_from_sc_b_m.CalcNorm();
  libra::Vector<3> u_b = earth_position_from_sc_b_m;  // TODO: make undestructive normalize function for Vector
  u_b /= r_norm_m;

  double coeff = 3.0 * gravity_constant_m3_s2_ / pow(r_norm_m, 3.0);
  torque_b_Nm_ = coeff * OuterProduct(u_b, inertia_tensor_b_kgm2 * u_b);
  return torque_b_Nm_;
}

std::string GravityGradient::GetLogHeader() const {
  std::string str_tmp = "";

  str_tmp += WriteVector("gravity_gradient_torque", "b", "Nm", 3);

  return str_tmp;
}

std::string GravityGradient::GetLogValue() const {
  std::string str_tmp = "";

  str_tmp += WriteVector(torque_b_Nm_);

  return str_tmp;
}
