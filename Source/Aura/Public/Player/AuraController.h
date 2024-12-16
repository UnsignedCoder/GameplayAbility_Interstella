// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraController.generated.h"

class AAuraCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ITargetInterface;

/**
 * @brief Custom player controller for the Aura game, managing input and targeting.
 * 
 * AAuraController extends the base PlayerController to provide specialized
 * input handling, movement, and target tracking functionality. It manages
 * input mappings, character movement, and cursor-based interaction with 
 * targetable actors in the game world.
 * 
 * Key Responsibilities:
 * - Handle player input mappings
 * - Process character movement
 * - Perform cursor tracing for targeting
 * - Manage interactions with targetable actors
 */
UCLASS()
class AURA_API AAuraController : public APlayerController {
	GENERATED_BODY()

public:
	/**
	* @brief Constructor for the AAuraController class.
	* 
	* Initializes the player controller with default settings.
	*/
	AAuraController();

	/**
	* @brief Called every frame to update the controller's state.
	* 
	* Overrides the base PlayerTick method to perform per-frame updates,
	* such as cursor tracing and target tracking.
	* 
	* @param DeltaTime Time elapsed since the last frame
	*/
	virtual void PlayerTick( float DeltaTime ) override;

protected:
	/**
	* @brief Called when the game starts or when the controller is spawned.
	* 
	* Overrides BeginPlay to perform initial setup and initialization.
	*/
	virtual void BeginPlay() override;

	/**
	* @brief Configures input component and bindings for the player controller.
	* 
	* Sets up input actions and mappings for player interactions.
	*/
	virtual void SetupInputComponent() override;

	/**
	* @brief Initializes input mappings for the player controller.
	* 
	* Configures the input mapping context and associates input actions
	* with their corresponding handler methods.
	*/
	void InitialiseInputMappings();

	/**
	* @brief Handles player movement input.
	* 
	* Processes the input action value to move the character.
	* 
	* @param Value Input action value representing movement input
	*/
	void HandleMoveAction( const FInputActionValue& Value );

	/**
	* @brief Performs cursor tracing to detect and interact with targetable actors.
	* 
	* Traces from the cursor position to identify actors implementing the 
	* ITargetInterface, managing highlighting and unhighlighting.
	*/
	void CursorTrace();

private:
	/**
	* @brief Input mapping context for the Aura game.
	* 
	* Defines the set of input mappings used by the player controller.
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;

	/**
	* @brief Input action for character movement.
	* 
	* Represents the input action used to control character movement.
	*/
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	/**
	* @brief Tracks the previously highlighted actor.
	* 
	* Stores a reference to the last actor that was under the cursor,
	* used for managing target highlighting and unhighlighting.
	*/
	TObjectPtr<ITargetInterface> LastActor;

	/**
	* @brief Tracks the currently highlighted actor.
	* 
	* Stores a reference to the actor currently under the cursor,
	* used for managing target interaction.
	*/
	TObjectPtr<ITargetInterface> CurrentActor;
};
