// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractActor.h"
#include "ExtracreditsCharacter.h"

// Sets default values
AInteractActor::AInteractActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create our scene
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// Create our box component.
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionRange"));
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractActor::OnActorEnter);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractActor::OnActorExit);
}

// Called when the game starts or when spawned
void AInteractActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called once an actor enters the range of the 
void AInteractActor::OnActorEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// Try to convert the actor to a player character
	AExtracreditsCharacter * player = Cast<AExtracreditsCharacter>(OtherActor);

	// We want to return if it is not a player.
	if (player == NULL) { return; }

	// Fire our event.
	OnEnterRange(OtherActor);
}

// Called once an actor enters the range of the 
void AInteractActor::OnActorExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	// Try to convert the actor to a player character
	AExtracreditsCharacter * player = Cast<AExtracreditsCharacter>(OtherActor);

	// We want to return if it is not a player.
	if (player == NULL) { return; }

	// Fire our event.
	OnExitRange(OtherActor);
}

// Called once an actor enters the range of the 
void AInteractActor::OnEnterRange_Implementation(AActor* actor) {
	// Try to convert the actor to a player character
	AExtracreditsCharacter * player = Cast<AExtracreditsCharacter>(actor);

	// We want to return if it is not a player.

	if (player == NULL) { return; }
	if (!player->InteractsInRange.Contains(this)) {
		player->InteractsInRange.Add(this);
	}
}

// Called once an actor enters the range of the 
void AInteractActor::OnExitRange_Implementation(AActor* actor) {
	// Try to convert the actor to a player character
	AExtracreditsCharacter * player = Cast<AExtracreditsCharacter>(actor);

	// We want to return if it is not a player.
	if (player == NULL) { return; }

	if (player->InteractsInRange.Contains(this)) {
		player->InteractsInRange.Remove(this);
	}
}

// Called once an actor enters the range of the 
void AInteractActor::OnInteractStart_Implementation(AActor* actor) {
	// Default, finish with success
	FinishInteraction(actor, true);
}

void AInteractActor::DoInteractions(bool success) {
	for (const TPair<AInteractableActor *, FString>& pair : EffectedObjects) {
		pair.Key->Interact(success);
	}
}

void AInteractActor::FinishInteraction(AActor* actor, bool success) {
	// Default, finish with success
	OnInteractFinish(actor, true);
}
