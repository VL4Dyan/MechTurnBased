// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Grid/CombatGridManager.h"
#include "Grid/MatrixIndexes.h"
#include "Grid/TileChecker.h"
#include "Grid/TileData.h"
#include "Temp/TempPawn.h"
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
		void ScanGrid(UCombatGridManager* combatGridManager, ATileChecker* tileCheckerBody);
};
