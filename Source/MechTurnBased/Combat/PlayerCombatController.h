// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/BoxComponent.h"
#include "Grid/CombatGridManager.h"
#include "Grid/MatrixIndex.h"
#include "Grid/TileData.h"
#include "Teams.h"
#include "Grid/CombatGridManager.h"
#include "Units/ActionResult/TileTargetingResult.h"
#include "Units/ActionResult/ComponentTargetingResult.h"
#include "Units/ActionResult/TileDataUpdate.h"
#include "Units/ActionResult/GridObjectComponentStateUpdate.h"
#include "PlayerCombatController.generated.h"

//The whole control system will be reworked.
UCLASS(Blueprintable)
class MECHTURNBASED_API APlayerCombatController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCombatController();

protected:
	UFUNCTION(BlueprintCallable)
		void SetSelectedTile(FMatrixIndex Index);
	UFUNCTION(BlueprintCallable)
		bool TryGetTempSelectedTile(FMatrixIndex Index, FTileData& TileOut);
	UFUNCTION(BlueprintCallable)
		TArray<UTileTargetingResult*> GetActionResultBasedOnUISignal(int Signal);
protected:
	UPROPERTY(BlueprintReadOnly)
		ETeams Team = ETeams::Team_Player;
	UPROPERTY(BlueprintReadWrite)
		UCombatGridManager* CombatGridManagerRef = nullptr;
	UPROPERTY(BlueprintReadOnly)
		FTileData SelectedTile;
	UPROPERTY(BlueprintReadOnly)
		FMatrixIndex SelectedTileIndex;
	UPROPERTY(BlueprintReadOnly)
		bool bIsTileSelected = false;
	UPROPERTY(BlueprintReadOnly)
		bool bIsControllableUnitSelected = false;
	UPROPERTY(BlueprintReadOnly)
		bool bActionState = false;
	UPROPERTY(BlueprintReadOnly)
		ACombatUnit* SelectedUnit = nullptr;
};
