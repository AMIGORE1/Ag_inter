#include "gun_update.h"
#include "core/global/config.h"

CachedWeaponStats* cachedWeaponStats = nullptr;

void ApplyWeaponHacks() {
    if (!cachedWeaponStats) return;

    if (config::NoRecoil) {
        cachedWeaponStats->recoilMultiplier.Set(0.0f);
        cachedWeaponStats->inaccuracyShrinkRateMultiplier.Set(100.0f);
        cachedWeaponStats->additiveMinSpread = 0.0f;
        cachedWeaponStats->additiveAimInaccuracyMultiplier.Set(0.0f);
    }
    else {
        cachedWeaponStats->recoilMultiplier.Set(1.0f);
        cachedWeaponStats->inaccuracyShrinkRateMultiplier.Set(1.0f);
        cachedWeaponStats->additiveMinSpread = 0.0f;
        cachedWeaponStats->additiveAimInaccuracyMultiplier.Set(1.0f);
    }

    if (config::RapidFire) {
        cachedWeaponStats->fireRateMultiplier.Set(100.0f);
        cachedWeaponStats->overrideFireMode = 2;
    }
    else {
        cachedWeaponStats->fireRateMultiplier.Set(1.0f);
        cachedWeaponStats->overrideFireMode = 2;
    }

    if (config::InfAmmo) {
        cachedWeaponStats->additionalCostPerShot = -1;
    }
    else {
        if (cachedWeaponStats->additionalCostPerShot == -1) {
            cachedWeaponStats->additionalCostPerShot = 30;
        }
    }

    if (config::MultiShot) {
        cachedWeaponStats->additionalProjectiles = 30;
    }
    else {
        cachedWeaponStats->additionalProjectiles = 1;
    }

    if (config::MegaWeaponMod) {
        cachedWeaponStats->damageMultiplier.Set(10.0f);
        cachedWeaponStats->projectileSpeedMultiplier = 9999.0f;
        cachedWeaponStats->additivePenetration.Set(99.0f);
        cachedWeaponStats->additiveArmorPen.Set(1.0f);
    }
    else {
        cachedWeaponStats->damageMultiplier.Set(1.0f);
        cachedWeaponStats->projectileSpeedMultiplier = 1.0f;
        cachedWeaponStats->additivePenetration.Set(0.0f);
        cachedWeaponStats->additiveArmorPen.Set(0.0f);
    }
}

void __fastcall hGunUpdate(void* __this, const void* method)
{
    if (__this) {
        cachedWeaponStats = reinterpret_cast<CachedWeaponStats*>((uintptr_t)__this + 0x38);
        ApplyWeaponHacks();
    }
    return oGunUpdate(__this, method);
}