// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/PlayerModeActor.h"

#include "Components/SkinActorComponent.h"

// Sets default values
APlayerModeActor::APlayerModeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkinComponent = CreateDefaultSubobject<USkinActorComponent>(TEXT("SkinComp"));
}

// Called when the game starts or when spawned
void APlayerModeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

USkeletalMeshComponent* APlayerModeActor::GetSkinSkeletalMeshComponent()
{
	return SkeletalMeshComponent;
}

// Called every frame
void APlayerModeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USkinActorComponent* APlayerModeActor::GetSkinComponent()
{
	return SkinComponent;
}

void APlayerModeActor::SetSkeletalMesh(USkeletalMesh* Mesh)
{
	SkeletalMeshComponent->SetSkeletalMesh(Mesh);
}

