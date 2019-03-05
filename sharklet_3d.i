[Mesh]
  type = GeneratedMesh
  dim = 3
  # nx = 12
  # ny = 12
  # nz = 5
  # xmax = 100
  # ymax = 100
  # zmax = 40
  nx = 12
  ny = 12
  nz = 16
  xmax = 4.8      # dx(=0.04) * nx * 2^(max_h_level)
  ymax = 4.8    # dy(=0.04) * ny * 2^(max_h_level)
  zmax = 5.12
[]

[Variables]
  [./u]
  [../]
[]

[Functions]
  [./image_func]
    type = ImageFunction
    file_base = sharklet_images_stack/shkstack
    file_suffix = png
    file_range = '0 255'
    component = 0
    scale = 0.00392156862
  [../]
[]

[ICs]
  [./u_ic]
    type = FunctionIC
    function = image_func
    variable = u
  [../]
[]

[Problem]
  type = FEProblem
  solve = false
[../]

[Executioner]
  type = Transient
  num_steps = 1
  dt = 0.1

  # adaptive mesh to resolve an interface
  [./Adaptivity]
    initial_adaptivity = 3
    max_h_level = 3
    refine_fraction = 0.99
    coarsen_fraction = 0.001
    weight_names =  'u'
    weight_values = '1'

  [../]
[]

[Outputs]
  exodus = true
[]
