// Fill out your copyright notice in the Description page of Project Settings.


#include "TDash.h"

#include "TCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATDash::ATDash()
{
	ProcParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ProcParticleComp");
	ProcParticleComp->SetupAttachment(RootComponent);
	
	MovementComp->InitialSpeed = 6000.0f;

}

// Called when the game starts or when spawned
void ATDash::BeginPlay()
{
	Super::BeginPlay();
	
	ProcParticleComp->Deactivate();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	
	GetWorldTimerManager().SetTimer(Timerhandle_Dash, this, &ATDash::Explode, 0.2f);
}


void ATDash::Explode()
{
	GetWorldTimerManager().ClearTimer(Timerhandle_Dash);
	
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	
	EffectComp->DeactivateSystem();
	SetActorEnableCollision(false);
	
	StopMovementComp();	
	
	ProcParticleComp->Activate();
	
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ATDash::TeleportInstigator, 0.2f);
}

void ATDash::TeleportInstigator()
{
	ATCharacter *Insti = Cast<ATCharacter>(GetInstigator());
	if (Insti)
	{
		Insti->TeleportTo(GetActorLocation(), GetActorRotation(), false, false);
		Destroy();
	}
}

