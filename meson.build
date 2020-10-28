# project info
project('graphDisplay', 'cpp',
  version : '1.0.0',
  license : 'MIT')

# project arguments
add_global_arguments('-DSOME_TOKEN=value -g', language : 'cpp')

# project main dependencies
lib_dep = [dependency('gtkmm-3.0'), dependency('libgvc')]

# include directory
inc = include_directories('include')

# sub directory
subdir('include')
subdir('src')
subdir('test')

# graphDlib output as pkg mode
pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : graphDlib,
                  version : '1.0',
                  name : 'libgraphD',
                  filebase : 'gui_tree',
                  description : 'Graph display lib')

configure_file(input : 'builder.ui',
               output : 'builder.ui',
               copy : true)

install_data('builder.ui')

# program entry point
executable('graphDisplay', 'hello_main.cc',
           include_directories : inc,
           dependencies : lib_dep,
           link_with : graphDlib,
           install : true)
