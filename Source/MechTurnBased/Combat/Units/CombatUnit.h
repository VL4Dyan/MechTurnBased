// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Grid/MatrixIndex.h"
#include "../Teams.h"
#include "SightDirection.h"
#include "../CombatMode.h"
#include "MechComponent.h"
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
	UFUNCTION()
		void AddMechComponent(UMechComponent* MechComponent);
	UFUNCTION()
		TArray<UMechComponent*> GetMechComponentsHavingCollisionBoxes();
	UFUNCTION()
		TArray<UMechComponent*> GetMechComponentsRepresentingFunctionality();
	UFUNCTION()
		UMechComponent* GetMechMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite)
		FMatrixIndex UnitTileIndex = FMatrixIndex(0, 0, 0);
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MovingSpeedScale = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MovingDistance = 2;
	UPROPERTY(BlueprintReadWrite)
		ETeams UnitOwner = ETeams::Team_Player;
	UPROPERTY(BlueprintReadWrite)
		ESightDirection UnitViewDirection = ESightDirection::Direction_North;

private:
	UPROPERTY()
		TArray<UMechComponent*> UnitMechComponents;
	UPROPERTY()
		UMechComponent* MovementComponent = nullptr;
};
