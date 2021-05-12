// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreMechComponent.h"

UCoreMechComponent::UCoreMechComponent()
{

}

void UCoreMechComponent::UpdateComponentState(FGridObjectComponentState ComponentStateReplacement)
{
	ComponentState = ComponentStateReplacement;

	if (ComponentState.HullPoints <= 0)
	{
		FGridObjectUpdate MechComponentOwnerUpdate = FGridObjectUpdate();

		MechComponentOwnerUpdate.VisualUpdateType = EGridObjectUpdateType::GOUT_Death;
	}
}
