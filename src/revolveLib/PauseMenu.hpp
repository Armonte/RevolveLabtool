#pragma once

namespace revolve
{
struct PauseMenu
{
	int setModeInCharacterSelect; // 0 = VS mode, 1 = Training mode
	int setModeInMatch; // 0 = VS mode, 1 = Training mode
	int whoPaused;
	int enemyAction;
	int cpuLevel;
	int enemyGuardType;
	int lifeRecovery;
	int ukemiType;
	int isCounterHit;
	int isMeterMax;
	int defenseType;
	int displayInput;	 // 0 or 1
	int restartPosition; // 0 to 2
};
} // namespace revolve
