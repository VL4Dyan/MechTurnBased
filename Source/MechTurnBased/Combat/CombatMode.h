// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Grid/CombatGridManager.h"
#include "Grid/MatrixIndex.h"
#include "Grid/TileChecker.h"
#include "Grid/TileData.h"
#include "Units/CombatUnit.h"
#include "Teams.h"
#include "CombatMode.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class MECHTURNBASED_API ACombatMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
		void ScanGrid(ATileChecker* TileCheckerBody);
	UFUNCTION(BlueprintCallable)
		bool PlaceCombatUnitOnGrid(ACombatUnit* CombatUnit, ASpawnPoint* SpawnPoint);

public:
	UFUNCTION(BlueprintCallable)
		UCombatGridManager* GetCombatGridManagerRef();

protected:
	UPROPERTY(BlueprintReadOnly)
		TArray<ASpawnPoint*> SpawnPoints;
	UPROPERTY(BlueprintReadOnly)
		UCombatGridManager* CombatGridManager;
};
