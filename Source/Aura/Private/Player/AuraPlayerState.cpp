// Copyright Dark Horse

#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

/**
 * @brief Constructor for the AuraPlayerState class.
 * 
 * Initializes the player state with key gameplay systems:
 * 1. Creates and configures the Ability System Component
 * 2. Sets up network replication for the ability system
 * 3. Creates the Attribute Set for tracking player attributes
 * 4. Configures network update frequency
 * 
 * Key Configuration Details:
 * - Ability System Component is created with replication enabled
 * - Replication mode set to Mixed for balanced network performance
 * - Net update frequency increased for more responsive state updates
 * 
 * @note Essential for setting up the player's gameplay capabilities
 * @note Ensures proper networking and attribute tracking
 */
AAuraPlayerState::AAuraPlayerState() {
    // Create Ability System Component with replication
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    // Create Attribute Set for tracking player attributes
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));

    // Increase network update frequency for more responsive state updates
    NetUpdateFrequency = 100.0f;
}

/**
 * @brief Retrieves the Ability System Component associated with this player state.
 * 
 * Provides access to the player's ability system for external systems and components.
 * 
 * @return UAbilitySystemComponent* Pointer to the player's Ability System Component
 * 
 * @note Const method ensuring the component cannot be modified through this accessor
 * @note Critical for ability and attribute interactions across the game system
 */
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const {
    return AbilitySystemComponent;
}