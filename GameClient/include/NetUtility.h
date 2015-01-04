/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetUtility.h
** Some tools for the network
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetUtility_h_
#define __NetUtility_h_

#include "stdafx.h"

#include <iostream>

namespace NetUtility
{
	static std::string getNextToken(std::string& message, std::string separator)
	{
		std::string token = "";

		if(message.empty())
		{
			return token;
		}

		size_t index = message.find(separator);
		if(index == std::string::npos)
		{
			token = message;
			message = "";
			return token;
		}

		token = message.substr(0, index);
		message.erase(0, index+1);
		return token;
	}

	static std::string generateMoveCharacterMessage(int teamId, int characterId, double x, double z)
	{
		char numstr[21]; // Enough to hold all numbers up to 64-bits
		sprintf(numstr, "%d", teamId);
		std::string message = "Game:UpdateCharacter:";
		message += numstr;
		sprintf(numstr, "%d", characterId);
		message += ":";
		message += numstr;
		sprintf(numstr, "%d", (int)x);
		message += ":";
		message += numstr;
		sprintf(numstr, "%d", (int)z);
		message += ":";
		message += numstr;

		return message;
	}

	static std::string generateMineHit(int hitTeamId, int hitCharacterId, int originTeamId, int originCharacterId)
	{
		char numstr[21]; // Enough to hold all numbers up to 64-bits
		sprintf(numstr, "%d", hitTeamId);
		std::string message = "Game:MineHit:";
		message += numstr;
		sprintf(numstr, "%d", hitCharacterId);
		message += ":";
		message += numstr;
		sprintf(numstr, "%d", originTeamId);
		message += ":";
		message += numstr;
		sprintf(numstr, "%d", originCharacterId);
		message += ":";
		message += numstr;

		return message;
	}

	static std::string generateMissileHit(int hitEntity, int hitTeamId, int hitCharacterId, int originTeamId, int originCharacterId)
	{
		char numstr[21]; // Enough to hold all numbers up to 64-bits
		std::string message = "Game:MissileHit";

		message += ":";
		sprintf(numstr, "%d", hitEntity);
		message += numstr;

		message += ":";
		sprintf(numstr, "%d", hitTeamId);
		message += numstr;

		message += ":";
		sprintf(numstr, "%d", hitCharacterId);
		message += numstr;

		message += ":";
		sprintf(numstr, "%d", originTeamId);
		message += numstr;

		message += ":";
		sprintf(numstr, "%d", originCharacterId);
		message += numstr;

		return message;
	}
};

#endif // #ifndef __NetUtility_h_
