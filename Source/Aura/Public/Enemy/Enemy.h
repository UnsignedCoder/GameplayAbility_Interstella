// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "Aura/Public/BaseCharacter/GameCharacter.h"
#include "Interaction/TargetInterface.h"
#include "Enemy.generated.h"

/**
 * @brief Represents an enemy character in the game world.
 * 
 * AEnemy is a specialized character class that inherits from AGameCharacter
 * and implements the ITargetInterface for targeting mechanics. It provides
 * basic enemy functionality and can be highlighted or unhighlighted during
 * gameplay interactions.
 * 
 * @note Derives from AGameCharacter and implements ITargetInterface
 */
UCLASS()
class AURA_API AEnemy : public AGameCharacter, public ITargetInterface {
    GENERATED_BODY()

public:
    /**
     * @brief Constructor for the AEnemy class.
     * 
     * Initializes default properties and sets up the enemy character.
     */
    AEnemy();

protected:
    /**
     * @brief Called when the game starts or when the enemy is spawned.
     * 
     * Overrides the base class BeginPlay method to perform 
     * initialization specific to enemy characters.
     */
    virtual void BeginPlay() override;

public:
    //~ Begin ITargetInterface Implementation
    /**
     * @brief Highlights the enemy to indicate it is a current target.
     * 
     * Implements the TargetInterface method to visually or logically
     * mark the enemy as a selected target.
     * 
     * @see ITargetInterface::HighlightActor()
     */
    virtual void HighlightActor() override;

    /**
     * @brief Removes the highlight from the enemy.
     * 
     * Implements the TargetInterface method to remove the targeting
     * indication from the enemy.
     * 
     * @see ITargetInterface::UnhighlightActor()
     */
    virtual void UnhighlightActor() override;
    //~ End ITargetInterface Implementation
    
private:
    /**
     * @brief Tracks whether the enemy is currently highlighted.
     * 
     * A boolean flag that indicates if the enemy is currently
     * selected or targeted. Can be used for visual feedback
     * or gameplay mechanics.
     * 
     * @note Accessible in Blueprints but remains private in C++
     */
    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    bool bTargetIsHighlighted = false;
};










