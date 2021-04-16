// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UMechComponent;
class UTargetingResult;
class UMovementMechComponent;

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Grid/MatrixIndex.h"
#include "../Teams.h"
#include "CombatUnitSize.h"
#include "../CombatMode.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "../GridObjects/GridObject.h"
#include "CombatUnit.generated.h"

UCLASS()
class MECHTURNBASED_API ACombatUnit : public AGridObject
{
	GENERATED_BODY()

public:
	ACombatUnit();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool TryToFall() override;
	virtual TArray<UGridObjectComponent*> GetGridObjectComponentsOccupyingTileIndex(FMatrixIndex TileIndex) override;
	virtual TArray<UActionResult*> GetActionResultArray() override;
	virtual TArray<UGridObjectComponent*> GetGridObjectComponents() override;

	UFUNCTION(BlueprintImplementableEvent)
		void MoveAlongPath(const TArray<FVector>& Path);
	UFUNCTION(BlueprintImplementableEvent)
		void PerformAnimation(UMechComponent* ComponentExecutor, UTargetingResult* ResultsToVisualize);
	UFUNCTION()
		bool TryPlaceCombatUnitOnTile(FMatrixIndex TileIndex);
	UFUNCTION()
		TArray<UMechComponent*> GetMechComponentsHavingCollisionBoxes();
	UFUNCTION()
		TArray<UMechComponent*> GetMechComponentsRepresentingFunctionality();
	UFUNCTION(BlueprintCallable)
		UMechComponent* GetMechMovementComponent();
	UFUNCTION()
		void DestroyCombatUnit();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void AddMechComponent(UMechComponent* MechComponent);

public:
	UPROPERTY(BlueprintReadWrite)
		ETeams UnitOwner = ETeams::Team_Player;
	UPROPERTY(BlueprintReadWrite)
		TArray<UMechComponent*> MechComponents;

private:
	UPROPERTY()
		UMovementMechComponent* MovementMechComponent = nullptr;
};
