// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LGPlayerCharacter.h"

#include "LegoGameHUD.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Scene/SceneItemActor.h"
#include "Components/PackageActorComponent.h"

ALGPlayerCharacter::ALGPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComp"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CamreComp"));
	MainCamera->SetupAttachment(ArmComponent);
	ArmComponent->SetupAttachment(RootComponent);
	ArmComponent->bUsePawnControlRotation = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	SphereComponent->SetSphereRadius(150.f);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALGPlayerCharacter::OnSphereComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALGPlayerCharacter::OnSphereComponentEndOverlap);
}

USpringArmComponent* ALGPlayerCharacter::GetSpringArmComponent()
{
	return ArmComponent; 
}

UCameraComponent* ALGPlayerCharacter::GetCameraComponent()
{
	return MainCamera;
}

void ALGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("DoJump"), IE_Pressed, this, &ALGPlayerCharacter::DoJump);
	PlayerInputComponent->BindAction(TEXT("DoSprint"), IE_Pressed, this, &ALGPlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("DoSprint"), IE_Released, this, &ALGPlayerCharacter::EndSprint);
	PlayerInputComponent->BindAction(TEXT("DoCrouch"), IE_Pressed, this, &ALGPlayerCharacter::DoCrouch);
	PlayerInputComponent->BindAction(TEXT("TogglePackage"), IE_Pressed, this, &ALGPlayerCharacter::TogglePackage);
	PlayerInputComponent->BindAction(TEXT("ToggleAim"), IE_Pressed, this, &ALGPlayerCharacter::StartAim);
	PlayerInputComponent->BindAction(TEXT("ToggleAim"), IE_Released, this, &ALGPlayerCharacter::EndAim);
	PlayerInputComponent->BindAction(TEXT("DoFire"), IE_Pressed, this, &ALGPlayerCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("DoFire"), IE_Released, this, &ALGPlayerCharacter::EndFire);
	PlayerInputComponent->BindAction(TEXT("DoReload"), IE_Pressed, this, &ALGPlayerCharacter::DoReload);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ALGPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ALGPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ALGPlayerCharacter::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ALGPlayerCharacter::LookUp);
}

void ALGPlayerCharacter::MoveForward(float Value)
{
	if (Value == 0) return;
	AddMovementInput(FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetAxisX(), Value);
}

void ALGPlayerCharacter::MoveRight(float Value)
{
	if (Value == 0) return;
	AddMovementInput(FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetAxisY(), Value);
}

void ALGPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * GetWorld()->GetDeltaSeconds() * 35);
}

void ALGPlayerCharacter::TurnRate(float Value)
{
	AddControllerYawInput(Value * GetWorld()->GetDeltaSeconds() * 35);
}

void ALGPlayerCharacter::TogglePackage()
{
	ALegoGameHUD* HUD = Cast<ALegoGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	HUD->TogglePackageShow();
}

void ALGPlayerCharacter::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASceneItemActor* SceneItemActor = Cast<ASceneItemActor>(OtherActor))
	{
		if (PackageComponent)
		{
			PackageComponent->AddNearSceneItem(SceneItemActor);
		}
	}
}

void ALGPlayerCharacter::OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ASceneItemActor* SceneItemActor = Cast<ASceneItemActor>(OtherActor))
	{
		if (PackageComponent)
		{
			PackageComponent->RemoveNearSceneItem(SceneItemActor);
		}
	}
}
