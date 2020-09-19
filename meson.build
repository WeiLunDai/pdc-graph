project('c++ graph display by gtkmm ', 'cpp',
  version : '1.0.0',
  license : 'MIT')
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

lib_dep = [dependency('gtkmm-3.0'), dependency('cairomm-1.0')]

inc = include_directories('include')

subdir('include')
subdir('src')
#subdir('test')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : graphDlib,
                  version : '1.0',
                  name : 'libgraphD',
                  filebase : 'gui_tree',
                  description : 'Graph display lib')

executable('main', 'hello_main.cc',
           include_directories : inc,
           dependencies : lib_dep,
           link_with : graphDlib)
