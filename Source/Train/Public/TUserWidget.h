// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TUserWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class TRAIN_API UTUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
		
	void BindToAttributes(UTAttributeComponent* Comp);
	
protected :
		
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthBar;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTAttributeComponent* OwningComp , float NewHealth, float Delta);
};
