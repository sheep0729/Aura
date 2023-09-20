// Copyright Yang Dong


#include "Data/AttributeInfo.h"
#include "Data/AuraGameplayTags.h"
#include "UObject/ObjectSaveContext.h"

const FAuraAttributeInfo FAuraAttributeInfo::Empty{};

void UAttributeInfo::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);

	SetDefaultData();
}

void UAttributeInfo::PostLoad()
{
	Super::PostLoad();

	SetDefaultData();
}

const FAuraAttributeInfo& UAttributeInfo::GetAttributeInfo(const FGameplayAttribute& Attribute, const bool bLogNotFound) const
{
	if (const auto AttributeInfoPtr = AttributeInfos.Find(Attribute))
	{
		return *AttributeInfoPtr;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for Attribute [%s] on AttributeInfo [%s]."), *Attribute.AttributeName, *GetNameSafe(this));
	}

	return FAuraAttributeInfo::Empty;
}

// const FAuraAttributeInfo& UAttributeInfo::GetAttributeInfo(const FGameplayTag& AttributeTag, const bool bLogNotFound) const
// {
// 	return GetAttributeInfo(UAuraAbilitySystemLibrary::GetAttributesByTag(AttributeTag), bLogNotFound);
// }

void UAttributeInfo::SetDefaultData()
{
	for (const auto& Pair : FAuraGameplayTags::GetAttributeMap())
	{
		auto AttributeInfoPtr = AttributeInfos.Find(Pair.Value);
		if (!AttributeInfoPtr)
		{
			AttributeInfoPtr = &AttributeInfos.Add(Pair.Value, FAuraAttributeInfo{Pair.Key});
		}
		if (AttributeInfoPtr->AttributeName.IsEmpty())
		{
			AttributeInfoPtr->AttributeName = FText::FromString(Pair.Value.AttributeName);
		}
		AttributeInfoPtr->Attribute = Pair.Value;
	}
}
