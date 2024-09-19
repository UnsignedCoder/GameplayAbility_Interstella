// Copyright Dark Horse


#include "Aura/Public/Enemy/Enemy.h"


// Sets default values
AEnemy::AEnemy() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay() {
	Super::BeginPlay();
	
}

void AEnemy::HighlightActor() {
	bIsHighlighted = true;
}
void AEnemy::UnhighlightActor() {
	bIsHighlighted = false;
}

