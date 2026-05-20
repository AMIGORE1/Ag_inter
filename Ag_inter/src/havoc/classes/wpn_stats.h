#include <cstddef>
#include <cstdint>
#include "havoc/hooks/get-set/set_protec/set_protec.h"


struct CachedWeaponStats {
    ProtectedFloat damageMultiplier;
    float projectileSpeedMultiplier;
    ProtectedFloat fireRateMultiplier;
    ProtectedFloat effectiveRangeMultiplier;
    ProtectedFloat additivePenetration;
    ProtectedFloat additiveAimInaccuracyMultiplier;
    ProtectedFloat inaccuracyShrinkRateMultiplier;
    ProtectedFloat recoilMultiplier;
    ProtectedFloat additiveArmorPen;
    ProtectedFloat additiveArmorDamageLoss;
    int32_t additionalProjectiles;
    int32_t additionalCostPerShot;
    uint8_t overrideUseSpreadPattern;

    uint8_t pad_09D[3]; 

    int32_t overrideFireMode;
    int32_t overrideFireSound;
    float additiveMinSpread;
};