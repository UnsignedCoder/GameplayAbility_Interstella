// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "Aura/Public/BaseCharacter/GameCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class AURA_API AEnemy : public AGameCharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
};
