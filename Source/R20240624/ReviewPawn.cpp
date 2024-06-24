// Fill out your copyright notice in the Description page of Project Settings.


#include "ReviewPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ReviewRocket.h"

// Sets default values
AReviewPawn::AReviewPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(45.0f, 65.0f, 15.0f));


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Mashes/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Sm_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Mashes/SM_P38_Propeller.SM_P38_Propeller'"));

	if (Sm_Propeller.Succeeded())
	{
		Left->SetStaticMesh(Sm_Propeller.Object);
		Right->SetStaticMesh(Sm_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(36.5f, 21.0f, 0.5f));
	Right->SetRelativeLocation(FVector(36.5f, -21.0f, 0.5f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	Arrow->SetRelativeLocation(FVector(90.9f, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->TargetArmLength = 200.0f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	MaxScale = 0.5f;


}

// Called when the game starts or when spawned
void AReviewPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReviewPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), MaxScale);

	Left->AddRelativeRotation(FRotator(0, 0, 3600.f * DeltaTime));
	Right->AddRelativeRotation(FRotator(0, 0, 3600.f * DeltaTime));



}

// Called to bind functionality to input
void AReviewPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AReviewPawn::Fire);
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &AReviewPawn::BoostPressed);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &AReviewPawn::BoostReleased);
	PlayerInputComponent->BindAxis("Pitch", this, &AReviewPawn::Pitch);
	PlayerInputComponent->BindAxis("Roll", this, &AReviewPawn::Roll);

}

void AReviewPawn::Fire()
{
	GetWorld()->SpawnActor<AReviewRocket>(Arrow->K2_GetComponentLocation(), Arrow->K2_GetComponentRotation());
}

void AReviewPawn::BoostPressed()
{
	MaxScale = 1.0f;
}

void AReviewPawn::BoostReleased()
{
	MaxScale = 0.5f;
}

void AReviewPawn::Pitch(float Value)
{
	float Dir = FMath::Clamp(Value, -1.0f, 1.0f);
	AddActorLocalRotation(FRotator(Dir * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));

}

void AReviewPawn::Roll(float Value)
{
	float Dir = FMath::Clamp(Value, -1.0f, 1.0f);
	AddActorLocalRotation(FRotator(0, 0, Dir * 60.0f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

