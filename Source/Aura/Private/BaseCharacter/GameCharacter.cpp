// Copyright Dark Horse

#include "Aura/Public/BaseCharacter/GameCharacter.h"

/**
 * @brief Constructor for the AGameCharacter class.
 * 
 * Initializes the base character with default settings:
 * - Enables actor tick for potential per-frame updates
 * - Creates and attaches a weapon skeletal mesh component
 * - Configures weapon collision to be disabled
 * 
 * @note The actor tick is enabled by default for potential dynamic behavior
 */
AGameCharacter::AGameCharacter()
{
	// Enable actor tick to allow per-frame updates if needed
	PrimaryActorTick.bCanEverTick = true;

	// Create and configure the weapon skeletal mesh component
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

/**
 * @brief Initializes the Game Character when the game starts or when spawned.
 * 
 * Calls the parent class's BeginPlay method to ensure proper initialization.
 * Currently does not add any additional initialization logic.
 * 
 * @note Overrides the base class BeginPlay method for potential future extensions
 */
void AGameCharacter::BeginPlay()
{
	// Call parent class initialization
	Super::BeginPlay();
}

/**
 * @brief Retrieves the Ability System Component for this character.
 * 
 * Returns the AbilitySystemComponent associated with this character,
 * allowing access to gameplay abilities and effects.
 * 
 * @return UAbilitySystemComponent* Pointer to the character's ability system component
 * @note Const method that provides read-only access to the ability system component
 */
UAbilitySystemComponent* AGameCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}