// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Extracredits.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class EXTRACREDITS_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void Interact(bool sucess);
};
