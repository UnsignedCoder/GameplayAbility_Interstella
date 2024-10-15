// Copyright Dark Horse

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySet.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams {
	GENERATED_BODY()

	FWidgetControllerParams() {} 

	FWidgetControllerParams(APlayerController* PController, APlayerState* AState, UAbilitySystemComponent* ASystem, UAttributeSet* ASet) :
		PLayerController(PController), PlayerState(AState), AbilitySystemComponent(ASystem), AttributeSet(ASet) {}
	
	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<APlayerController> PLayerController = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitWidgetController(const FWidgetControllerParams& WControllerParams);
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<APlayerController> PLayerController;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "AuraWidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
