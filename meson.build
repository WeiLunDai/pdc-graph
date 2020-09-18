project('c++ gtkmm project', 'cpp',
  version : '1.0.0',
  license : 'MIT')
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

lib_dep = dependency('gtkmm-3.0')

inc = include_directories('include')

subdir('include')
subdir('src')
subdir('test')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : hellolib,
                  version : '1.0',
                  name : 'libhello',
                  filebase : 'hello',
                  description : 'A hello lib')
