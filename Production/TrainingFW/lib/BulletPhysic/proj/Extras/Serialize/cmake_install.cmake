# Install script for directory: D:/Study/GameloftInternship/GL_Test/Newfolder/TrainingFW/lib/BulletPhysic/src/physicBullet/Extras/Serialize

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Study/GameloftInternship/GL_Test/Newfolder/TrainingFW/lib/BulletPhysic/proj/Extras/Serialize/BulletFileLoader/cmake_install.cmake")
  include("D:/Study/GameloftInternship/GL_Test/Newfolder/TrainingFW/lib/BulletPhysic/proj/Extras/Serialize/BulletXmlWorldImporter/cmake_install.cmake")
  include("D:/Study/GameloftInternship/GL_Test/Newfolder/TrainingFW/lib/BulletPhysic/proj/Extras/Serialize/BulletWorldImporter/cmake_install.cmake")

endif()

