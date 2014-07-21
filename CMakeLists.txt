cmake_minimum_required(VERSION 2.8)

# add modules
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

# set version
set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "1")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# append git revision if available
include(get-git-revision)
get_git_revision(VERSION_GIT)
if(NOT "${VERSION_GIT}" STREQUAL "")
    set(VERSION "${VERSION}-${VERSION_GIT}")
endif()

message(STATUS "Configuring chaos-head version " ${VERSION})

# project name and language
project (chaos-head CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

# include version number in header
configure_file(${PROJECT_SOURCE_DIR}/src/version.hpp.in
    ${PROJECT_SOURCE_DIR}/src/version.hpp)

find_package(Boost REQUIRED COMPONENTS system)
find_package(SFML 2 REQUIRED COMPONENTS system window graphics)
find_package(GStreamer REQUIRED)
find_package(GLIB REQUIRED)
find_package(NPA REQUIRED)
find_package(NPENGINE REQUIRED)

# add libraries
include_directories(
    ${NPA_INCLUDE_DIR}
    ${NPENGINE_INCLUDE_DIR}
    ${GLIB_INCLUDE_DIRS}
)
link_directories(
    ${NPENGINE_LIBRARY_DIR}
    ${NPA_LIBRARY_DIR}
)

add_executable(chaos-head
    src/main.cpp
)
target_link_libraries(chaos-head
    npengine npa
    ${Boost_LIBRARIES}
    ${SFML_LIBRARIES}
    ${GSTREAMER_LIBRARIES} ${GSTREAMER_APP_LIBRARIES} ${GSTREAMER_VIDEO_LIBRARIES}
)

# install target
install(TARGETS chaos-head DESTINATION bin)

# create packages
set(CPACK_GENERATOR "TBZ2")
set(CPACK_PACKAGE_VERSION ${VERSION})
include(CPack)
