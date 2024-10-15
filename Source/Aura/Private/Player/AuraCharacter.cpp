// Copyright Dark Horse


#include "Aura/Public/Player/AuraCharacter.h"

#include <Windows.ApplicationModel.Activation.h>

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"


// Sets default values
AAuraCharacter::AAuraCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AAuraCharacter::BeginPlay() {
	Super::BeginPlay();
	
}

void AAuraCharacter::InitialiseAuraAbilitySystem(AController* PController) {
	if(AAuraPlayerState* AuraPlayerState = PController->GetPlayerState<AAuraPlayerState>()) {
		AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();

		if (AAuraController* AuraController = Cast<AAuraController>(GetController())) {
			AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraController->GetHUD());
			if(AuraHUD) {
				AuraHUD->InitOverlay(AuraController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
			}
		} 
	}	
}

void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	InitialiseAuraAbilitySystem(NewController);
}
