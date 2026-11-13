// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TProjectile.h"
#include "GameFramework/Actor.h"
#include "TDash.generated.h"

UCLASS()
class TRAIN_API ATDash : public ATProjectile
{
	GENERATED_BODY()
	
public:	

	ATDash();

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ProcParticleComp;
	

protected:

	virtual void BeginPlay() override;

	FTimerHandle Timerhandle_Dash;
	
	void TeleportInstigator();
	
	void Explode() override;
};
