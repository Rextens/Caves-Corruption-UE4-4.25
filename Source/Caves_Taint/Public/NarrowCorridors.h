// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Biome.h"

/**
 * 
 */
class NarrowCorridors : public Biome
{
public:
	NarrowCorridors();

	float generator(const FVoxelFastNoise &noise, const v_flt& X, const v_flt& Y, const v_flt& Z) override;
};
