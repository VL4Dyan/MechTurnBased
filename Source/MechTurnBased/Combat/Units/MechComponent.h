// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "CombatUnit.h"
#include "../Grid/MatrixIndex.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "../GridObjects/GridObjectComponent.h"
#include "ActionResult/ActionResult.h"
#include "MechComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable)
class MECHTURNBASED_API UMechComponent : public UGridObjectComponent
{
	GENERATED_BODY()

public:
	UMechComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual UBoxComponent* GetCollisionRef() override;

	UFUNCTION()
		bool TryGetSubComponents(TArray<UMechComponent*>& OutMechComponents);
	UFUNCTION()
		void UpdateMechComponentState(const FGridObjectComponentState& MechComponentStateReplacement);
	UFUNCTION()
		FGridObjectComponentState GetMechComponentState();
	UFUNCTION()
		void UpdateComponentPosition(FMatrixIndex TileIndexReplacement);
	UFUNCTION(BlueprintImplementableEvent)
		UActionResult* GetActionResult();

	virtual FMatrixIndex GetTileToHighlight() override; //temp function

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetCollisionBoxRef(UBoxComponent* CollisionBox);

public:
	UPROPERTY(BlueprintReadWrite)
		ACombatUnit* Owner = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
		FMatrixIndex ComponentFunctionalityPosition = FMatrixIndex(0, 0, 0);
	UPROPERTY()
		TArray<UMechComponent*> SubComponents;
	UPROPERTY()
		FGridObjectComponentState MechComponentState = FGridObjectComponentState();
};
