// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Extracredits.h"
#include "GameFramework/Pawn.h"
#include "MinigameActor.generated.h"

UCLASS()
class EXTRACREDITS_API AMinigameActor : public APawn
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMinigameActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		class USceneComponent * RootScene;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector startLoc;
	FRotator startRot;

	// The initialising player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	APawn * initPlayer;

	// The initialising actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AActor * initActor;

	bool isTweeningCamera = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the minigame
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void start(APawn * player, AActor * initialiser);

	// Start the minigame
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void finish(APawn * player, bool success, AActor * initialiser);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void OnMinigameStart(APawn * player, AActor * initialiser);
	void OnMinigameStart_Implementation(APawn * player, AActor * initialiser);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void OnMinigameFinish(APawn * player, bool success, AActor * initialiser);
	void OnMinigameFinish_Implementation(APawn * player, bool success, AActor * initialiser);
};
