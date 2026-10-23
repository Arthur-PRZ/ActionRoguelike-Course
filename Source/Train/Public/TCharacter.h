// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UTInteractionComponent;
class UAnimeMontage;
class UTAttributeComponent;

UCLASS()
class TRAIN_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> BlackholeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> DashClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_Blackhole;
	FTimerHandle Timerhandle_Dash;
	// FTimerHandle Timerhandle_DashAnim;
	
public:
	// Sets default values for this character's properties
	ATCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* ArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTAttributeComponent* AttributeComp;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PrimaryAttackAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* BlackholeAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DashAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	
	

	UPROPERTY(VisibleAnywhere)
	UTInteractionComponent* InteractComp;

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void Blackhole();
	void Blackhole_TimeElapsed();
	void Jump();
	void Interact();
	void Dash();
	void Dash_TimeElapsed();
	
	UFUNCTION()
	void DashStop_TimeElapsed(ATDash *Actor);
	
	UFUNCTION()
	void DashTP_TimeElapsed(ATDash* Actor);
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UTAttributeComponent* OwningComp , float NewHealth, float Delta);
	
	void Move(const FInputActionValue& EventValue);
	void Look(const FInputActionValue& EventValue);
	
	FTransform GetSpawnTM();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
