#include "pch.h"
#include "aitest.h"
#include "MockAiMoveManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

float MockAiMoveManager::GetDistanceTo(Unit* target)
{
	return distanceTo[target];
}

void MockAiMoveManager::MoveTo(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">master");

	if (target == MockedTargets::GetCurrentTarget())
	{
		if (distance >= SPELL_DISTANCE) 
			buffer->append(">T:reach spell"); 
		else 
			buffer->append(">T:reach melee");
	}
}
float MockAiMoveManager::GetFollowAngle()
{
	return 0.0f;
}

void MockAiMoveManager::Follow(Unit* target, float distance, float angle)
{
	Follow(target, distance);
}

void MockAiMoveManager::Follow(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">S:follow master");
	
	else if (target == MockedTargets::GetLineTarget())
		buffer->append(">S:follow line");

	else
		buffer->append(">S:follow");
}

bool MockAiMoveManager::Flee(Unit* target, float distance)
{
	if (target == MockedTargets::GetMaster())
		buffer->append(">goaway");
	else
		buffer->append(">S:flee"); 

	return true;
}

void MockAiMoveManager::StayCircle(float range)
{
	buffer->append(">stay circle");
}

void MockAiMoveManager::StayLine(float range)
{
	buffer->append(">stay line");
}

void MockAiMoveManager::StayCombat(float range)
{
	buffer->append(">stay combat");
}


void MockAiMoveManager::Stay()
{
	buffer->append(">stay");
}

bool MockAiMoveManager::IsMoving(Unit* target)
{
	return moving[target];
}

void MockAiMoveManager::Attack(Unit* target)
{
	if (target == MockedTargets::GetCurrentTarget())
	buffer->append(">T:melee");

	if (target == MockedTargets::GetTargetForDps())
	buffer->append(">dps assist");

	if (target == MockedTargets::GetTargetForTank())
	buffer->append(">tank assist");
}

bool MockAiMoveManager::IsBehind(Unit* target)
{
    return isBehind[target];
}
