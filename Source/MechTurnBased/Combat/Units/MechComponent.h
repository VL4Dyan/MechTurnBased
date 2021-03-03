// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "../Grid/MatrixIndex.h"
#include "../GridObjects/GridObjectComponentState.h"
#include "ActionResult/ActionResult.h"
#include "../GridObjects/GridObjectComponent.h"
#include "MechComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract, Blueprintable)
class MECHTURNBASED_API UMechComponent : public UGridObjectComponent
{
	GENERATED_BODY()

public:
	UMechComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual UBoxComponent* GetCollisionRef() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		UActionResult* GetAvailableActions();
	UFUNCTION()
		bool TryGetSubComponents(TArray<UMechComponent*>& OutMechComponents);
	UFUNCTION()
		void UpdateMechComponentState(const FGridObjectComponentState& MechComponentStateReplacement);
	UFUNCTION()
		FGridObjectComponentState GetMechComponentState();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetCollisionBoxRef(UBoxComponent* CollisionBox);

protected:
	UPROPERTY()
		TArray<UMechComponent*> SubComponents;
	UPROPERTY(BlueprintReadWrite)
		int ComponentHullPoints = 5;
	UPROPERTY(BlueprintReadWrite)
		float IncomingHitChanceModifier = 1.0;
	UPROPERTY(BlueprintReadWrite)
		int ExecutionRange = 3;
	UPROPERTY(BlueprintReadWrite)
		float ComponentPower = 2;
	UPROPERTY()
		FGridObjectComponentState MechComponentState = FGridObjectComponentState();
};
