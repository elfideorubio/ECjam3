// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Extracredits.h"
#include "Entities/Minigame/MinigameActor.h"
#include "Entities/Interaction/InteractableActor.h"
#include "Components/BoxComponent.h"

#include "GameFramework/Actor.h"
#include "InteractActor.generated.h"

UCLASS()
class EXTRACREDITS_API AInteractActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	class USceneComponent * RootScene;

	// Our box component that will be used for detecting the interaction range.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	class UBoxComponent * InteractionBox;

	// Can we interact with the entity?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool canInteract = true;

	// The minigame we want to initialise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	AMinigameActor * Minigame;

	// [Actor, Description] Objects that will be affected by the interaction. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TMap<AInteractableActor *, FString> EffectedObjects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Premliminarily check our actor overlap.
	UFUNCTION()
	void OnActorEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void OnEnterRange(AActor * actor);
	void OnEnterRange_Implementation(AActor * actor);

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void OnExitRange(AActor * actor);
	void OnExitRange_Implementation(AActor * actor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void OnInteractStart(AActor * player);
	void OnInteractStart_Implementation(AActor * actor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteractFinish(AActor * player, bool success);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void DoInteractions(bool success);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void FinishInteraction(AActor * actor, bool success);
};
