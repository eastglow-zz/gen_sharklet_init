//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html



#include "WeightedDiffusion.h"

registerMooseObject("PhaseFieldApp", WeightedDiffusion);

template <>
InputParameters
validParams<WeightedDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Calculates a general form of div(M(var)grad(var))");
  params.addParam<Real>("prefactor",1,"The prefacror used with the kernel, a constant");
  params.addParam<MaterialPropertyName>("mob_name","M","Mobility as a function of variable, which can be provided by DerivativeParsedMaterial with derivative_order 1");
  params.addCoupledVar("coupled_vars", "Names of the coupled variables");
  return params;
}

WeightedDiffusion::WeightedDiffusion(const InputParameters & parameters)
  : DerivativeMaterialInterface<Kernel>(parameters),
  _nvar(_coupled_moose_vars.size()),
  _jvar2cvar(_nvar+1),
  _cvars(coupledComponents("coupled_vars")),
  _L(getParam<Real>("prefactor")),
  _M(getMaterialProperty<Real>("mob_name")),
  _dM_dcvars(coupledComponents("coupled_vars"))
{

  /// Get derivative data:
  /// _dM_dcvars
  for (unsigned int i = 0; i < _dM_dcvars.size(); ++i)
  {
    const VariableName iname = getVar("coupled_vars", i)->name();
    if (iname == _var.name())
      paramError("coupled_vars entry error",\
                 "WeightedDiffusion: The kernel variable should not be specified in the coupled parameter.");

    /// The 1st derivatives
    _dM_dcvars[i] = &getMaterialPropertyDerivative<Real>("mob_name", iname);
  }

  for (unsigned int i = 0; i < _cvars.size(); ++i)
  {
    _cvars[i] = coupled("coupled_vars", i);
    _jvar2cvar[_cvars[i]] = i;
    printf("!!! Kernel:WeightedDiffusion: _cvars[%d] = %d, _jvar2cvar[%d] = %d \n", i, _cvars[i], _cvars[i], _jvar2cvar[_cvars[i]]);
  }
}

void
WeightedDiffusion::initialSetup()
{
  validateCoupling<Real>("coupled_vars");
}

Real
WeightedDiffusion::computeQpResidual()
{
  return _L * _M[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
WeightedDiffusion::computeQpJacobian()
{
  return _L * _M[_qp] * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

Real
WeightedDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real returnval = 0.0;
  returnval = _L * ((*_dM_dcvars[_jvar2cvar[jvar]])[_qp] * _phi[_j][_qp]) * (_grad_u[_qp] * _grad_test[_i][_qp]);
  return returnval;
}
