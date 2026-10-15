// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TProjectileCannon.generated.h"

class ATMagicProjectile;

UCLASS()
class TRAIN_API ATProjectileCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATProjectileCannon();

protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	FTimerHandle ShootTimer;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	void Shoot_TimeElapsed();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
