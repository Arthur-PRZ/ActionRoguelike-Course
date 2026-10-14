// Fill out your copyright notice in the Description page of Project Settings.


#include "TDash.h"

#include "TCharacter.h"

// Sets default values
ATDash::ATDash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProcParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProcParticleComp"));
	ProcParticleComp->SetupAttachment(RootComponent);

	
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void ATDash::BeginPlay()
{
	Super::BeginPlay();
	
	ProcParticleComp->Deactivate();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

// Called every frame
void ATDash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

