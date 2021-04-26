// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Grid/CombatGridManager.h"
#include "../../Grid/TileData.h"
#include "../../Grid/MatrixIndex.h"
#include "../ActionResult/TargetingResult/TargetingResult.h"
#include "../ActionResult/TargetingResult/TileTargetingResult.h"
#include "../MechComponent.h"
#include "../SightDirection.h"
#include "../CombatUnitSize.h"
#include "MovementLogic.h"
#include "MovementMechComponent.generated.h"

UCLASS()
class MECHTURNBASED_API UMovementMechComponent : public UMechComponent
{
	GENERATED_BODY()

public:
	UMovementMechComponent();

	//To do: deconstruct to smaller methods; this all is kinda messy

	virtual void ExecuteAction(UTargetingResult* TargetingResult) override;

	UFUNCTION()
		bool TryAnchorUnitToTile(FMatrixIndex TileIndex);
	UFUNCTION()
		bool TryToFall();
	UFUNCTION()
		void RespondToPush(ESightDirection PushDirection, int Power);
	UFUNCTION()
		FCombatUnitSize GetRelativeUnitSize();

private:
	UFUNCTION()
		bool CheckIfUnitShouldFall(FMatrixIndex CurrentTileIndex, FCombatUnitSize RelativeUnitSize, TArray<FMatrixIndex>& OutMapPlatformsTileIndexes, bool& OutPlacementOutOfBounds);
	UFUNCTION()
		bool TryGetShiftedUnitTileIndex(FMatrixIndex CurrentUnitTileIndex, FCombatUnitSize RelativeUnitSize, int XAxisWeight, int YAxisWeight, FMatrixIndex& OutNewUnitTileIndex);

public:
	UPROPERTY(BlueprintReadWrite)
		FMatrixIndex UnitTileIndex = FMatrixIndex(0, 0, 0);
	UPROPERTY()
		FCombatUnitSize UnitSize = FCombatUnitSize(1, 1, 2);
	UPROPERTY(BlueprintReadWrite)
		ESightDirection UnitViewDirection = ESightDirection::Direction_North;
	
protected:
	UPROPERTY(BlueprintReadWrite)
		UMovementLogic* MovementLogicRef;
	UPROPERTY(BlueprintReadWrite)
		UCombatGridManager* CombatGridManagerRef;
};
