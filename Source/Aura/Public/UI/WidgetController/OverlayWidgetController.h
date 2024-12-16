// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"

#include "OverlayWidgetController.generated.h"

class UAuraAttributeSet;

/**
 * Dynamic delegate for broadcasting health change events.
 * Allows UI elements to respond to changes in character health.
 * @param NewHealth The updated health value after the change.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);

/**
 * Dynamic delegate for broadcasting maximum health change events.
 * Enables UI updates when the character's maximum health is modified.
 * @param NewMaxHealth The updated maximum health value.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);

/**
 * Dynamic delegate for broadcasting mana change events.
 * Allows UI elements to track and respond to mana value changes.
 * @param NewMana The updated mana value after the change.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature, float, NewMana);

/**
 * Dynamic delegate for broadcasting maximum mana change events.
 * Enables UI updates when the character's maximum mana is modified.
 * @param NewMaxMana The updated maximum mana value.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature, float, NewMaxMana);

/**
 * Widget controller responsible for managing and broadcasting UI updates 
 * related to character attributes such as health and mana.
 * 
 * This class serves as a bridge between the game's attribute system and 
 * the user interface, providing real-time updates for key character stats.
 * 
 * @brief Handles overlay widget interactions for character attributes
 * @inherits UAuraWidgetController Base widget controller for Aura game system
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
    GENERATED_BODY()

public:
    /**
     * Broadcasts the initial values of character attributes when the widget is first created.
     * Ensures that the UI reflects the character's starting state immediately.
     * 
     * @overrides Base class method to provide specific attribute initialization
     */
    virtual void BroadcastInitValues() override;

    /**
     * Binds callback functions to attribute change events.
     * Sets up event listeners to track and respond to changes in character attributes.
     * 
     * @overrides Base class method to establish attribute-specific event connections
     */
    virtual void BindCallbacksToDependencies() override;

    /** 
     * Multicast delegate for health change events.
     * Notifies UI elements when the character's health changes.
     * 
     * @category Gas System Attributes
     */
    UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
    FOnHealthChangeSignature OnHealthChange;

    /** 
     * Multicast delegate for maximum health change events.
     * Allows UI to update when the character's maximum health is modified.
     * 
     * @category Gas System Attributes
     */
    UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
    FOnMaxHealthChangeSignature OnMaxHealthChange;

    /** 
     * Multicast delegate for mana change events.
     * Notifies UI elements when the character's mana changes.
     * 
     * @category Gas System Attributes
     */
    UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
    FOnManaChangeSignature OnManaChange;

    /** 
     * Multicast delegate for maximum mana change events.
     * Allows UI to update when the character's maximum mana is modified.
     * 
     * @category Gas System Attributes
     */
    UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
    FOnMaxManaChangeSignature OnMaxManaChange;

protected:
    /**
     * Default constructor for the Overlay Widget Controller.
     * Initializes the widget controller with default settings.
     */
    UOverlayWidgetController();
    
    /**
     * Callback method triggered when the character's health changes.
     * Processes health attribute change data and broadcasts the update.
     * 
     * @param Data Attribute change information containing the new health value
     */
    void HealthChanged(const FOnAttributeChangeData& Data) const;

    /**
     * Callback method triggered when the character's maximum health changes.
     * Processes maximum health attribute change data and broadcasts the update.
     * 
     * @param Data Attribute change information containing the new maximum health value
     */
    void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

    /**
     * Callback method triggered when the character's mana changes.
     * Processes mana attribute change data and broadcasts the update.
     * 
     * @param Data Attribute change information containing the new mana value
     */
    void ManaChanged(const FOnAttributeChangeData& Data) const;

    /**
     * Callback method triggered when the character's maximum mana changes.
     * Processes maximum mana attribute change data and broadcasts the update.
     * 
     * @param Data Attribute change information containing the new maximum mana value
     */
    void MaxManaChanged(const FOnAttributeChangeData& Data) const;

private:
    // Currently no private members or methods
};