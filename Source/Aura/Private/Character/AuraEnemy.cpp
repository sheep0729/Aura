// Copyright Yang Dong


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"
#include "Kismet/KismetSystemLibrary.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	SetHighlighted(true);

	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void AAuraEnemy::UnHighlightActor()
{
	SetHighlighted(false);

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetCustomDepthStencilValue(CustomDepthRed);
	Weapon->SetCustomDepthStencilValue(CustomDepthRed);
}
