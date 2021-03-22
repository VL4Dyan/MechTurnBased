// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetingResult.generated.h"


UCLASS(Abstract, Blueprintable)
class MECHTURNBASED_API UTargetingResult : public UObject
{
	GENERATED_BODY()

public:

	UTargetingResult();

	UFUNCTION(BlueprintCallable)
		void ExecuteContainedUpdates();
};
