// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/SkinInterface.h"
#include "PlayerModeActor.generated.h"

class USkinActorComponent;

UCLASS()
class LEGOGAME_API APlayerModeActor : public AActor, public ISkinInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerModeActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USkinActorComponent* SkinComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual USkeletalMeshComponent* GetSkinSkeletalMeshComponent() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	USkinActorComponent* GetSkinComponent();
	void SetSkeletalMesh(USkeletalMesh* Mesh);
};
