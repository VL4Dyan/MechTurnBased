// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../GridObjects/GridObjectComponent.h"
#include "ComponentDescription.generated.h"

USTRUCT(BlueprintType)
struct FComponentDescription
{
	GENERATED_BODY()

public:
	FComponentDescription();

	UPROPERTY(BlueprintReadOnly)
		EGridObjectCompType ComponentType = EGridObjectCompType::CompType_Other;
};
