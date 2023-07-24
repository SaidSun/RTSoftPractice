cmake_minimum_required(VERSION 3.0)
project( Serverd )
include_directories(/home/said/Figna/Pract/Threadst/MyDR)
add_executable( Serverd Serverd.c )


install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}Target" COMPONENT ${PROJECT_NAME} RUNTIME DESTINATION "/home/" LIBRARY DESTINATION "/home/" DESTINATION "/home")

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "AM")
INCLUDE(CPack)
