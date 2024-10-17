// Copyright Dark Horse

#include "UI/WidgetController/AuraWidgetController.h"


/**
 * Initializes the widget controller with the provided parameters.
 *
 * @param WControllerParams The parameters used to initialize the widget controller, including:
 * - PLayerController: The player controller.
 * - PlayerState: The player state.
 * - AbilitySystemComponent: The ability system component.
 * - AbilitySet: The ability set.
 */
void UAuraWidgetController::InitWidgetController( const FWidgetControllerParams& WControllerParams ) {
	PLayerController = WControllerParams.PLayerController;
	PlayerState = WControllerParams.PlayerState;
	AbilitySystemComponent = WControllerParams.AbilitySystemComponent;
	AttributeSet = WControllerParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitValues() {}
