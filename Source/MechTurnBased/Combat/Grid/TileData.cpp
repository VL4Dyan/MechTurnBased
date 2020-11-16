#include "TileData.h"

FTileData::FTileData(float XAbsPosition, float YAbsPosition, float ZAbsPosition)
{
	AbsoluteCoordinates = FVector(XAbsPosition, YAbsPosition, ZAbsPosition);
}

FTileData::FTileData()
{
	AbsoluteCoordinates = FVector(0, 0, 0);
}