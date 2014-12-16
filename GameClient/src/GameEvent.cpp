/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameEvent.cpp
** Implementation of GameEvent
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "GameEvent.h"

int GameEvent::convertCharToNumeral(std::string token)
{
	bool isDigit = true;

	// Skip the first character because it could be "-"
	for(int i = 1; i < token.size(); ++i)
	{
		if(!isdigit(token[i]))
		{
			isDigit = false;
			break;
		}
	}

	if(isDigit)
	{
		return std::atoi(token.c_str());
	}
	std::cout << "Converting char to numeral failed for :" << token << std::endl;
	return 0;
}

void ErrorEvent::execute(World* world)
{
	std::cout << "Error :" << message << std::endl;
}

bool ErrorEvent::fill(std::string arguments)
{
	message = arguments;
	return true;
}

void DisconnectEvent::execute(World* world)
{
	std::cout << "Player " << teamId << " disconnected from the game" << std::endl;

	world->removeTeam(teamId);
}

bool DisconnectEvent::fill(std::string arguments)
{
	teamId = convertCharToNumeral(arguments);

	if(teamId != 0)
		return true;
	return false;
}

void AddTeamEvent::execute(World* world)
{
	std::cout << "Team " << teamId << " join with name " << teamName << std::endl;
	for( int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		std::cout << "    * Character " << characterNames[i] << " enter the battlefield" << std::endl;
	}

	world->addTeam(teamId, teamName, characterNames);
}

bool AddTeamEvent::fill(std::string arguments)
{

	teamName = NetUtility::getNextToken(arguments, ":");

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		characterNames[i] = NetUtility::getNextToken(arguments, ":");
	}

	teamId = convertCharToNumeral(NetUtility::getNextToken(arguments, ":"));

	if(teamId != 0)
		return true;
	return false;
}

void MoveCharacterEvent::execute(World* world)
{
	std::cout << "Team " << teamId << " move character " << characterId << 
				 " to (" << positionX << "," << positionZ << ")" << std::endl;

	world->getTeam(teamId)->getCharacter(characterId)->setTargetPosition(positionX, positionZ);
}

bool MoveCharacterEvent::fill(std::string arguments)
{
	characterId = convertCharToNumeral(NetUtility::getNextToken(arguments, ":"));
	positionX = convertCharToNumeral(NetUtility::getNextToken(arguments, ":"));
	positionZ = convertCharToNumeral(NetUtility::getNextToken(arguments, ":"));
	teamId = convertCharToNumeral(NetUtility::getNextToken(arguments, ":"));

	if(teamId != 0)
		return true;
	return false;
}
