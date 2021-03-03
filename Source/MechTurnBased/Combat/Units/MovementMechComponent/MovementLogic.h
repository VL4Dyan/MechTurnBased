// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Grid/CombatGridManager.h"
#include "../../CombatMode.h"
#include "PathNode.h"
#include "MovementLogic.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UMovementLogic : public UActorComponent
{
	GENERATED_BODY()

public:
	UMovementLogic();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void GetOnFootPassableTiles();

private:
	UFUNCTION()
		TArray<FMatrixIndex> GetAllEndLocations(FMatrixIndex StartingTile, int Distance);
	UFUNCTION()
		TArray<FMatrixIndex> GetNeighbouringTiles(FMatrixIndex TileIndex);
	UFUNCTION()
		TArray<UPathNode*> GetNeighbouringPathNodes(UPathNode* CurrentNode, FMatrixIndex DestinationTile);
	UFUNCTION()
		TArray<FMatrixIndex> GetPath(FMatrixIndex StartTile, FMatrixIndex EndTile);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		UCombatGridManager* CombatGridManagerRef = nullptr;
};
