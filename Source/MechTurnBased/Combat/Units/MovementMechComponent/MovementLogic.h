// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AGridObject;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../ActionResult/ActionResult.h"
#include "../../Grid/CombatGridManager.h"
#include "../../CombatMode.h"
#include "../CombatUnitSize.h"
#include "../SightDirection.h"
#include "PathNode.h"
#include "MovementLogic.generated.h"


UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UMovementLogic : public UObject
{
	GENERATED_BODY()

public:
	UMovementLogic();

	UFUNCTION(BlueprintCallable)
		void Initialize(UCombatGridManager* CombatGridManager);
	UFUNCTION(BlueprintCallable)
		void SetTargetsInActionResultViaMovementLogicProcessing(UActionResult* ActionResultToProcess, AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartTile, int Distance);
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetPath(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartTile, FMatrixIndex EndTile);
	UFUNCTION(BlueprintCallable)
		TArray<FMatrixIndex> GetAllEndLocations(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, FMatrixIndex StartingTile, int Distance);

private:
	UFUNCTION()
		TArray<FMatrixIndex> GetNeighbouringTiles(FMatrixIndex TileIndex, AGridObject* GridObjectToIgnore);
	UFUNCTION()
		TArray<UPathNode*> GetNeighbouringPathNodes(AGridObject* MovingGridObject, ESightDirection SightDirection, FCombatUnitSize UnitSize, UPathNode* CurrentNode, FMatrixIndex DestinationTile);


public:
	UPROPERTY(BlueprintReadWrite)
		UCombatGridManager* CombatGridManager = nullptr;
};
