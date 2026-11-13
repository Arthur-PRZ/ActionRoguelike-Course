// Fill out your copyright notice in the Description page of Project Settings.


#include "TProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/FastReferenceCollector.h"


// Sets default values
ATProjectile::ATProjectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ATProjectile::OnActorHit);
	RootComponent = SphereComp;
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->InitialSpeed = 8000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	
	
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	EffectComp->SetupAttachment(SphereComp);
}

void ATProjectile::StopMovementComp() const
{
	MovementComp->StopMovementImmediately();
}

void ATProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void ATProjectile::Explode()
{
	if (ensure(IsValid(this)))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		
		Destroy();
	}
}



