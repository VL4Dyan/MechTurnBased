// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Grid/MatrixIndex.h"
#include "CoreMinimal.h"
#include "PathNode.generated.h"

UCLASS()
class MECHTURNBASED_API UPathNode : public UObject
{
	GENERATED_BODY()

public:
	UPathNode();
	UFUNCTION()
		void Initialize(FMatrixIndex TileIndexToSet, float EstimatedCostToSet);
	UFUNCTION()
		void SetCurrentCost(float CurrentCostToSet);

public:
	UPROPERTY()
		FMatrixIndex TileIndex;
	UPROPERTY()
		float OverallCost;
	UPROPERTY()
		float EstimatedCost;
	UPROPERTY()
		float CurrentCost;
	UPROPERTY()
		UPathNode* PreviousNode;
};

bool operator<(const UPathNode& NodeOne, const UPathNode& NodeTwo);
