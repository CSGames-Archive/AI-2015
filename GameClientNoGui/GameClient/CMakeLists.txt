cmake_minimum_required(VERSION 2.8)
SET(GameClient)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.54.0 COMPONENTS system thread regex) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable (GameClient client.cpp NetCharacter.cpp NetCharacter.h NetCommandController.cpp NetworkController.h NetPlayer.cpp NetPlayer.h NetPlayerController.cpp NetPlayerController.h NetUtility.h NetworkController.cpp NetworkController.h)
    target_link_libraries(GameClient ${Boost_LIBRARIES})                                                                                                                                                                                                                            
endif()

