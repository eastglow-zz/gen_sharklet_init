[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 100
  ny = 100
  nz = 40
  # nx = 12
  # ny = 12
  # nz = 6
  # xmax = 96
  # ymax = 96
  # zmax = 48
  xmax = 100
  ymax = 100
  zmax = 40
  elem_type = HEX8
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

[Functions]
  [./image_func]
    type = ImageFunction
    file_base = sharklet_images_stack/shkstack
    file_suffix = png
    file_range = '0 39'
    component = 0  # the function value will be brought from 'red' color component
    scale = 0.00392156862   #  = 1/255
  [../]
[]

[ICs]
  [./c_ic]
    type = FunctionIC
    function = image_func
    variable = c
  [../]
  [./T_ic]
    type = ConstantIC
    variable = T
    value = 298
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
  [./gradEterm]
    type = ACInterface
    variable = c
    mob_name = L
    kappa_name = kappa0
  [../]
  [./doublewellterm]
    type = AllenCahn
    variable = c
    f_name = fbulk
    mob_name = L
  [../]

  [./Tdot]
    type = TimeDerivative
    variable = T
  [../]
[]

[Materials]
  [./constants]
    type = GenericConstantMaterial
    prop_names =  'L kappa0 w0'
    prop_values = '1 1      1'
  [../]
  [./doublewellfunction]
    type = DerivativeParsedMaterial
    f_name = fbulk
    material_property_names = 'w0'
    args = 'c'
    function = 'w0*c^2*(1-c)^2'
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

  # petsc_options_iname = '-pc_type -pc_factor_mat_solver_package'
  # petsc_options_value = 'lu superlu_dist'
  petsc_options_iname = '-pc_type -pc_asm_overlap'
  petsc_options_value = 'asm      1'
  # num_steps = 1
  dt = 0.1
  start_time = -1
  end_time = 0

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
  #show_var_residual = true
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
[]
