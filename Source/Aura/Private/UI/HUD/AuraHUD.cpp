// Copyright Dark Horse
/**
 * @file AuraHUD.cpp
 * @brief Implementation of the AAuraHUD class, responsible for managing the HUD in the Aura game.
 * 
 * This file contains the implementation of the AAuraHUD class, which is responsible for initializing
 * and managing the overlay widget controller and the main HUD widget.
 * 
 * @copyright Dark Horse
 */

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

/**
 * @brief Retrieves the overlay widget controller, creating it if necessary.
 * 
 * This function checks if the OverlayWidgetController is already created. If not, it creates a new instance
 * of UOverlayWidgetController, initializes it with the provided parameters, and returns it.
 * 
 * @param WidgetControllerParams Parameters required to initialize the widget controller.
 * @return UOverlayWidgetController* Pointer to the overlay widget controller.
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWIdgetController( const FWidgetControllerParams& WidgetControllerParams ) {
	if(!OverlayWidgetController) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

		OverlayWidgetController->InitWidgetController(WidgetControllerParams);

		OverlayWidgetController->BindCallbacksToDependencies();
		
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}


/**
 * @brief Initializes the overlay HUD.
 * 
 * This function initializes the overlay HUD by creating the main widget, setting up the widget controller,
 * and binding the necessary callbacks.
 * 
 * @param Controller The player controller.
 * @param PlayerState The player state.
 * @param AbilitySystemComponent The ability system component.
 * @param AbilitySet The attribute set.
 */
void AAuraHUD::InitOverlay( APlayerController* Controller, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AbilitySet ) {
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(Controller, PlayerState, AbilitySystemComponent, AbilitySet);
	UOverlayWidgetController* WidgetController = GetOverlayWIdgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitValues();

	OverlayWidget->AddToViewport();
}
