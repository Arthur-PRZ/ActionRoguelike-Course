// Fill out your copyright notice in the Description page of Project Settings.


#include "TUserWidget.h"

#include "TAttributeComponent.h"
#include "Components/ProgressBar.h"

void UTUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	HealthBar->SetPercent(1);
}

void UTUserWidget::BindToAttributes(UTAttributeComponent* Comp)
{
	Comp->OnHealthChanged.AddDynamic(this, &UTUserWidget::OnHealthChanged);
}

void UTUserWidget::OnHealthChanged(AActor* InstigatorActor, UTAttributeComponent* OwningComp , float NewHealth, float Delta)
{
		HealthBar->SetPercent(NewHealth / 100);
}
