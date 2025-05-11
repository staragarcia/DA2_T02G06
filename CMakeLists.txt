cmake_minimum_required(VERSION 3.15)
project(KnapsackSolver)

set(CMAKE_CXX_STANDARD 17)

# OR-Tools paths (adjust if needed)
set(ORTOOLS_ROOT ${CMAKE_SOURCE_DIR}/ortools)
include_directories(${ORTOOLS_ROOT}/include)
link_directories(${ORTOOLS_ROOT}/lib)

add_executable(knapsack main.cpp)

# Link against OR-Tools and dependencies
target_link_libraries(knapsack
  ortools
  protobuf
  absl_raw_hash_set
  absl_hashtablez_sampler
  absl_synchronization
)
