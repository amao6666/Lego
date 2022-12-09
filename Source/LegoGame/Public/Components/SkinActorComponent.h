// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystem/PropsSubsystem.h"
#include "SkinActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEGOGAME_API USkinActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkinActorComponent();

	void OnSkinPuton(ESkinType Type, int32 ID);
	void OnSkinTakeoff(ESkinType Type, int32 ID);
	
protected:
	UPROPERTY()
	TMap<ESkinType, UStaticMeshComponent*> StaticMeshCompMap;
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UStaticMeshComponent* GetStaticMeshComponent(ESkinType Type);
	USkeletalMeshComponent* GetSkeletalMeshComponent();
	
	FName GetSocketName(ESkinType Type);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
