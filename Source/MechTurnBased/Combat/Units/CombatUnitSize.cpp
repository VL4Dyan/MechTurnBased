// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatUnitSize.h"

FCombatUnitSize::FCombatUnitSize()
{
	XLength = 1;
	YWidth = 1;
	ZHeight = 1;
}

FCombatUnitSize::FCombatUnitSize(int LengthToSet, int WidthToSet, int HeightToSet)
{
	XLength = LengthToSet;
	YWidth = WidthToSet;
	ZHeight = HeightToSet;

	if (XLength < 1)
	{
		XLength = 1;
	}
	if (YWidth < 1)
	{
		YWidth = 1;
	}
	if (ZHeight < 1)
	{
		ZHeight = 1;
	}
}
