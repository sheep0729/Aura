// Copyright Yang Dong

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadOnly, Transient)
	mutable float AttributeValue;

	static const FAuraAttributeInfo Empty;
};

UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	virtual void PostLoad() override;
	const FAuraAttributeInfo& GetAttributeInfo(const FGameplayAttribute& Attribute, bool bLogNotFound = false) const;
	// FAuraAttributeInfo& GetAttributeInfo(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

protected:
	void SetDefaultData();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TMap<FGameplayAttribute, FAuraAttributeInfo> AttributeInfos;
};
