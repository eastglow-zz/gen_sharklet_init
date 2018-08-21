#include "gen_sharklet_initApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<gen_sharklet_initApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

gen_sharklet_initApp::gen_sharklet_initApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  gen_sharklet_initApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  gen_sharklet_initApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  gen_sharklet_initApp::registerExecFlags(_factory);
}

gen_sharklet_initApp::~gen_sharklet_initApp() {}

void
gen_sharklet_initApp::registerApps()
{
  registerApp(gen_sharklet_initApp);
}

void
gen_sharklet_initApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"gen_sharklet_initApp"});
}

void
gen_sharklet_initApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"gen_sharklet_initApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
gen_sharklet_initApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
gen_sharklet_initApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
gen_sharklet_initApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
gen_sharklet_initApp__registerApps()
{
  gen_sharklet_initApp::registerApps();
}

extern "C" void
gen_sharklet_initApp__registerObjects(Factory & factory)
{
  gen_sharklet_initApp::registerObjects(factory);
}

extern "C" void
gen_sharklet_initApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  gen_sharklet_initApp::associateSyntax(syntax, action_factory);
}

extern "C" void
gen_sharklet_initApp__registerExecFlags(Factory & factory)
{
  gen_sharklet_initApp::registerExecFlags(factory);
}
