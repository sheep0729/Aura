// Copyright Yang Dong


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::BindCallBacksToController_Implementation()
{
}

void UAuraUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BindCallBacksToController();
}
