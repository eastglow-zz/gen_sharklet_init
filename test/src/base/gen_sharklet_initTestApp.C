//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "gen_sharklet_initTestApp.h"
#include "gen_sharklet_initApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<gen_sharklet_initTestApp>()
{
  InputParameters params = validParams<gen_sharklet_initApp>();
  return params;
}

gen_sharklet_initTestApp::gen_sharklet_initTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  gen_sharklet_initApp::registerObjectDepends(_factory);
  gen_sharklet_initApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  gen_sharklet_initApp::associateSyntaxDepends(_syntax, _action_factory);
  gen_sharklet_initApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  gen_sharklet_initApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    gen_sharklet_initTestApp::registerObjects(_factory);
    gen_sharklet_initTestApp::associateSyntax(_syntax, _action_factory);
    gen_sharklet_initTestApp::registerExecFlags(_factory);
  }
}

gen_sharklet_initTestApp::~gen_sharklet_initTestApp() {}

void
gen_sharklet_initTestApp::registerApps()
{
  registerApp(gen_sharklet_initApp);
  registerApp(gen_sharklet_initTestApp);
}

void
gen_sharklet_initTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
gen_sharklet_initTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
gen_sharklet_initTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
gen_sharklet_initTestApp__registerApps()
{
  gen_sharklet_initTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
gen_sharklet_initTestApp__registerObjects(Factory & factory)
{
  gen_sharklet_initTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
gen_sharklet_initTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  gen_sharklet_initTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
gen_sharklet_initTestApp__registerExecFlags(Factory & factory)
{
  gen_sharklet_initTestApp::registerExecFlags(factory);
}
