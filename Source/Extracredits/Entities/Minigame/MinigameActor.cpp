// Fill out your copyright notice in the Description page of Project Settings.

#include "MinigameActor.h"
#include "ExtracreditsCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMinigameActor::AMinigameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AMinigameActor::start(APawn * player) {
	AController * controller = player->GetController();
	controller->Possess(this);

	AExtracreditsCharacter * character = Cast<AExtracreditsCharacter>(player);
	if (!character) {
		return;
	}

	OnMinigameStart(player);

	FVector loc = character->FollowCamera->GetComponentLocation();
	FRotator rot = character->FollowCamera->GetComponentRotation();

	FollowCamera->SetWorldLocationAndRotation(loc, rot);

	isTweeningCamera = true;
}

