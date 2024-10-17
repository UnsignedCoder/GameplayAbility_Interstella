// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "Aura/Public/BaseCharacter/GameCharacter.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AGameCharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacter();
	
	virtual void PossessedBy( AController* NewController ) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitialiseAuraAbilitySystem(AController* PController);
private:
	  
public:
};
