[Mesh]
  type = GeneratedMesh
  dim = 3
  nx = 100
  ny = 100
  nz = 40
  xmax = 100
  ymax = 100
  zmax = 40
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./image_func]
    type = ImageFunction
    #file_base = sharklet_images_stack/shkstack
    file_base = rods_images_stack/RodsRef
    file_suffix = png
    file_range = '0 39'
    component = 0  # the function value will be brought from 'red' color component
    scale = 0.00392156862   #  = 1/255
  [../]
[]

[ICs]
  [./u_ic]
    type = FunctionIC
    function = image_func
    variable = u
  [../]
[]

[Kernels]
  [./udot]
    type = TimeDerivative
    variable = u
  [../]
  [./gradEterm]
    type = ACInterface
    variable = u
    mob_name = L
    kappa_name = kappa0
  [../]
  [./doublewellterm]
    type = AllenCahn
    variable = u
    f_name = fbulk
    mob_name = L
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
    args = 'u'
    function = 'w0*u^2*(1-u)^2'
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
  end_time = 1
[]

[Outputs]
  exodus = true
[]
