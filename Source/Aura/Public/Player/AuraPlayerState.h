// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/**
 * @brief AAuraPlayerState class that extends APlayerState and implements IAbilitySystemInterface.
 *
 * This class is responsible for managing the player's state, including the ability system component
 * and attribute set.
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface {
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for AAuraPlayerState.
	 */
	AAuraPlayerState();

	/**
	 * @brief Gets the ability system component.
	 * @return A pointer to the UAbilitySystemComponent.
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/**
	 * @brief Gets the attribute set.
	 * @return A pointer to the UAttributeSet.
	 */
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	/**
	 * @brief The ability system component associated with the player state.
	 */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/**
	 * @brief The attribute set associated with the player state.
	 */
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
