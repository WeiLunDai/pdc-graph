
# test source file
src_test = ['node_test.cc', 'edge_test.cc']

# generate shared library for test
# install isn't necessary
testlib = shared_library('graph_test',
    src_test, 
    include_directories : test_inc, 
    dependencies : test_dep,
    link_with : graphDlib)
    # install : true)
