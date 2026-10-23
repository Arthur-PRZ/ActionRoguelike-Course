// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UTAttributeComponent*, OwningComp , float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAIN_API UTAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTAttributeComponent();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	float Health;
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void ApplyHealthChange(float Delta);
		
};
