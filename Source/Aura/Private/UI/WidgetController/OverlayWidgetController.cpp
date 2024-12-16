// Copyright Dark Horse

#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

/**
 * Default constructor for the Overlay Widget Controller.
 * Initializes the widget controller with default settings and prepares it for use.
 * Currently does not perform any specific initialization beyond the base class constructor.
 */
UOverlayWidgetController::UOverlayWidgetController() {}

/**
 * Broadcasts the initial values of health and mana to the respective delegates.
 * This function is called to initialize the widget controller with the current attribute values.
 * It ensures that the UI elements are updated with the initial health and mana values
 * when the widget controller is first created or reset.
 * 
 * The method performs the following key steps:
 * 1. Calls the base class implementation of BroadcastInitValues()
 * 2. Casts the AttributeSet to UAuraAttributeSet to access attribute values
 * 3. Broadcasts initial health and max health values
 * 4. Broadcasts initial mana and max mana values
 * 
 * @note This method assumes that the AttributeSet is of type UAuraAttributeSet
 * @throws No exceptions are thrown, but an invalid cast will result in no broadcasts
 */
void UOverlayWidgetController::BroadcastInitValues() {
    Super::BroadcastInitValues();

    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);

    OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());

    OnManaChange.Broadcast(AuraAttributeSet->GetMana());
    OnMaxManaChange.Broadcast(AuraAttributeSet->GetMaxMana());
}

/**
 * Binds the attribute change callbacks to the corresponding delegates.
 * This function sets up the necessary bindings between the attribute changes
 * in the Ability System Component and the delegate functions that handle these changes.
 * It ensures that the UI elements are updated in real-time when the health or mana attributes change.
 * 
 * The method performs the following key steps:
 * 1. Calls the base class implementation of BindCallbacksToDependencies()
 * 2. Casts the AttributeSet to UAuraAttributeSet to access attribute change delegates
 * 3. Binds callback methods to health and max health attribute change events
 * 4. Binds callback methods to mana and max mana attribute change events
 * 
 * @note This method assumes that the AttributeSet is of type UAuraAttributeSet
 * @throws No exceptions are thrown, but an invalid cast will result in no bindings
 */
void UOverlayWidgetController::BindCallbacksToDependencies() {
    Super::BindCallbacksToDependencies();
    
    const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

/**
 * Callback method triggered when the character's health changes.
 * Broadcasts the new health value to registered UI delegates.
 * 
 * @param Data A struct containing information about the attribute change, 
 *             including the new value of the health attribute
 * @note This is a const method, meaning it does not modify the object's state
 */
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const {
    OnHealthChange.Broadcast(Data.NewValue);
}

/**
 * Callback method triggered when the character's maximum health changes.
 * Broadcasts the new maximum health value to registered UI delegates.
 * 
 * @param Data A struct containing information about the attribute change, 
 *             including the new value of the maximum health attribute
 * @note This is a const method, meaning it does not modify the object's state
 */
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const {
    OnMaxHealthChange.Broadcast(Data.NewValue);
}

/**
 * Callback method triggered when the character's mana changes.
 * Broadcasts the new mana value to registered UI delegates.
 * 
 * @param Data A struct containing information about the attribute change, 
 *             including the new value of the mana attribute
 * @note This is a const method, meaning it does not modify the object's state
 */
void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const {
    OnManaChange.Broadcast(Data.NewValue);
}

/**
 * Callback method triggered when the character's maximum mana changes.
 * Broadcasts the new maximum mana value to registered UI delegates.
 * 
 * @param Data A struct containing information about the attribute change, 
 *             including the new value of the maximum mana attribute
 * @note This is a const method, meaning it does not modify the object's state
 */
void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const {
    OnMaxManaChange.Broadcast(Data.NewValue);
}