// Copyright Dark Horse

#include "Aura/Public/Enemy/Enemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

/**
 * @brief Constructor for the AEnemy class.
 * 
 * Initializes the enemy with default settings:
 * - Disables actor tick for performance optimization
 * - Creates and configures the Ability System Component
 * - Creates the Attribute Set for gameplay-related stats
 * 
 * @note The tick is disabled by default to improve performance
 */
AEnemy::AEnemy() {
    // Disable actor tick to improve performance if no per-frame updates are needed
    PrimaryActorTick.bCanEverTick = false;

    // Create and configure the Ability System Component
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    // Create the Attribute Set to manage enemy's gameplay attributes
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

/**
 * @brief Initializes the Enemy when the game starts or when spawned.
 * 
 * Calls the parent class's BeginPlay method and initializes 
 * the Ability System Component's actor info.
 * 
 * @note This method is crucial for setting up the enemy's initial state
 */
void AEnemy::BeginPlay() {
    // Call parent class initialization
    Super::BeginPlay();
    
    // Initialize the Ability System Component with this enemy as both the owner and avatar
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

/**
 * @brief Highlights the enemy to indicate it is a current target.
 * 
 * Sets the targeting flag to true, which can be used to trigger
 * visual feedback or targeting mechanics.
 * 
 * @note Implements the HighlightActor method from the TargetInterface
 */
void AEnemy::HighlightActor() {
    // Mark the enemy as currently highlighted/targeted
    bTargetIsHighlighted = true;
}

/**
 * @brief Removes the highlight from the enemy.
 * 
 * Clears the targeting flag, indicating the enemy is no longer 
 * the current target.
 * 
 * @note Implements the UnhighlightActor method from the TargetInterface
 */
void AEnemy::UnhighlightActor() {
    // Clear the highlight/targeting flag
    bTargetIsHighlighted = false;
}