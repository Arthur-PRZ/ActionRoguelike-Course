// Fill out your copyright notice in the Description page of Project Settings.


#include "TTargetDummy.h"
#include "TAttributeComponent.h"

ATTargetDummy::ATTargetDummy()
{
	AttributeComp = CreateDefaultSubobject<UTAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATTargetDummy::OnHealthChanged);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	
}

void ATTargetDummy::OnHealthChanged(AActor* InstigatorPawn, UTAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}



