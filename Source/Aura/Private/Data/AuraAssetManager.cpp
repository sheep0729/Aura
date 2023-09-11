// Copyright Yang Dong


#include "Data/AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Data/AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeAuraGameplayTags();
}
