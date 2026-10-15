// Fill out your copyright notice in the Description page of Project Settings.


#include "TAttributeComponent.h"

// Sets default values for this component's properties
UTAttributeComponent::UTAttributeComponent()
{
	Health = 100;
}


void UTAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}



