cmake_minimum_required(VERSION 2.8)
SET(AIClient)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54.0 COMPONENTS system thread regex)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable (AIClient client.cpp Character.cpp Character.h GameMap.cpp GameMap.h NetCommandController.cpp NetworkController.h NetUtility.h NetworkController.cpp NetworkController.h Player.cpp Player.h)
    target_link_libraries(AIClient ${Boost_LIBRARIES})                                                                                                                                                                                                                            
endif()

