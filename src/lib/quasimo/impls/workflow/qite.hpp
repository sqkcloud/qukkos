/*******************************************************************************
 * Copyright (c) 2018-, UT-Battelle, LLC.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the MIT License 
 * which accompanies this distribution. 
 *
 * Contributors:
 *   Alexander J. McCaskey - initial API and implementation
 *   Thien Nguyen - implementation
 *******************************************************************************/
#pragma once
#include "qukkos_qsim.hpp"

namespace qukkos {
namespace QuaSiMo {
class QiteWorkflow : public QuantumSimulationWorkflow {
protected:
  std::vector<std::shared_ptr<xacc::IRTransformation>> extra_circuit_optimizers;
  
public:
  virtual bool initialize(const HeterogeneousMap &params) override;
  virtual QuantumSimulationResult
  execute(const QuantumSimulationModel &model) override;

  virtual const std::string name() const override { return "qite"; }
  virtual const std::string description() const override { return ""; }

private:
  HeterogeneousMap config_params;
};
} // namespace QuaSiMo
} // namespace qukkos