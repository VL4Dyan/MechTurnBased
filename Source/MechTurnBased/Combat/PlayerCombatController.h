// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Grid/CombatGridManager.h"
#include "Grid/MatrixIndexes.h"
#include "Grid/TileChecker.h"
#include "Grid/TileData.h"
#include "Components/BoxComponent.h"
#include "PlayerCombatController.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class MECHTURNBASED_API APlayerCombatController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCombatController();
};
