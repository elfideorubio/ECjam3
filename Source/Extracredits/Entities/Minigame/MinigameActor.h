// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MinigameActor.generated.h"

UCLASS()
class EXTRACREDITS_API AMinigameActor : public APawn
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:	
	// Sets default values for this actor's properties
	AMinigameActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector startLoc;
	FRotator startRot;

	bool isTweeningCamera = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the minigame
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void start(APawn * player);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnMinigameStart(APawn * player);
};
