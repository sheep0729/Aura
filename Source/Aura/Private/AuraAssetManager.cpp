// Copyright Yang Dong


#include "AuraAssetManager.h"

#include "AbilitySystem/AuraAttributeSet.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// FAuraGameplayTags::Initialize();
	UAuraAttributeSet::InitializeAttributeTag();
}
