// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "Aura/Public/BaseCharacter/GameCharacter.h"
#include "AuraCharacter.generated.h"

class AAuraPlayerState;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AGameCharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacter();
	
	virtual void PossessedBy( AController* NewController ) override;

	virtual void OnRep_PlayerState() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitAuraAbilitySystem();

	void InitAuraHUD() const;
private:
	// The player state associated with this character
	UPROPERTY()
	TObjectPtr<AAuraPlayerState> AuraPlayerState;
	
public:
};
