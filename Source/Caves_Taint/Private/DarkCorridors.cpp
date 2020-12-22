// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkCorridors.h"

DarkCorridors::DarkCorridors()
{
	frequency = 2;
	meshID = 1;
}

float DarkCorridors::generator(const FVoxelFastNoise& noise, const v_flt& X, const v_flt& Y, const v_flt& Z)
{
	return noise.GetValueFractal_3D(X * 0.01f + 0.5f, Y * 0.01f + 0.5f, Z * 0.01f + 0.5f, 1.2f, 12);
}
