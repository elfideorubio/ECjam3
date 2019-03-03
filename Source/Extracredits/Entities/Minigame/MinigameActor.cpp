// Fill out your copyright notice in the Description page of Project Settings.

#include "MinigameActor.h"
#include "Entities/Interaction/InteractActor.h"
#include "ExtracreditsCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMinigameActor::AMinigameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our scene
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 30; // The camera follows at this distance behind the character	

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
}

// Called when the game starts or when spawned
void AMinigameActor::BeginPlay()
{
	Super::BeginPlay();

	startLoc = FollowCamera->GetComponentLocation();
	startRot = FollowCamera->GetComponentRotation();
}

// Called every frame
void AMinigameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isTweeningCamera) {

		FVector newPos = FMath::VInterpTo(FollowCamera->GetComponentLocation(), startLoc, DeltaTime, 3.0f);
		FRotator newRot = FMath::RInterpTo(FollowCamera->GetComponentRotation(), startRot, DeltaTime, 3.0f);

		FollowCamera->SetWorldLocationAndRotation(newPos, newRot);

		if (FVector::Dist(FollowCamera->GetComponentLocation(), startLoc) <= 1.0f) {
			FollowCamera->SetWorldLocationAndRotation(startLoc, startRot);
			isTweeningCamera = false;
		}
	}

}

void AMinigameActor::start(APawn * player, AActor * initialiser) {
	AController * controller = player->GetController();
	controller->Possess(this);

	AExtracreditsCharacter * character = Cast<AExtracreditsCharacter>(player);
	if (!character) {
		return;
	}

	OnMinigameStart(player, initialiser);

	FVector loc = character->FollowCamera->GetComponentLocation();
	FRotator rot = character->FollowCamera->GetComponentRotation();

	FollowCamera->SetWorldLocationAndRotation(loc, rot);

	isTweeningCamera = true;
}

void AMinigameActor::finish(APawn * player, bool success, AActor * initialiser) {
	AController * controller = this->GetController();
	controller->Possess(player);

	AInteractActor * interact = Cast<AInteractActor>(initialiser);
	if (!interact) {
		return;
	}

	interact->OnMinigameFinish(player, success, this);
	OnMinigameFinish(player, success, initialiser);
}

void AMinigameActor::OnMinigameStart_Implementation(APawn * player, AActor * initialiser) {
	initPlayer = player;
	initActor = initialiser;
}

void AMinigameActor::OnMinigameFinish_Implementation(APawn * player, bool success, AActor * initialiser) {

}
