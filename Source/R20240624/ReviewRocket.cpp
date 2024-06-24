// Fill out your copyright notice in the Description page of Project Settings.


#include "ReviewRocket.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AReviewRocket::AReviewRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	Rocket->SetupAttachment(Box);
	Rocket->SetRelativeRotation(FRotator(-90, 0, 0));



	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));

	if (SM_Rocket.Succeeded())
	{
		Rocket->SetStaticMesh(SM_Rocket.Object);
	}

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.0f;
	Movement->MaxSpeed = 1000.0f;
	Movement->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AReviewRocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReviewRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

