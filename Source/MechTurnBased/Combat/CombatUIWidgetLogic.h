// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridObjects/GridObject.h"
#include "Units/ActionResult/ActionResult.h"
#include "Units/ActionResult/ComponentDescription.h"
#include "GridObjects/GridObject.h"
#include "GridObjects/GridObjectComponent.h"
#include "CombatUIWidgetLogic.generated.h"

UCLASS(Blueprintable)
class MECHTURNBASED_API UCombatUIWidgetLogic : public UObject
{
	GENERATED_BODY()

public:
	UCombatUIWidgetLogic();

	//UFUNCTION(BlueprintCallable)
	//	bool TryGetCompRefBasedOnSignal(int Signal, UGridObjectComponent*& OutComponentRef);
	UFUNCTION(BlueprintCallable)
		TArray<UActionResult*> GetActionResultArrayFromGridObject(AGridObject* GridObject);
	UFUNCTION(BlueprintCallable)
		void ExtractActionResultsFromGridObject(AGridObject* GridObject);
	UFUNCTION(BlueprintCallable)
		bool TryGetActionResultBasedOnSignal(int Signal, UActionResult*& OutActionResult);

public:
	UPROPERTY(BlueprintReadWrite)
		AGridObject* GridObjectRef = nullptr;

private:
	UPROPERTY()
		TArray<UActionResult*> SortedActionResultArray;
};
