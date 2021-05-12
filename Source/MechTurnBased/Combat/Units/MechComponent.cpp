// Fill out your copyright notice in the Description page of Project Settings.

#include "MechComponent.h"
#include "ActionResult/DataUpdate/GridObjectComponentStateUpdate.h"
#include "ActionResult/DataUpdate/TileDataUpdate.h"
#include "ActionResult/TargetingResult/TargetingResult.h"
#include "GridObjectUpdate.h"

UMechComponent::UMechComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMechComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}

void UMechComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMechComponent::UpdateComponentState(FGridObjectComponentState ComponentStateReplacement)
{
	ComponentState = ComponentStateReplacement;

	if (ComponentState.HullPoints <= 0)
	{
		bIsFunctional = false;
	}
}

void UMechComponent::SetCollisionBoxRef(UBoxComponent* CollisionBox)
{
	CollisionBoxRef = CollisionBox;
}

bool UMechComponent::TryGetSubComponents(TArray<UMechComponent*>& OutMechComponents)
{
	OutMechComponents = SubComponents;
	return false;
}

FGridObjectComponentState UMechComponent::GetMechComponentState()
{
	return MechComponentState;
}

void UMechComponent::UpdateComponentPosition(FMatrixIndex TileIndexReplacement)
{
	ComponentFunctionalityPosition = TileIndexReplacement;
}

FMatrixIndex UMechComponent::GetTileToHighlight()
{
	return ComponentFunctionalityPosition;
}

void UMechComponent::ExecuteAction(UTargetingResult* TargetingResult)
{
	for (UGridObjectComponentStateUpdate* GridObjCompStateUpd : TargetingResult->GridObjectComponentUpdates)
	{
		FGridObjectUpdate GridObjectUpdate = FGridObjectUpdate();
		GridObjectUpdate.VisualUpdateType = EGridObjectUpdateType::GOUT_Attack;
		GridObjectUpdate.WorldLocationTargets.Add(GridObjCompStateUpd->GridObjectComponent->GetCollisionRef()->GetComponentLocation());
		GridObjectUpdate.AffectedGridObjects.Add(GridObjCompStateUpd->GridObjectComponent->GetGridObjectComponentOwner());

		GridObjectComponentOwner->AddGridObjectUpdate(GridObjectUpdate);
	}

	GridObjectComponentOwner->ExecuteNextGridObjectUpdate();
}

