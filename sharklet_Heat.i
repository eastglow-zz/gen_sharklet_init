
#Length unit: micrometer
#Time unit: second
#Mass unit: kilogram
#Heat conductivity: [kg*um/K/s^3]
#  -Relation between [kg*m/K/s^3] and [kg*um/K/s^3]:
#   [kg*um/K/s^3] = 1e6 * [kg*m/K/s^3]
#kV: Heat conductivity of dry air @ 300K [kg*um/K/s^3]
#kS: Hear conductivity of Si @ 300K [kg*um/K/s^3]

[Mesh]
  type = FileMesh
  file = sharklet_Heat_init_out.e
  # xmax = 100  # um
  # ymax = 100  # um
  # zmax = 40  # um
[]

[Variables]
  #Phase-field
  [./c]
    order = FIRST
    family = LAGRANGE
  [../]
  #Temperature
  [./T]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[UserObjects]
  [./ICs_c_T]
    type = SolutionUserObject
    mesh = sharklet_Heat_init_out.e
    timestep = 'LATEST'
    execute_on = 'initial'
  [../]
[]

[ICs]
  [./c_ic]
    type = FunctionIC
    function = c_sharklet
    variable = c
  [../]
  [./T_ic]
    type = FunctionIC
    function = T_init
    variable = T
  [../]
[]

[Functions]
  [./c_sharklet]
    type = SolutionFunction
    solution = ICs_c_T
    from_variable = 'c'
  [../]
  [./T_init]
    type = SolutionFunction
    solution = ICs_c_T
    from_variable = 'T'
  [../]
[]

[BCs]
  [./T_bottom]
    type = DirichletBC
    variable = T
    boundary = 'back'
    value = 263
  [../]
  [./T_top]
    type = DirichletBC
    variable = T
    boundary = 'front'
    value = 298
  [../]
[]

[Kernels]
  [./cdot]
    type = TimeDerivative
    variable = c
  [../]

  [./Tdot]
    type = TimeDerivative
    variable = T
  [../]

  [./divFlux]
    type = WeightedDiffusion
    variable = T
    coupled_vars = 'c'
    mob_name = keff
    prefactor = 1
  [../]
[]

[Materials]
  [./constants]
    type = GenericConstantMaterial
    prop_names =  'kV      kS'
    # prop_values = '2.624e4 148e6'
    prop_values = '1 50'
  [../]

  [./heat_conductivity]
    type = DerivativeParsedMaterial
    f_name = keff
    material_property_names = 'kV kS hV(c) hS(c)'
    args = 'c'
    function = 'kV*hV + kS*hS'
    derivative_order = 2
    outputs = exodus
  [../]

  [./hV]
    type = DerivativeParsedMaterial
    f_name = hV
    args = 'c'
    constant_names = 'xi'
    constant_expressions = '0.1'
    function = '0.5+0.5*tanh((1-c-0/5)/xi)'
    derivative_order = 2
  [../]
  [./hS]
    type = DerivativeParsedMaterial
    f_name = hS
    args = 'c'
    constant_names = 'xi'
    constant_expressions = '0.1'
    function = '0.5+0.5*tanh((c-0/5)/xi)'
    derivative_order = 2
  [../]
[]

[Preconditioning]
  [./cw_coupling]
    type = SMP
    full = true
  #  type = FDP
  #  full = true
  [../]
[]


# [Problem]
#   type = FEProblem
#   solve = false
# [../]

[Executioner]
  type = Transient
  solve_type = PJFNK
  scheme = bdf2

  petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
  petsc_options_value = 'lu superlu_dist'
  # petsc_options_iname = '-pc_type -pc_asm_overlap'
  # petsc_options_value = 'asm      1'
  # num_steps = 1
  dt = 0.1
  # start_time = -1
  end_time = 10
  steady_state_detection = true
  # [./Adaptivity]
  #   initial_adaptivity = 3
  #   max_h_level = 3
  #   refine_fraction = 0.99
  #   coarsen_fraction = 0.001
  #   weight_names =  'c T'
  #   weight_values = '1 1'
  # [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
[]
