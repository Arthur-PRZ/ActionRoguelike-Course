// Fill out your copyright notice in the Description page of Project Settings.


#include "TCharacter.h"

#include "TDash.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TAttributeComponent.h"
#include "TInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATCharacter::ATCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ArmComp = CreateDefaultSubobject<USpringArmComponent>("ArmComp");
	ArmComp->bUsePawnControlRotation = true; 
	ArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(ArmComp);
	
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractComp = CreateDefaultSubobject<UTInteractionComponent>("InteractComp");
	AttributeComp = CreateDefaultSubobject<UTAttributeComponent>("AttributeComp");
}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		PC->PlayerCameraManager->ViewPitchMin = -60.f;
		PC->PlayerCameraManager->ViewPitchMax = 60.f;
		
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
	
}

void ATCharacter::OnHealthChanged(AActor* InstigatorActor, UTAttributeComponent* OwningComp , float NewHealth, float Delta)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewHealth);
}

void ATCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ATCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ATCharacter::PrimaryAttack_TimeElapsed()
{
	if (ensureAlways(ProjectileClass))
	{
		FTransform SpawnTM = GetSpawnTM();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}

void ATCharacter::Blackhole()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_Blackhole, this, &ATCharacter::Blackhole_TimeElapsed, 0.2f);
}

void ATCharacter::Blackhole_TimeElapsed()
{
	FTransform SpawnTM = GetSpawnTM();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(BlackholeClass, SpawnTM, SpawnParams);
}

void ATCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(Timerhandle_Dash, this, &ATCharacter::Dash_TimeElapsed, 0.2f);
}

void ATCharacter::Dash_TimeElapsed()
{
	FTransform SpawnTM = GetSpawnTM();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	
	ATDash* SpawnedActor = GetWorld()->SpawnActor<ATDash>(DashClass, SpawnTM, SpawnParams);
	
	// SpawnedActor->GetMovementComp()->OnProjectileStop
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "DashStop_TimeElapsed", SpawnedActor);
	
	GetWorldTimerManager().SetTimer(Timerhandle_Dash, TimerDelegate, 0.2f, false);
}

void ATCharacter::DashStop_TimeElapsed(ATDash* Actor)
{
	Actor->StopMovementComp();
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, "DashTP_TimeElapsed", Actor);
	
	Actor->ProcParticleComp->Activate();
	GetWorldTimerManager().SetTimer(Timerhandle_Dash, TimerDelegate, 0.2f, false);
}

void ATCharacter::DashTP_TimeElapsed(ATDash* Actor)
{
	SetActorLocation(Actor->GetActorLocation());
	Actor->Destroy();
}

void ATCharacter::Jump()
{
	Super::Jump();
}

void ATCharacter::Move(const FInputActionValue& EventValue)
{
	FVector2D MovementVector = EventValue.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0;
		Rotation.Roll = 0;
		
		AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::X), MovementVector.Y);
		AddMovementInput(FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y), MovementVector.X);
	}
}

void ATCharacter::Look(const FInputActionValue& EventValue)
{
	FVector2D MovementVector = EventValue.Get<FVector2D>();
	
	// if (GEngine)
	// {
	//  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ma variable: %f"),  MovementVector.Y));
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Ma variable: %f"),  MovementVector.X));
	// }
	AddControllerYawInput(MovementVector.X);
	AddControllerPitchInput(MovementVector.Y * 0.5f);
}



void ATCharacter::Interact()
{
	InteractComp->PrimaryInteract();
}

FTransform ATCharacter::GetSpawnTM()
{
	FHitResult Hit;
	FVector Start = GetMesh()->GetSocketLocation("Muzzle_01");
	FVector End = CameraComp->GetComponentLocation() + (CameraComp->GetForwardVector() * 10000.0f);
	
	FVector TargetPoint = End;
	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraComp->GetComponentLocation(), End, ECC_Visibility))
	{
		TargetPoint = Hit.ImpactPoint;
	}
	
	FRotator FinalRotation = UKismetMathLibrary::FindLookAtRotation(Start, TargetPoint);
	FTransform SpawnTM(FinalRotation, Start);
	
	return SpawnTM;
}



// Called every frame
void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATCharacter::Look);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &ATCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATCharacter::Jump);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATCharacter::Interact);
		EnhancedInputComponent->BindAction(BlackholeAction, ETriggerEvent::Started, this, &ATCharacter::Blackhole);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ATCharacter::Dash);
	}
}

