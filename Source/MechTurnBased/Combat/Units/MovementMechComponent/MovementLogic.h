// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../ActionResult/ActionResult.h"
#include "../../Grid/CombatGridManager.h"
#include "../../CombatMode.h"
#include "PathNode.h"
#include "MovementLogic.generated.h"


UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UMovementLogic : public UObject
{
	GENERATED_BODY()

public:
	UMovementLogic();

	UFUNCTION(BlueprintCallable)
		UActionResult* GetActionResult(FMatrixIndex StartTile, int Distance);
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetPath(FMatrixIndex StartTile, FMatrixIndex EndTile);
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetAllEndLocations(FMatrixIndex StartingTile, int Distance);

private:
	UFUNCTION()
		TArray<FMatrixIndex> GetNeighbouringTiles(FMatrixIndex TileIndex);
	UFUNCTION()
		TArray<UPathNode*> GetNeighbouringPathNodes(UPathNode* CurrentNode, FMatrixIndex DestinationTile);


public:
	UPROPERTY(BlueprintReadWrite)
		UCombatGridManager* CombatGridManagerRef = nullptr;
};
