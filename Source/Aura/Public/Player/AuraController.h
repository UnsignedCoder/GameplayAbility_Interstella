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

UCLASS()
class AURA_API AAuraController : public APlayerController {
	GENERATED_BODY()

public:
	AAuraController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	void InitialiseInputMappings();

	void HandleMoveAction( const FInputActionValue& Value );

	void CursorTrace();

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	ITargetInterface* LastActor;

	ITargetInterface* CurrentActor;
};
