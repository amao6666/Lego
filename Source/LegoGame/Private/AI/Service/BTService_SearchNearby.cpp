// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_SearchNearby.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/LGCharacterBase.h"
#include "Components/PackageActorComponent.h"
#include "LegoGame/LegoGame.h"
#include "Scene/SceneItemActor.h"
#include "Subsystem/PropsSubsystem.h"
#include "Weapon/WeaponActor.h"

UBTService_SearchNearby::UBTService_SearchNearby()
{
	NodeName = TEXT("搜索附近");
	SearchRadius = 150;
	bCreateNodeInstance = true;
}

void UBTService_SearchNearby::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 球形检测附近的目标
	TArray<FHitResult> HitResults;
	FCollisionShape Shape;
	Shape.ShapeType = ECollisionShape::Sphere;
	Shape.Sphere.Radius = SearchRadius;
	// 检测起点
	FVector Location = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	// 忽略自己
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerComp.GetAIOwner()->GetPawn());

	DrawDebugSphere(GetWorld(), Location, 150, 8, FColor::Green, false, 3);

	if (GetWorld()->SweepMultiByObjectType(HitResults, Location, Location, FRotator::ZeroRotator.Quaternion(), ECC_SceneItem, Shape, Params))
	{
		for (auto Hit : HitResults)
		{
			if (!IsValid(Hit.GetActor())) continue;
			if (ALGCharacterBase* Player = Cast<ALGCharacterBase>(OwnerComp.GetAIOwner()->GetPawn()))
			{
				if (ASceneItemActor* SceneItemActor = Cast<ASceneItemActor>(Hit.GetActor()))
				{
					if (SceneItemActor->GetID() < WEAPON_INDEX)
					{
						Player->GetPackageComponent()->PutonSkin(SceneItemActor);	
					}
					else
					{
						Player->GetPackageComponent()->EquipWeapon(SceneItemActor);
					}
					break;
				}
			}
		}
	}
}

void UBTService_SearchNearby::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	if (ALGCharacterBase* Player = Cast<ALGCharacterBase>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		Player->GetPackageComponent()->OnEquipWeapon.AddUObject(this, &UBTService_SearchNearby::OnEquipWeapon);
		Player->OnDamaged.AddUObject(this, &UBTService_SearchNearby::OnDamaged);
		MyCharacterBase = Player;
	}
}

void UBTService_SearchNearby::OnEquipWeapon(AWeaponActor* WeaponActor)
{
	if (!MyCharacterBase) return;
	if (AAIController* AaiController = Cast<AAIController>(MyCharacterBase->GetController()))
	{
		AaiController->GetBlackboardComponent()->SetValueAsBool(TEXT("bHoldWeapon"), true);
	}
}

void UBTService_SearchNearby::OnDamaged(ALGCharacterBase* HitCharacter)
{
	if (!MyCharacterBase) return;
	if (AAIController* AaiController = Cast<AAIController>(MyCharacterBase->GetController()))
	{
		AaiController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitCharacter);
	}
}


