// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkinActorComponent.h"

#include "Interface/SkinInterface.h"

// Sets default values for this component's properties
USkinActorComponent::USkinActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USkinActorComponent::OnSkinPuton(ESkinType Type, int32 ID)
{
	const FPropsBase* PropsBase = GetOwner()->GetWorld()->GetGameInstance()->GetSubsystem<UPropsSubsystem>()->GetPropsByID(ID);
	if (PropsBase && PropsBase->Type == EPropsType::EPT_Weapon)
	{
		return;
	}
	const FSkin* Skin = static_cast<const FSkin*>(PropsBase);
	if (Skin->SkinType == ESkinType::EST_Coat)//如果是外套
	{
		GetSkeletalMeshComponent()->SetSkeletalMesh(Skin->SkeletalMesh);
	}
	else//静态网格
	{
		GetStaticMeshComponent(Type)->SetStaticMesh(Skin->StaticMesh);
	}
}

void USkinActorComponent::OnSkinTakeoff(ESkinType Type, int32 ID)
{
	if (Type == ESkinType::EST_Coat) //如果是外套
	{
		GetSkeletalMeshComponent()->SetSkeletalMesh(nullptr);
	}
	else //静态网格
	{
		GetStaticMeshComponent(Type)->SetStaticMesh(nullptr);
	}
}


// Called when the game starts
void USkinActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UStaticMeshComponent* USkinActorComponent::GetStaticMeshComponent(ESkinType Type)
{
	if (StaticMeshCompMap.Contains(Type))
	{
		return StaticMeshCompMap[Type];
	}

	UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
	StaticMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
	//设置依附关系
	if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
	{
		StaticMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GetSocketName(Type));
	}
	StaticMeshCompMap.Add(Type, StaticMeshComponent);
	
	return StaticMeshComponent;
}

USkeletalMeshComponent* USkinActorComponent::GetSkeletalMeshComponent()
{
	if (!SkeletalMeshComponent)
	{
		SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(GetOwner());
		SkeletalMeshComponent->RegisterComponentWithWorld(GetOwner()->GetWorld());
		if (ISkinInterface* SkinInterface = Cast<ISkinInterface>(GetOwner()))
		{
			SkeletalMeshComponent->AttachToComponent(SkinInterface->GetSkinSkeletalMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			// 让衣服骨架拥有身体骨架动画
			SkeletalMeshComponent->SetMasterPoseComponent(SkinInterface->GetSkinSkeletalMeshComponent());
		}
	}
	return SkeletalMeshComponent;
}

FName USkinActorComponent::GetSocketName(ESkinType Type)
{
	switch (Type)
	{
	case ESkinType::EST_Hair:
	case ESkinType::EST_Helmet:
		return TEXT("HeadSocket");
	case ESkinType::EST_Glasses:
	case ESkinType::EST_Eyeshades:
	case ESkinType::EST_Facemask:
	case ESkinType::EST_Beard:
		return TEXT("EyeSocket");
	case ESkinType::EST_Bag:
		return TEXT("BagSocket");
	}
	return TEXT("NONE");
}


// Called every frame
void USkinActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

