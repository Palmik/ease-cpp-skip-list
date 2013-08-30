# Copyright 2013 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Updated by: Petr Pilar

cmake_minimum_required(VERSION 2.6)

project(skip_list_bench CXX)

if(DEFINED ENV{GTEST_ROOT})
  set(GTEST_ROOT $ENV{GTEST_ROOT})
else()
  set(GTEST_ROOT "/usr/src/gtest")
endif()

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "-O2 -fmax-errors=1")

enable_testing()
include_directories(${GTEST_ROOT}/include)
link_directories(${GTEST_ROOT})
add_executable(skip_list_bench bench.cpp btree-google/btree_test_flags.cc)
target_link_libraries(skip_list_bench gflags gtest)

