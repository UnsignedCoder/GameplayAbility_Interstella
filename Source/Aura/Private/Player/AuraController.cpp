// Copyright Dark Horse



#include "Aura/Public/Player/AuraController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/TargetInterface.h"


AAuraController::AAuraController() {
	bReplicates = true;
}

void AAuraController::PlayerTick( float DeltaTime ) {
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraController::BeginPlay() {
	Super::BeginPlay();
	check(AuraMappingContext);

	InitialiseInputMappings();
}

void AAuraController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraController::HandleMoveAction);
}

void AAuraController::InitialiseInputMappings() {
	UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(PlayerSubsystem);
	PlayerSubsystem->AddMappingContext(AuraMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::SlashedCircle;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraController::HandleMoveAction( const FInputActionValue& Value ) {
	const FVector2D MovementAxis = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, MovementAxis.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementAxis.X);
	}
}

void AAuraController::CursorTrace() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if(!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = Cast<ITargetInterface>(CursorHit.GetActor());

	if (LastActor == nullptr) {
		if (CurrentActor != nullptr) {
			CurrentActor->HighlightActor();
		} else { }
	} else {
		if (LastActor != CurrentActor) {
			LastActor->UnhighlightActor();
			
			if (CurrentActor != nullptr) {
				CurrentActor->HighlightActor();
			} else { }
		}
	}
}
