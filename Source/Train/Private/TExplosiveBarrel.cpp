// Fill out your copyright notice in the Description page of Project Settings.


#include "TExplosiveBarrel.h"
#include "TMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ATExplosiveBarrel::ATExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	
	MeshComp->OnComponentHit.AddDynamic(this, &ATExplosiveBarrel::Explose);
	MeshComp->SetCollisionProfileName(TEXT("Barrel"));
	MeshComp->SetSimulatePhysics(true);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(RootComponent);
	
	RadialForceComp->Radius = 1500.0f;
	RadialForceComp->ImpulseStrength = 300000.0f;
	RadialForceComp->Falloff = RIF_Linear;
	RadialForceComp->AddCollisionChannelToAffect(ECC_PhysicsBody);
}

void ATExplosiveBarrel::Explose(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (ATMagicProjectile* Projectile = Cast<ATMagicProjectile>(OtherActor))
		{
			RadialForceComp->FireImpulse();
			OtherActor->Destroy();
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ATExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

