// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GridObjects/GridObjectComponentState.h"
#include "../../GridObjects/GridObjectComponent.h"
#include "GridObjectComponentStateUpdate.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UGridObjectComponentStateUpdate : public UObject
{
	GENERATED_BODY()

public:
	UGridObjectComponentStateUpdate();

	UFUNCTION()
		void Initialize(UGridObjectComponent* GridObjCompRef);

public:
	UPROPERTY(BlueprintReadOnly)
		UGridObjectComponent* GridObjectComponent;
	UPROPERTY(BlueprintReadOnly)
		FGridObjectComponentState GridObjectComponentStateReplacement;
};
