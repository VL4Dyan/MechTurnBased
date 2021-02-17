// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "../Grid/MatrixIndex.h"
#include "../Grid/CombatGridManager.h"
#include "../CombatMode.h"
#include "MechComponent.h"
#include "../GridObjects/GridObjectType.h"
#include "ActionResult/ActionResult.h"
#include "TargetingLogic.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UTargetingLogic : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetingLogic();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		UActionResult* GetTargetsViaLineTrace(FMatrixIndex PositionToLookFrom, int Range);
	//UFUNCTION(BlueprintCallable)
	//	TArray<UTileTargetingResult*> GetTargetsViaArcTrace(FMatrixIndex PositionToLookFrom, int Range);

private:
		TArray<FMatrixIndex> GetTargetableIndexesInRange(FMatrixIndex PositionToLookFrom, int Range, bool bIgnoreTilesWithoutUnits);
		TArray<UMechComponent*> GetTargetableMechComponents(FMatrixIndex PositionToLookFrom, FMatrixIndex TargetPosition);
		TArray <FVector> GetExecutionerSidePoints(FVector ExecutionerCentre, FVector TargetCentre);
		bool AnyObstaclesOnLine(FVector StartingPoint, FVector EndingPoint, UPrimitiveComponent* PrimitiveComponent);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
		float TraceSphereRadius = 10.0;
	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_GameTraceChannel1;

private:
	UPROPERTY()
		UCombatGridManager* CombatGridManagerRef = nullptr;
	UPROPERTY()
		float TileWidthLength = 0.0;
	UPROPERTY()
		float TileHeight = 0.0;

};
