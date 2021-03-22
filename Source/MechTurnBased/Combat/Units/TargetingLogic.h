// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "../Grid/MatrixIndex.h"
#include "../Grid/CombatGridManager.h"
#include "../CombatMode.h"
#include "../GridObjects/GridObjectComponent.h"
#include "../GridObjects/GridObjectType.h"
#include "ActionResult/ActionResult.h"
#include "ActionResult/TileTargetingResult.h"
#include "ActionResult/ComponentTargetingResult.h"
#include "TargetingLogic.generated.h"


UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UTargetingLogic : public UObject
{
	GENERATED_BODY()

public:
	UTargetingLogic();

	UFUNCTION(BlueprintCallable)
		UActionResult* GetTargetsViaLineTrace(FMatrixIndex PositionToLookFrom, int Range);

private:
	UFUNCTION()
		TArray<FMatrixIndex> GetTargetableIndexesInRange(FMatrixIndex PositionToLookFrom, int Range, bool bIgnoreTilesWithoutUnits);
	UFUNCTION()
		TArray<UGridObjectComponent*> GetTargetableGridObjectComponents(FMatrixIndex PositionToLookFrom, FMatrixIndex TargetTileIndex);
	UFUNCTION()
		TArray <FVector> GetExecutionerSidePoints(FVector ExecutionerCentre, FVector TargetCentre);
	UFUNCTION()
		bool AnyObstaclesOnLine(FVector StartingPoint, FVector EndingPoint, UPrimitiveComponent* ComponentToTrace, AGridObject* ActorToIgnore);

public:
	UPROPERTY(BlueprintReadWrite)
		float TraceSphereRadius = 5.0;
	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;
	UPROPERTY(BlueprintReadWrite)
		UCombatGridManager* CombatGridManagerRef = nullptr;

private:
	UPROPERTY()
		float TileWidthLength = 100.0;
	UPROPERTY()
		float TileHeight = 100.0;

};
