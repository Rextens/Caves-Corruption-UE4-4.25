// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VoxelFastNoise.h"

/**
 * 
 */

class Biome
{
public:
	float frequency = 0;

	int32 size = 0;

	int32 meshID = 0;

	virtual float generator(const FVoxelFastNoise &noise, const v_flt& X, const v_flt& Y, const v_flt& Z) { return 0.0f; };
};
