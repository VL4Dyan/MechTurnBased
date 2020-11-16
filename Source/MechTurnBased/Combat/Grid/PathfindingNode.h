// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MatrixIndexes.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PathfindingNode.generated.h"

/**
 *
 */
UCLASS()
class MECHTURNBASED_API UPathfindingNode : public UObject
{
	GENERATED_BODY()

public:
	UPathfindingNode();
	void Initialize(FMatrixIndexes StartLocationIndexes, float EstimatedCost);
	void SetNewCurrentCost(float currentCost);

	UPROPERTY()
		FMatrixIndexes Indexes;
	UPROPERTY()
		float OverallCost;
	UPROPERTY()
		float EstimatedCost;
	UPROPERTY()
		float CurrentCost;
	UPROPERTY()
		UPathfindingNode* Previous;
};

bool operator<(const UPathfindingNode& nodeOne, const UPathfindingNode& nodeTwo);
bool operator==(const UPathfindingNode& nodeOne, const UPathfindingNode& nodeTwo);
