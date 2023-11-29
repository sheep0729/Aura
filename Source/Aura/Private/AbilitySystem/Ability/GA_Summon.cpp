// Copyright Yang Dong


#include "AbilitySystem/Ability/GA_Summon.h"

#include "Aura/Aura.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UGA_Summon::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2, FVector::UpVector);
	const float DeltaSpread = SpawnSpread / NumMinions;

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByObjectType(Hit, ChosenSpawnLocation + FVector(0, 0, 400), ChosenSpawnLocation - FVector(0, 0, 400),
		                                        FCollisionObjectQueryParams{EAuraCollisionChannel::Floor});
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18, 12, FColor::Cyan, false, 3);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UGA_Summon::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
