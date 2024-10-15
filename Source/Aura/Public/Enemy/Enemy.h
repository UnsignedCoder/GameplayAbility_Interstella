// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "Aura/Public/BaseCharacter/GameCharacter.h"
#include "Interaction/TargetInterface.h"
#include "Enemy.generated.h"

UCLASS()
class AURA_API AEnemy : public AGameCharacter, public ITargetInterface {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bTargetIsHighlighted = false;
};
