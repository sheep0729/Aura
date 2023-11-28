// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"

namespace CustomDepth
{
	constexpr int32 Red = 250;
}

namespace EAuraCollisionChannel
{
	inline const ECollisionChannel& Projectile = ECC_GameTraceChannel1;
	inline const ECollisionChannel& Pickup = ECC_GameTraceChannel2;
	inline const ECollisionChannel& Interactivity = ECC_GameTraceChannel3;
	inline const ECollisionChannel& Floor = ECC_GameTraceChannel4;
}

namespace EAuraCollision
{
	
}

namespace EAuraCollisionProfileName
{
	inline const FName Projectile{"Projectile"};
	inline const FName Pickup{"Pickup"};
	inline const FName Enemy{"Enemy"};
	inline const FName Weapon{"Weapon"};
}
