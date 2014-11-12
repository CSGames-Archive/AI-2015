/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** stdafx.h
** All the precompile headers
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

// Remove warning for Boost library
#define NOMINMAX

#define MAX_CHARACTER_PER_TEAM 2
#define MAX_TEAM 2
#define MESSAGE_MAX_ARGUMENT 16

// Boost
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>

#include "Ogre.h"
#include "OIS.h"

#include <iostream>
#include <map>
#include <queue>
#include <chrono>
#include <thread>

// Check for duplicate include of window.h
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
