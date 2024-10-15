// Copyright Dark Horse


#include "Aura/Public/Enemy/Enemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


// Sets default values
AEnemy::AEnemy() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

// Called when the game starts or when spawned 
void AEnemy::BeginPlay() {
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AEnemy::HighlightActor() {
	bTargetIsHighlighted = true;
}
void AEnemy::UnhighlightActor() {
	bTargetIsHighlighted = false;
}

