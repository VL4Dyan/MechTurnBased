// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Grid/CombatGridManager.h"
#include "../../Grid/MatrixIndex.h"
#include "../../CombatMode.h"
#include "../GridObject.h"
#include "BuildingComponent.h"
#include "Building.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable)
class MECHTURNBASED_API ABuilding : public AGridObject
{
	GENERATED_BODY()

public:
	ABuilding();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Activate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetComponentsRelations();

protected:
	TArray<UBuildingComponent*> Components;

};
