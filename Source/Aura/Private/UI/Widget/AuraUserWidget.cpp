// Copyright Dark Horse


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController( UObject* Controller ) {
	WidgetController = Controller;
	OnWidgetContrillerSet();
}