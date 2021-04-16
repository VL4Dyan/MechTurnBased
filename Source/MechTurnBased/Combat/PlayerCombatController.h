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
#include "Units/ActionResult/TargetingResult/ComponentTargetingResult.h"
#include "Units/ActionResult/DataUpdate/TileDataUpdate.h"
#include "Units/ActionResult/DataUpdate/GridObjectComponentStateUpdate.h"
#include "PlayerCombatController.generated.h"

UENUM(BlueprintType)
enum class EControllerState : uint8
{
	State_Selection UMETA(DisplayName="Selection"),
	State_Choice UMETA(DisplayName="Choice"),
	State_Execution UMETA(DisplayName="Execution")
};

UCLASS(Blueprintable)
class MECHTURNBASED_API APlayerCombatController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCombatController();
};
