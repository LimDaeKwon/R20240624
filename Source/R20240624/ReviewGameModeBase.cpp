// Fill out your copyright notice in the Description page of Project Settings.


#include "ReviewGameModeBase.h"
#include "ReviewPawn.h"
#include "ReviewPlayerController.h"
AReviewGameModeBase::AReviewGameModeBase()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Gello"));
	}
	DefaultPawnClass = AReviewPawn::StaticClass();
	PlayerControllerClass = AReviewPlayerController::StaticClass();

}
