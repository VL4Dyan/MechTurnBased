// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridObjects/GridObject.h"
#include "GridObjects/GridObjectComponent.h"
#include "CombatUIWidgetLogic.generated.h"

UCLASS(Blueprintable)
class MECHTURNBASED_API UCombatUIWidgetLogic : public UObject
{
	GENERATED_BODY()

public:
	UCombatUIWidgetLogic();

	UFUNCTION(BlueprintCallable)
		bool TryGetCompRefBasedOnSignal(int Signal, UGridObjectComponent*& OutComponentRef);

public:
	UPROPERTY(BlueprintReadWrite)
		AGridObject* GridObjectRef = nullptr;
};
