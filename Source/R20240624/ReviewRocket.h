// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReviewRocket.generated.h"

UCLASS()
class R20240624_API AReviewRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReviewRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<class UBoxComponent> Box;
	TObjectPtr<class UStaticMeshComponent> Rocket;
	TObjectPtr<class UProjectileMovementComponent> Movement;
};
