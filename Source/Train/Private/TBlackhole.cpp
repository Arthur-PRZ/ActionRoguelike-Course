// Fill out your copyright notice in the Description page of Project Settings.


#include "TBlackhole.h"

#include "AssetTypeCategories.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ATBlackhole::ATBlackhole()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	DestroySphereComp = CreateDefaultSubobject<USphereComponent>("DestroySphereComp");
	DestroySphereComp->SetupAttachment(SphereComp);
	
	DestroySphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATBlackhole::OnOverlap);
	DestroySphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	DestroySphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(SphereComp);
	
	RadialForceComp->Radius = 800.0f;
	RadialForceComp->ForceStrength = -3000000.0f;
	RadialForceComp->Falloff = RIF_Linear;
	RadialForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
	RadialForceComp->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	RadialForceComp->SetAutoActivate(true);
	RadialForceComp->bIgnoreOwningActor = true;
	
	
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 1000.0f;
	
}

// Called when the game starts or when spawned
void ATBlackhole::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(Handler_Destroy, this, &ATBlackhole::DestroyTimer, 5.0f);
}

void ATBlackhole::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(APawn::StaticClass()) && OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void ATBlackhole::DestroyTimer()
{
	Destroy();
}

