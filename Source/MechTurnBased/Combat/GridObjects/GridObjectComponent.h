// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "GridObjectComponentState.h"
#include "GridObjectComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Abstract)
class MECHTURNBASED_API UGridObjectComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UGridObjectComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		virtual void UpdateComponentState(FGridObjectComponentState ComponentStateReplacement);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		UBoxComponent* CollisionBoxRef;
	UPROPERTY()
		FGridObjectComponentState ComponentState;


};
