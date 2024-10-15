// Copyright Dark Horse


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWIdgetController( const FWidgetControllerParams& WidgetControllerParams ) {
	if(!OverlayWidgetController) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

		OverlayWidgetController->InitWidgetController(WidgetControllerParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay( APlayerController* Controller, APlayerState* PlayerState, UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AbilitySet ) {
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams WidgetControllerParams(Controller, PlayerState, AbilitySystemComponent, AbilitySet);
	UOverlayWidgetController* WidgetController = GetOverlayWIdgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	OverlayWidget->AddToViewport();
}
