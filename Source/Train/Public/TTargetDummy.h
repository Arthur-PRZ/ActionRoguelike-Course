// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTargetDummy.generated.h"

class UTAttributeComponent;

UCLASS()
class TRAIN_API ATTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ATTargetDummy();

protected:
	
	UPROPERTY(VisibleAnywhere);
	UTAttributeComponent *AttributeComp;

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent *MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorPawn, UTAttributeComponent* OwningComp, float NewHealth, float Delta);
};
