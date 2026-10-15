// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAIN_API UTAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTAttributeComponent();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Attribute")
	float Health;
	
public:
	
	void ApplyHealthChange(float Delta);
		
};
