cmake_minimum_required(VERSION 2.8)

SET(GameClient)

set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.54.0 COMPONENTS system thread regex)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

set(HEADER_FILES
  include/stdafx.h
  include/BaseApplication.h
  include/GameClientApplication.h
  include/NetCommandController.h
  include/NetPlayer.h
  include/NetPlayerController.h
  include/NetworkController.h
  include/SinbadCharacterController.h
)

set(SOURCE_FILES
  src/BaseApplication.cpp
  src/GameClientApplication.cpp
  src/NetCommandController.cpp
  src/NetPlayer.cpp
  src/NetPlayerController.cpp
  src/NetworkController.cpp
  src/stdafx.cpp
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}
			${OIS_INCLUDE_DIRS}
			${OGRE_INCLUDE_DIRS}
			${OGRE_SAMPLES_INCLUDEPATH}
			${OGRE_Overlay_INCLUDE_DIRS})

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_executable (GameClient ${HEADER_FILES} ${SOURCE_FILES})
    target_link_libraries(GameClient ${Boost_LIBRARIES} ${OGRE_LIBRARIES} ${OIS_LIBRARIES}${OGRE_Overlay_LIBRARIES})                                                                                                                                                                                                                            
endif()

