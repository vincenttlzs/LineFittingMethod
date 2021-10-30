cmake_minimum_required( VERSION 2.8 )
project( zs_dbot_fitting )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# 添加cmake模块以使用ceres库
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# Ceres
find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )


# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_DIRS} )


include_directories(./include/)
aux_source_directory(./src/ SOURCE_DIR)
add_library(method SHARED  ${SOURCE_DIR})

add_executable( zs_dbot_fitting Example.cpp )
# 链接
target_link_libraries( zs_dbot_fitting ${CERES_LIBRARIES} ${OpenCV_LIBS} method)
