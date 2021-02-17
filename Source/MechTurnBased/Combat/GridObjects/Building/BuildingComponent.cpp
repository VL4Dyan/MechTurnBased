// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingComponent.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatGridManagerRef = Cast<ACombatMode>(GetWorld()->GetAuthGameMode())->GetCombatGridManagerRef();
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBuildingComponent::IsComponentABase()
{
	return bIsABase;
}

void UBuildingComponent::RemoveConnectionToComponent(UBuildingComponent* ComponentRefToRemove)
{
	for (int i = 0; i < NextComponents.Num(); i++)
	{
		if (NextComponents[i] == ComponentRefToRemove)
		{
			NextComponents.RemoveAt(i);
			break;
		}
	}

	for (int i = 0; i < PreviousComponents.Num(); i++)
	{
		if (PreviousComponents[i] == ComponentRefToRemove)
		{
			PreviousComponents.RemoveAt(i);
			break;
		}
	}

	TryToDestroyYourself();
}

bool UBuildingComponent::TryToDestroyYourself()
{
	if ((PreviousComponents.Num() == 0 && !bIsABase) || ComponentState.HullPoints == 0)
	{
		for (UBuildingComponent* Component : NextComponents)
		{
			Component->RemoveConnectionToComponent(this);
		}

		FTileData TileDataToUpdate;
		CombatGridManagerRef->TryGetTileDataByIndex(OccupiedTileIndex, TileDataToUpdate);
		TileDataToUpdate.TileHolder = nullptr;
		CombatGridManagerRef->TryUpdateTileData(OccupiedTileIndex, TileDataToUpdate);

		DeactivateComponent();

		CollisionBoxRef->DestroyComponent();
		this->DestroyComponent();

		return true;
	}

	return false;
}

void UBuildingComponent::NotifyNextComponentsOfAcquirementOfABaseComponent(UBuildingComponent* BaseComponent)
{
	if (PreviousComponents.Num() == 0)
	{
		for (UBuildingComponent* Component : NextComponents)
		{
			Component->NotifyNextComponentsOfAcquirementOfABaseComponent(this);
		}
	}

	PreviousComponents.Add(BaseComponent);
}

void UBuildingComponent::UpdateComponentState(FGridObjectComponentState ComponentStateReplacement)
{
	ComponentState = ComponentStateReplacement;

	TryToDestroyYourself();
}

void UBuildingComponent::ActivateComponent()
{
	if (bIsAPlatform)
	{
		FTileData TileData;
		FMatrixIndex TileIndex = OccupiedTileIndex;
		TileIndex.IndexZ++;
		if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, TileData))
		{
			TileData.bIsVoid = false;

			CombatGridManagerRef->TryUpdateTileData(TileIndex, TileData);
		}
	}
}

void UBuildingComponent::DeactivateComponent()
{
	if (bIsAPlatform)
	{
		FTileData TileData;
		FMatrixIndex TileIndex = OccupiedTileIndex;
		TileIndex.IndexZ++;
		if (CombatGridManagerRef->TryGetTileDataByIndex(TileIndex, TileData))
		{
			AGridObject* GridObjectRef = TileData.TileHolder;
			TileData.bIsVoid = false;

			CombatGridManagerRef->TryUpdateTileData(TileIndex, TileData);

			if (GridObjectRef != nullptr)
			{
				GridObjectRef->TryToFall();
			}
		}
	}
}

