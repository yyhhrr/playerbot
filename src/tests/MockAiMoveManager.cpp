#include "pch.h"
#include "aitest.h"
#include "MockAiMoveManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;


void MockAiMoveManager::Attack(Unit* target)
{
	if (target == MockedTargets::GetCurrentTarget())
	buffer->append(">T:melee");

	if (target == MockedTargets::GetTargetForDps())
	buffer->append(">dps assist");

	if (target == MockedTargets::GetTargetForTank())
	buffer->append(">tank assist");
}
