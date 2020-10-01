# link_directories(
#     ${GTKMM_LIBRARY_DIRS}
#     ${GVC_LIBRARY_DIRS})

# include_directories(
#     ${GTKMM_INCLUDE_DIRS}
#     ${GVC_INCLUDE_DIRS})

add_library(graphD SHARED graph.cc gui.cc)

target_link_libraries(graphD
     ${GTKMM_LIBRARIES}
     ${GVC_LIBRARIES})
