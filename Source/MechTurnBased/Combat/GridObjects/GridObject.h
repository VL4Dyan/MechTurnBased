// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UActionResult;

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridObjectType.h"
#include "GridObjectComponent.h"
#include "../Units/GridObjectUpdate.h"
#include "../Units/CombatUnitSize.h"
#include "GridObject.generated.h"

UCLASS(Abstract, Blueprintable)
class MECHTURNBASED_API AGridObject : public ACharacter
{
	GENERATED_BODY()

public:
	AGridObject();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		EGridObjectType GetGridObjectType();
	UFUNCTION()
		virtual TArray<FMatrixIndex> GetOccupiedTiles();
	UFUNCTION(BlueprintCallable)
		virtual TArray<UActionResult*> GetActionResultArray();
	UFUNCTION()
		virtual bool TryToFall();
	UFUNCTION()
		virtual void ApplyEnvironmentalDamage(FMatrixIndex IndexOfAffectedTile, int Dmg);
	UFUNCTION(BlueprintCallable)
		virtual TArray<UGridObjectComponent*> GetGridObjectComponents();
	UFUNCTION(BlueprintCallable)
		virtual bool TryGetGridObjectTileIndex(FMatrixIndex& OutTileIndex);
	UFUNCTION()
		virtual TArray<UGridObjectComponent*> GetGridObjectComponentsOccupyingTileIndex(FMatrixIndex TileIndex);
	UFUNCTION()
		virtual bool TryToCrush(FMatrixIndex CrushedTile, FCombatUnitSize CrushingArea);
	UFUNCTION()
		void AddGridObjectUpdate(FGridObjectUpdate GridObjectUpdate);
	UFUNCTION(BlueprintImplementableEvent)
		void ExecuteNextGridObjectUpdate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool TryGetNextGridObjectUpdate(FGridObjectUpdate& OutGridObjectUpdate);

protected:
	UPROPERTY(BlueprintReadOnly)
		EGridObjectType GridObjectType;
	UPROPERTY(BlueprintReadOnly)
		TArray<FGridObjectUpdate> GridObjectUpdates;
};
