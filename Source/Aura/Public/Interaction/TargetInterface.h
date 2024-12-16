// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetInterface.generated.h"

/**
 * Minimal UINTERFACE implementation for the TargetInterface.
 * This class is a required wrapper for Unreal Engine's reflection and garbage collection systems.
 * It does not need to be modified or directly used by developers.
 */
UINTERFACE(MinimalAPI)
class UTargetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * @brief Defines an interface for interactable or highlightable actors in the game.
 * 
 * The ITargetInterface provides a standard set of methods for managing actor visibility 
 * and highlight states, allowing consistent targeting mechanics across different actor types.
 * 
 * Any class implementing this interface must provide concrete implementations for:
 * - HighlightActor(): Visually indicate that an actor is currently selected or targeted
 * - UnhighlightActor(): Remove the targeting visual indication
 * 
 * @note This interface is part of the Aura project's targeting system
 */
class AURA_API ITargetInterface
{
    GENERATED_BODY()

public:
    /**
     * @brief Visually highlights the actor to indicate it is currently selected or targeted.
     * 
     * This method should apply visual feedback such as:
     * - Outlining the actor
     * - Changing material properties
     * - Adding a selection indicator
     * 
     * @note This is a pure virtual function that must be implemented by derived classes
     */
    virtual void HighlightActor() = 0;

    /**
     * @brief Removes the highlight from the actor, returning it to its default visual state.
     * 
     * This method should reverse the visual changes made by HighlightActor(), such as:
     * - Removing any outline
     * - Restoring original material properties
     * - Hiding selection indicators
     * 
     * @note This is a pure virtual function that must be implemented by derived classes
     */
    virtual void UnhighlightActor() = 0;
};