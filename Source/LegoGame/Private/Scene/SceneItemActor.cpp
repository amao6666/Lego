// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/SceneItemActor.h"
#include "Components/BillboardComponent.h"
#include "LegoGame/LegoGame.h"
#include "Subsystem/PropsSubsystem.h"

// Sets default values
ASceneItemActor::ASceneItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComp"));
	BillboardComponent->SetupAttachment(RootComponent);
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASceneItemActor::BeginPlay()
{
	Super::BeginPlay();
	InitActor();
}

void ASceneItemActor::InitActor()
{
	//找一下数据对象
	const FPropsBase* PropsBase = GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(ID);
	if (PropsBase)
	{
		if (PropsBase->Type == EPropsType::EPT_Skin)
		{
			const FSkin* Skin = static_cast<const FSkin*>(PropsBase);
			if (Skin->StaticMesh)
			{
				GetStaticMeshComponent()->SetStaticMesh(Skin->StaticMesh);
			}
			else if (Skin->SkeletalMesh)
			{
				GetSkeletalMeshComponent()->SetSkeletalMesh(Skin->SkeletalMesh);
			}
		}
		else if (PropsBase->Type == EPropsType::EPT_Weapon)
		{
			const FWeapon* Weapon = static_cast<const FWeapon*>(PropsBase);
			GetSkeletalMeshComponent()->SetSkeletalMesh(Weapon->WeaponMesh);
		}
	}
}

UStaticMeshComponent* ASceneItemActor::GetStaticMeshComponent()
{
	if (StaticMeshComponent)
	{
		return StaticMeshComponent;
	}
	//动态创建组件
	StaticMeshComponent = NewObject<UStaticMeshComponent>(this);
	StaticMeshComponent->RegisterComponentWithWorld(GetWorld());
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//设置collsion的物体类别通道
	StaticMeshComponent->SetCollisionObjectType(ECC_SceneItem);
	return StaticMeshComponent;
}

USkeletalMeshComponent* ASceneItemActor::GetSkeletalMeshComponent()
{
	if (SkeletalMeshComponent)
	{
		return SkeletalMeshComponent;
	}
	//动态创建组件
	SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this);
	SkeletalMeshComponent->RegisterComponentWithWorld(GetWorld());
	SkeletalMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//设置collsion的物体类别通道
	SkeletalMeshComponent->SetCollisionObjectType(ECC_SceneItem);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SkeletalMeshComponent->SetGenerateOverlapEvents(true);
	return SkeletalMeshComponent;
}

// Called every frame
void ASceneItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ASceneItemActor::GetID()
{
	return ID;
}

void ASceneItemActor::SetID(int32 OutID)
{
	ID = OutID;
}

