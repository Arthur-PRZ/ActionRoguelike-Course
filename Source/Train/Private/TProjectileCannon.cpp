// Fill out your copyright notice in the Description page of Project Settings.


#include "TProjectileCannon.h"
#include "Kismet/KismetMathLibrary.h"
#include "TCharacter.h"
#include "TMagicProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATProjectileCannon::ATProjectileCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATProjectileCannon::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ShootTimer, this, &ATProjectileCannon::Shoot_TimeElapsed, 2.0f, true);

}

void ATProjectileCannon::Shoot_TimeElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("OUI"));
	
	FActorSpawnParameters SpawnInfo;
	
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
	
	FTransform SpawnTransform(Rotation, GetActorLocation());
	
	GetWorld()->SpawnActor<ATMagicProjectile>(ProjectileClass, SpawnTransform, SpawnInfo);
}

// Called every frame
void ATProjectileCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

