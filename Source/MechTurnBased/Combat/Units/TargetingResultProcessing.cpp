// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetingResultProcessing.h"

void UTargetingResultProcessing::ProcessTargetingResults(UActionResult* ActionTargetingResult, int Damage)
{
	/*TArray<UGridObjectComponentStateUpdate*> CompStatesToProcess = ActionTargetingResult->GetComponentStateUpdates();

	for (UGridObjectComponentStateUpdate* CompStateUpd : CompStatesToProcess)
	{
		FGridObjectComponentState CompState = CompStateUpd->GridObjectComponent->ComponentState;

		if (Damage > 0)
		{
			CompState.HullPoints = CompState.HullPoints - Damage;
			
			if (CompState.HullPoints < 0)
			{
				CompState.HullPoints = 0;
			}
		}

		CompStateUpd->GridObjectComponentStateReplacement = CompState;
	}*/
}
