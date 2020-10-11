// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include "VoxelMaterialBuilder.h"

TVoxelSharedRef<FVoxelWorldGeneratorInstance> UWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FVoxelCavesWorldGeneratorInstance>(*this);
}

///////////////////////////////////////////////////////////////////////////////

FVoxelCavesWorldGeneratorInstance::FVoxelCavesWorldGeneratorInstance(UWorldGenerator& MyGenerator) : Super(&MyGenerator), NoiseHeight(MyGenerator.NoiseHeight)
{
}

void FVoxelCavesWorldGeneratorInstance::Init(const FVoxelWorldGeneratorInit& InitStruct)
{
	static const FName SeedName = "MySeed";
	Noise.SetSeed(InitStruct.Seeds.Contains(SeedName) ? InitStruct.Seeds[SeedName] : 1337);
}

v_flt FVoxelCavesWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	//const float Height = Noise.GetPerlin_3D(X * 0.01f, Y * 0.01f, Z * 0.02f, 1.0f);

	const float Height = Noise.GetValueFractal_3D(X * 0.01f, Y * 0.01f, Z * 0.01f, 1.0f, 12);// * Noise.GetValueFractal_3D(X, Y, Z, 0.02f, 6);
	
	return Height;
}

FVoxelMaterial FVoxelCavesWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{ 
	FVoxelMaterialBuilder builder;
	builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	builder.SetSingleIndex(1);

	if (Noise.GetCellular_3D(X, Y, Z, 0.001f) < 0.5f) {
		return builder.Build();
	}

	//builder.SetSingleIndex(1);

	return FVoxelMaterial::Default(); //Just to return something
}

TVoxelRange<v_flt> FVoxelCavesWorldGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const
{
	// Return the values that GetValueImpl can return in Bounds
	// Used to skip chunks where the value does not change
	// Be careful, if wrong your world will have holes!
	// By default return infinite range to be safe
	return TVoxelRange<v_flt>::Infinite();

	// Example for the GetValueImpl above

	// Noise is between -1 and 1
	const TVoxelRange<v_flt> Height = TVoxelRange<v_flt>(-1, 1) * NoiseHeight;

	// Z can go from min to max
	TVoxelRange<v_flt> Value = TVoxelRange<v_flt>(Bounds.Min.Z, Bounds.Max.Z) - Height;

	Value /= 5;

	return Value;
}

FVector FVoxelCavesWorldGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}
