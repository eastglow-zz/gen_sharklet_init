//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef GEN_SHARKLET_INITAPP_H
#define GEN_SHARKLET_INITAPP_H

#include "MooseApp.h"

class gen_sharklet_initApp;

template <>
InputParameters validParams<gen_sharklet_initApp>();

class gen_sharklet_initApp : public MooseApp
{
public:
  gen_sharklet_initApp(InputParameters parameters);
  virtual ~gen_sharklet_initApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void registerObjectDepends(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void associateSyntaxDepends(Syntax & syntax, ActionFactory & action_factory);
  static void registerExecFlags(Factory & factory);
};

#endif /* GEN_SHARKLET_INITAPP_H */
