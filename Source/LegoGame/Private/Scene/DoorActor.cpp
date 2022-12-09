// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/DoorActor.h"
#include "Character/LGCharacterBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnSphereComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnSphereComponentEndOverlap);
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoorActor::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ALGCharacterBase>(OtherActor))
	{
		if (bPlayAnim) return;
		bPlayAnim = true;
		CurveDirection = 1;
		// CosValue > 0在右侧，否则在左侧
		OpenDirection = FVector::DotProduct(GetActorRightVector(),
			(OtherActor->GetActorLocation() - GetActorLocation()).GetSafeNormal()) > 0 ? 1 : -1;
		
	}
}

void ADoorActor::OnSphereComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ALGCharacterBase>(OtherActor))
	{
		if (bPlayAnim) return;
		bPlayAnim = true;
		CurveDirection = -1;
	}
}

void ADoorActor::UpdateAnim(float DeltaTime)
{
	if (!bPlayAnim || !DoorAnim)
	{
		return;
	}
	CurrentCurveTime += DeltaTime * CurveDirection;
	float StartTime, EndTime;
	DoorAnim->GetTimeRange(StartTime, EndTime);
	if (CurrentCurveTime < StartTime)
	{
		CurrentCurveTime = StartTime;
		bPlayAnim = false;
	}
	if (CurrentCurveTime > EndTime)
	{
		CurrentCurveTime = EndTime;
		bPlayAnim = false;
	}
	float Value = DoorAnim->GetFloatValue(CurrentCurveTime) * OpenDirection;
	StaticMeshComponent->SetRelativeRotation(FRotator(0, 90 * Value, 0));
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateAnim(DeltaTime);
}

