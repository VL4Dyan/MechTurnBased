// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingResult.h"
#include "ComponentTargetingResult.h"
#include "../../../GridObjects/GridObject.h"
#include "GridObjectTargetingResult.generated.h"

UCLASS(BlueprintType)
class MECHTURNBASED_API UGridObjectTargetingResult : public UTargetingResult
{
	GENERATED_BODY()

public:
	UGridObjectTargetingResult();

	UFUNCTION()
		void Initialize(AGridObject* GridObjectToSet);
	UFUNCTION()
		UComponentTargetingResult* AddComponentTarget(UGridObjectComponent* GridObjectComponentTarget);

public:
	UPROPERTY()
		AGridObject* GridObject = nullptr;
	UPROPERTY()
		TArray<UComponentTargetingResult*> ComponentTargetingResults;
};
