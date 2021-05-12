// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GridObjects/GridObjectComponent.h"
#include "../DataUpdate/GridObjectComponentStateUpdate.h"
#include "../DataUpdate/TileDataUpdate.h"
#include "TargetingResult.h"
#include "ComponentTargetingResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UComponentTargetingResult : public UTargetingResult
{
	GENERATED_BODY()

public:
	UComponentTargetingResult();

	UFUNCTION()
		void Initialize(UGridObjectComponent* GridObjectComponentToSet);
	UFUNCTION(BlueprintCallable)
		UGridObjectComponentStateUpdate* AddGridObjectComponentStateUpdate(UGridObjectComponent* GridObjCompRef);

private:
	UPROPERTY()
		UGridObjectComponent* GridObjectComponent;
};
