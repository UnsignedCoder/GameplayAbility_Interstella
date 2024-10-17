// Copyright Dark Horse


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValues() {
	Super::BroadcastInitValues();

	
	if ( const UAuraAttributeSet* DerivedAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChange.Broadcast(DerivedAttributeSet->GetHealth());
		OnHealthChange.Broadcast(DerivedAttributeSet->GetMaxHealth());
		
	}
}
