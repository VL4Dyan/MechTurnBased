// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "../../CombatMode.h"
#include "../../Grid/CombatGridManager.h"
#include "../GridObject.h"
#include "../GridObjectComponent.h"
#include "BuildingComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MECHTURNBASED_API UBuildingComponent : public UGridObjectComponent
{
	GENERATED_BODY()

public:
	UBuildingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		bool IsComponentABase();
	UFUNCTION()
		void RemoveConnectionToComponent(UBuildingComponent* ComponentRefToRemove);
	UFUNCTION()
		bool TryToDestroyYourself();
	UFUNCTION()
		void NotifyNextComponentsOfAcquirementOfABaseComponent(UBuildingComponent* BaseComponent);
	UFUNCTION()
		void ActivateComponent();
	UFUNCTION()
		void DeactivateComponent();

	virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		FMatrixIndex OccupiedTileIndex;
	UPROPERTY()
		TArray<UBuildingComponent*> NextComponents; //Components to notify in case this one gets destroyed/this one gets a connection to a base
	UPROPERTY()
		TArray<UBuildingComponent*> PreviousComponents; //Components that lead to base components

private:
	UCombatGridManager* CombatGridManagerRef = nullptr;

protected:
	UPROPERTY(BlueprintReadWrite)
		bool bIsAPlatform = false;
	UPROPERTY(BlueprintReadWrite)
		bool bIsABase = false;
};
