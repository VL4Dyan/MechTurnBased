// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GridObjects/GridObjectComponentState.h"
#include "../../../GridObjects/GridObjectComponent.h"
#include "GridObjectComponentStateUpdate.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UGridObjectComponentStateUpdate : public UObject
{
	GENERATED_BODY()

public:
	UGridObjectComponentStateUpdate();

	UFUNCTION()
		void Initialize(UGridObjectComponent* GridObjCompToSet);
	UFUNCTION(BlueprintCallable)
		void SetGridObjectComponentStateReplacement(FGridObjectComponentState GridObjectComponentStateReplacementToSet);
	UFUNCTION(BlueprintCallable)
		void GetCurrentComponentState(FGridObjectComponentState& OutGridObjCompState);
	UFUNCTION()
		void ExecuteUpdate();

private:
	UPROPERTY()
		bool bCorrectParameters = false;
	UPROPERTY()
		UGridObjectComponent* GridObjectComponent;
	UPROPERTY()
		FGridObjectComponentState GridObjectComponentStateReplacement;
	UPROPERTY()
		FGridObjectComponentState OldGridObjectComponentState;
};
