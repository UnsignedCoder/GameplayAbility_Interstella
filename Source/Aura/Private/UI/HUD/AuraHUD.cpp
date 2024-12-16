// Copyright Dark Horse


/**
 * @file AuraHUD.cpp
 * @brief Implementation of the AAuraHUD class, responsible for managing the HUD in the Aura game.
 * 
 * This file contains the implementation of the AAuraHUD class, which is responsible for initializing
 * and managing the overlay widget controller and the main HUD widget.
 * 
 * The AAuraHUD class serves as a central manager for creating and setting up the user interface
 * elements, specifically handling the overlay widget and its associated controller.
 * 
 * Key Responsibilities:
 * - Creating and managing the overlay widget
 * - Initializing the widget controller with necessary game state information
 * - Ensuring proper setup of UI elements at game start
 * 
 * @copyright Dark Horse
 */

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

/**
 * @brief Retrieves or creates the overlay widget controller.
 * 
 * This method implements a lazy initialization pattern for the OverlayWidgetController. 
 * If the controller doesn't exist, it:
 * 1. Creates a new UOverlayWidgetController instance
 * 2. Initializes the controller with provided parameters
 * 3. Binds necessary callbacks to dependencies
 * 
 * The method ensures that only one instance of the OverlayWidgetController is created 
 * and reused across multiple calls.
 * 
 * @param WidgetControllerParams Struct containing essential parameters for widget controller initialization
 *        - Includes PlayerController, PlayerState, AbilitySystemComponent, and AttributeSet
 * 
 * @return UOverlayWidgetController* Pointer to the initialized overlay widget controller
 * 
 * @note This method uses lazy initialization to create the widget controller only when needed
 * @note The created widget controller is stored and reused for subsequent calls
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams) {
    // Check if the OverlayWidgetController has already been created
    if(!OverlayWidgetController) {
       // Create a new OverlayWidgetController using the specified class
       OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

       // Initialize the widget controller with provided parameters
       OverlayWidgetController->InitWidgetController(WidgetControllerParams);

       // Bind callbacks to handle attribute changes and other dependencies
       OverlayWidgetController->BindCallbacksToDependencies();
       
       return OverlayWidgetController;
    }
    // Return existing OverlayWidgetController if already created
    return OverlayWidgetController;
}

/**
 * @brief Initializes the game's overlay HUD.
 * 
 * This method is responsible for setting up the primary user interface for the game.
 * It performs the following critical operations:
 * 1. Validates the existence of required widget classes
 * 2. Creates the overlay widget
 * 3. Sets up the widget controller
 * 4. Broadcasts initial attribute values
 * 5. Adds the widget to the game viewport
 * 
 * The initialization process ensures that the HUD is fully prepared with all 
 * necessary connections between the game state and UI elements.
 * 
 * @param Controller Pointer to the PlayerController managing the player's input and view
 * @param PlayerState Pointer to the PlayerState containing persistent player information
 * @param AbilitySystemComponent Pointer to the component managing player abilities and attributes
 * @param AbilitySet Pointer to the set of attributes for the player
 * 
 * @throws Assertion error if OverlayWidgetClass or OverlayWidgetControllerClass are not set
 * 
 * @note This method is typically called during player initialization or level start
 * @note Uses checkf() to provide clear error messages if required classes are not configured
 */
void AAuraHUD::InitOverlay(APlayerController* Controller, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AbilitySet) {
    // Validate that required widget classes are set
    checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in AuraHUD"));
    checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in AuraHUD"));

    // Create the overlay widget using the specified widget class
    UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

    // Cast to AuraUserWidget for type-specific operations
    OverlayWidget = Cast<UAuraUserWidget>(Widget);

    // Prepare widget controller parameters
    const FWidgetControllerParams WidgetControllerParams(Controller, PlayerState, AbilitySystemComponent, AbilitySet);
    
    // Get or create the overlay widget controller
    UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

    // Connect the widget controller to the overlay widget
    OverlayWidget->SetWidgetController(WidgetController);

    // Broadcast initial attribute values to update UI
    WidgetController->BroadcastInitValues();

    // Add the overlay widget to the game viewport
    OverlayWidget->AddToViewport();
}