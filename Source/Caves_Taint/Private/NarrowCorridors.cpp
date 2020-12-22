// Fill out your copyright notice in the Description page of Project Settings.


#include "NarrowCorridors.h"

NarrowCorridors::NarrowCorridors()
{
	frequency = 2;
	meshID = 0;
}

float NarrowCorridors::generator(const FVoxelFastNoise &noise, const v_flt &X, const v_flt& Y, const v_flt& Z)
{
	return noise.GetValueFractal_3D(X * 0.01f + 0.5f, Y * 0.01f + 0.5f, Z * 0.01f + 0.5f, 1.02f, 12) * cos(noise.GetCellular_3D(X + 0.5f, Y + 0.5f, Z + 0.5f, 0.09f) * PI * 2);
}

