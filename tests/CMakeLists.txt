#@author S. V. Paulauskas
add_executable(unittest-Variable unittest-Variable.cpp)
target_link_libraries(unittest-Variable UnitTest++)
install(TARGETS unittest-Variable DESTINATION bin/)