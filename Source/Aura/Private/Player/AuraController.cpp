// Copyright Dark Horse

#include "Aura/Public/Player/AuraController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/TargetInterface.h"

/**
 * @brief Constructor for the AuraController class.
 * 
 * Initializes the controller with replication enabled, allowing network synchronization
 * of controller-specific properties and actions across multiplayer sessions.
 * 
 * @note Replication is crucial for maintaining consistent game state in multiplayer environments
 */
AAuraController::AAuraController() {
    bReplicates = true;
}

/**
 * @brief Called every frame to update player-specific tick operations.
 * 
 * Overrides the base PlayerTick method to perform additional per-frame actions.
 * Currently used to execute cursor tracing for interactive object detection.
 * 
 * @param DeltaTime The time elapsed since the last frame
 * 
 * @note Runs on every frame, allowing continuous updates to player interactions
 */
void AAuraController::PlayerTick(float DeltaTime) {
    Super::PlayerTick(DeltaTime);

    CursorTrace();
}

/**
 * @brief Initializes the controller when play begins.
 * 
 * Performs essential setup operations when the game starts:
 * 1. Calls the parent class BeginPlay method
 * 2. Validates the existence of input mapping context
 * 3. Initializes input mappings and controller settings
 * 
 * @throws Assertion error if AuraMappingContext is not set
 */
void AAuraController::BeginPlay() {
    Super::BeginPlay();
    check(AuraMappingContext);

    InitialiseInputMappings();
}

/**
 * @brief Configures the input component for the controller.
 * 
 * Sets up enhanced input bindings:
 * 1. Casts the input component to UEnhancedInputComponent
 * 2. Binds the move action to the HandleMoveAction method
 * 
 * @note Uses CastChecked for type-safe input component conversion
 * @note Establishes the connection between input actions and gameplay responses
 */
void AAuraController::SetupInputComponent() {
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraController::HandleMoveAction);
}

/**
 * @brief Initializes input mapping and cursor settings.
 * 
 * Performs comprehensive input and UI setup:
 * 1. Adds input mapping context to the local player
 * 2. Configures mouse cursor visibility and appearance
 * 3. Sets up input mode to combine game and UI interactions
 * 
 * Key configuration steps:
 * - Enables mouse cursor
 * - Sets cursor to slashed circle design
 * - Configures mouse lock and capture behavior
 * 
 * @note Ensures smooth integration of input systems and user interface
 */
void AAuraController::InitialiseInputMappings() {
    // Retrieve the Enhanced Input local player subsystem
    UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if(PlayerSubsystem) {
       // Add the predefined input mapping context
       PlayerSubsystem->AddMappingContext(AuraMappingContext, 0);
    }

    // Configure cursor settings
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::SlashedCircle;

    // Set up input mode to support both game and UI interactions
    FInputModeGameAndUI InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
    InputModeData.SetHideCursorDuringCapture(false);
    SetInputMode(InputModeData);
}

/**
 * @brief Handles movement input action.
 * 
 * Translates 2D input values into 3D movement for the controlled pawn:
 * 1. Extracts movement axis values
 * 2. Calculates movement direction based on current camera rotation
 * 3. Applies movement input to the controlled pawn
 * 
 * @param Value Input action value containing 2D movement vector
 * 
 * @note Supports movement in forward/backward and right/left directions
 * @note Respects current camera orientation for movement direction
 */
void AAuraController::HandleMoveAction(const FInputActionValue& Value) {
    // Extract 2D movement vector
    const FVector2D MovementAxis = Value.Get<FVector2D>();
    
    // Calculate movement rotation based on current control rotation
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

    // Determine forward and right directions
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    // Apply movement to controlled pawn
    if(APawn* ControlledPawn = GetPawn<APawn>()) {
       ControlledPawn->AddMovementInput(ForwardDirection, MovementAxis.Y);
       ControlledPawn->AddMovementInput(RightDirection, MovementAxis.X);
    }
}

/**
 * @brief Performs cursor tracing to detect and interact with objects under the cursor.
 * 
 * Implements a sophisticated cursor interaction system:
 * 1. Performs a visibility trace under the cursor
 * 2. Detects and manages actor highlighting
 * 3. Tracks changes in targeted actors
 * 
 * Interaction logic:
 * - Highlights newly targeted actors
 * - Unhighlights previously targeted actors
 * - Handles transitions between different interactive actors
 * 
 * @note Runs every frame during PlayerTick
 * @note Uses the TargetInterface for actor interaction
 */
void AAuraController::CursorTrace() {
    // Perform hit detection under cursor
    FHitResult CursorHit;
    GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

    // Exit if no blocking hit detected
    if(!CursorHit.bBlockingHit) return;

    // Update current and last actors
    LastActor = CurrentActor;
    CurrentActor = Cast<ITargetInterface>(CursorHit.GetActor());

    // Handle actor highlighting logic
    if (LastActor == nullptr) {
       if (CurrentActor != nullptr) {
          CurrentActor->HighlightActor();
       }
    } else {
       if (LastActor != CurrentActor) {
          LastActor->UnhighlightActor();
          
          if (CurrentActor != nullptr) {
             CurrentActor->HighlightActor();
          }
       }
    }
}