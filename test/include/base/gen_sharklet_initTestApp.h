//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef GEN_SHARKLET_INITTESTAPP_H
#define GEN_SHARKLET_INITTESTAPP_H

#include "MooseApp.h"

class gen_sharklet_initTestApp;

template <>
InputParameters validParams<gen_sharklet_initTestApp>();

class gen_sharklet_initTestApp : public MooseApp
{
public:
  gen_sharklet_initTestApp(InputParameters parameters);
  virtual ~gen_sharklet_initTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};

#endif /* GEN_SHARKLET_INITTESTAPP_H */
