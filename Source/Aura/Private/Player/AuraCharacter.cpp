// Copyright Dark Horse


#include "Aura/Public/Player/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"



/**
 * @brief Sets default values for this character's properties.
 */
AAuraCharacter::AAuraCharacter() {
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Disable controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AAuraCharacter::BeginPlay() {
	Super::BeginPlay();
	
}


/**
 * @brief Initializes the Aura Ability System for the character.
 * @param PController The controller possessing the character.
 */
void AAuraCharacter::InitialiseAuraAbilitySystem(AController* PController) {
	// Get the player state and ability system component
	if (AAuraPlayerState* AuraPlayerState = PController->GetPlayerState<AAuraPlayerState>()) {
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();

		// Get the controller and HUD, and initialize the overlay
		if (AAuraController* AuraController = Cast<AAuraController>(GetController())) {
			AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraController->GetHUD());
			if (AuraHUD) {
				AuraHUD->InitOverlay(AuraController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			}
		}
	}
}

/**
 * @brief Called when the character is possessed by a controller.
 * @param NewController The new controller possessing the character.
 */
void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	// Initialize the Aura Ability System with the new controller
	InitialiseAuraAbilitySystem(NewController);
}
