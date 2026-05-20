#include "move_update.h"
PlayerMovementData* cachedMovementData = nullptr;

void hMovementUpdate(void* __this, const void* method)
{
	cachedMovementData = reinterpret_cast<PlayerMovementData*>(__this);
	ApplyMovementHacks();
	return oMovementUpdate(__this, method);
}

void ApplyMovementHacks()
{
    if (!cachedMovementData) return;

    if (config::SpeedHack) {
        cachedMovementData->walkingSpeedMultiplier.Set(5.0f);
        cachedMovementData->sprintSpeedMultiplier.Set(5.0f);
        cachedMovementData->runningSpeed.Set(3.0f);
    }
    else {
        cachedMovementData->walkingSpeedMultiplier.Set(3.0f);
        cachedMovementData->sprintSpeedMultiplier.Set(3.0f);
        cachedMovementData->runningSpeed.Set(3.0f);
    }

    if (config::NoFallDamage) {
        cachedMovementData->useFallDistanceDamage = false;
        cachedMovementData->minFallDamageVelocity = 99999.0f;
        cachedMovementData->deathFallDamageVelocity = 99999.0f;
        cachedMovementData->minFallDamageHeight = 99999.0f;
        cachedMovementData->deathFallDamageHeight = 99999.0f;
    }
    else {

        cachedMovementData->useFallDistanceDamage = true;
        if (cachedMovementData->minFallDamageVelocity == 99999.0f) {
            cachedMovementData->minFallDamageVelocity = 12.0f;
            cachedMovementData->deathFallDamageVelocity = 25.0f;
            cachedMovementData->minFallDamageHeight = 4.0f;
            cachedMovementData->deathFallDamageHeight = 15.0f;
        }
    }

    if (config::SpiderMan) {
        if (cachedMovementData->hitWall && cachedMovementData->verticalInput > 0.1f) {
            cachedMovementData->isInLadder = true;
            cachedMovementData->currentMovementVelocity.y = 6.0f;
        }
    }

    if (config::FlyHack) {
        cachedMovementData->isGrounded = true;
        cachedMovementData->isFalling = false;

        cachedMovementData->currentMovementVelocity.y = 0.0f;

        if (GetAsyncKeyState(VK_SPACE)) {
            cachedMovementData->currentMovementVelocity.y = 15.0f;
        }
        if (GetAsyncKeyState(VK_CONTROL)) {
            cachedMovementData->currentMovementVelocity.y = -15.0f;
        }
    }

}
