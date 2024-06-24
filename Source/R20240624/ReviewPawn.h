// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ReviewPawn.generated.h"

UCLASS()
class R20240624_API AReviewPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AReviewPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Fire();
	void BoostPressed();
	void BoostReleased();
	void Pitch(float Value);
	void Roll(float Value);



	TObjectPtr<class UBoxComponent> Box;
	TObjectPtr<class UStaticMeshComponent> Body;
	TObjectPtr<class UStaticMeshComponent> Left;
	TObjectPtr<class UStaticMeshComponent> Right;
	TObjectPtr<class UArrowComponent> Arrow;
	TObjectPtr<class UFloatingPawnMovement> FloatingMovement;
	TObjectPtr<class UCameraComponent> Camera;
	TObjectPtr<class USpringArmComponent> SpringArm;

	float MaxScale;

};
