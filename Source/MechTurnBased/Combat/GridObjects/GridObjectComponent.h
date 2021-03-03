// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "../Grid/MatrixIndex.h"
//#include "GridObject.h"
#include "GridObjectComponentState.h"
#include "GridObjectComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract)
class MECHTURNBASED_API UGridObjectComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UGridObjectComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		virtual FGridObjectComponentState GetComponentState();
	UFUNCTION()
		virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement);
	UFUNCTION()
		virtual UBoxComponent* GetCollisionRef();
	UFUNCTION(BlueprintCallable)
		virtual void SetCollisionRef(UBoxComponent* CollisionBoxRefToSet);
	UFUNCTION(BlueprintCallable)
		virtual TArray<FMatrixIndex> GetTileTargets(bool& OutIsDynamicTargeting);
	UFUNCTION(BlueprintCallable)
		virtual bool TryGetTargetableGridObjectComponents(FMatrixIndex TargetTile, TArray<UGridObjectComponent*>& OutTargetableGridObjectComponents);
	UFUNCTION(BlueprintCallable)
		virtual void ExecuteFunction(FMatrixIndex TargetTile, UGridObjectComponent* TargetComponent);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		UBoxComponent* CollisionBoxRef;
	UPROPERTY()
		FGridObjectComponentState ComponentState;


};
