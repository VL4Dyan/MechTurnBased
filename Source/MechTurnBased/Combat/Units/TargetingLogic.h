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
#include "../GridObjects/GridObject.h"
#include "ActionResult/ActionResult.h"
#include "ActionResult/TargetingResult/TileTargetingResult.h"
#include "ActionResult/TargetingResult/ComponentTargetingResult.h"
#include "TargetingLogic.generated.h"


UCLASS(BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UTargetingLogic : public UObject
{
	GENERATED_BODY()

public:
	UTargetingLogic();

	UFUNCTION(BlueprintCallable)
		void Initialize(UCombatGridManager* CombatGridManager);
	//UFUNCTION(BlueprintCallable)
	//	void SetTargetsInActionResultViaLineTrace(UActionResult* ActionResultToProcess, FMatrixIndex PositionToLookFrom, int Range);
	UFUNCTION(BlueprintCallable)
		TArray<AGridObject*> GetGridObjectsInRange(FMatrixIndex PositionToLookFrom, int Range, AGridObject* GridObjectToIgnore);
	UFUNCTION(BlueprintCallable)
		TArray<UGridObjectComponent*> GetTargetableGridObjectComponents(FMatrixIndex PositionToLookFrom, AGridObject* TargetGridObject, int Range);

private:
	UFUNCTION()
		TArray <FVector> GetExecutionerSidePoints(FVector ExecutionerCentre, FVector TargetCentre);
	UFUNCTION()
		bool AnyObstaclesOnLine(FVector StartingPoint, FVector EndingPoint, UPrimitiveComponent* ComponentToTrace, AGridObject* ActorToIgnore);
	UFUNCTION()
		float GetDistanceBetweenPoints(FVector PointOne, FVector PointTwo);

public:
	UPROPERTY(BlueprintReadWrite)
		float TraceSphereRadius = 5.0;
	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;

private:
	UPROPERTY()
		UCombatGridManager* CombatGridManager;
	UPROPERTY()
		float TileWidthLength;
	UPROPERTY()
		float TileHeight;

};
