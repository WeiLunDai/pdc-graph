test_dep = [lib_dep, dependency('gtest')]
test_inc = [inc, include_directories('include')]

subdir('include')
# subdir('src')

# node_test = executable('node_test', 'node_test.cc',
#                      include_directories : inc,
#                      dependencies : test_dep,
#                      link_with : graphDlib)

test_link = [graphDlib]

main_test = executable('main_test', 'main_test.cc',
                     include_directories : test_inc,
                     dependencies : test_dep,
                     link_with : test_link)

#test('graph test', graph_test)
test('main test', main_test)
