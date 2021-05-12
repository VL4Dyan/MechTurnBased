// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UActionResult;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "CombatUnit.h"
#include "GridObjectUpdate.h"
#include "../Grid/MatrixIndex.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "../GridObjects/GridObjectComponent.h"
#include "MechComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable)
class MECHTURNBASED_API UMechComponent : public UGridObjectComponent
{
	GENERATED_BODY()

public:
	UMechComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FMatrixIndex GetTileToHighlight() override; //temp function
	virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement) override;

	UFUNCTION()
		bool TryGetSubComponents(TArray<UMechComponent*>& OutMechComponents);
	UFUNCTION()
		FGridObjectComponentState GetMechComponentState();
	UFUNCTION()
		void UpdateComponentPosition(FMatrixIndex TileIndexReplacement);
	UFUNCTION()
		virtual void ExecuteAction(UTargetingResult* TargetingResult);
	UFUNCTION(BlueprintImplementableEvent)
		UActionResult* GetActionResult();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetCollisionBoxRef(UBoxComponent* CollisionBox);

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bIsFunctional = true;
	UPROPERTY(BlueprintReadOnly)
		FMatrixIndex ComponentFunctionalityPosition = FMatrixIndex(0, 0, 0);
	UPROPERTY()
		TArray<UMechComponent*> SubComponents;
	UPROPERTY()
		FGridObjectComponentState MechComponentState = FGridObjectComponentState();
};
