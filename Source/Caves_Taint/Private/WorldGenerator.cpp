// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include <ctime>
#include "VoxelTools/VoxelDataTools.h"
#include "SaveWorld.h"
#include "Kismet/GameplayStatics.h"
#include "VoxelMaterialBuilder.h"

TVoxelSharedRef<FVoxelWorldGeneratorInstance> UWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FVoxelCavesWorldGeneratorInstance>(*this);

	
}
/*
AdditionalGenerations::AdditionalGenerations()
{

}

AdditionalGenerations::AdditionalGenerations(const AVoxelWorld* worldReference)
{
	ref = worldReference;
}

void AdditionalGenerations::generatePerlinWorms(const float& X, const float& Y, const float& Z, const int& interval, const int& range, FVoxelFastNoise &PerlinWormsNoise)
{
	if (ref != nullptr)
	{
		TArray<FVector> vectors;

		for (int i = 0; i < interval; ++i) {
			vectors.Add(FVector(PerlinWormsNoise.GetPerlin_3D(X + 0.5f + i, Y + 0.5f, Z + 0.5f, 3.02f) * 360.0f, PerlinWormsNoise.GetPerlin_3D(X + 0.5f + i, Y + 0.5f, Z + 1.5f, 3.02f) * 360.0f, PerlinWormsNoise.GetPerlin_3D(X + 0.5f + i, Y + 0.5f, Z + 2.5f, 3.02f) * 360.0f));
		}

		for (int i = 0; i < interval; ++i) {
			for (int j = 0; j < range; ++j) {
				UVoxelDataTools::SetMaterial((AVoxelWorld*)ref, FIntVector(1, 2, 3), )
			}
		}
	}
}

void AdditionalGenerations::setMaterialInArea(const FVector& start, const FVector& end, const int& range)
{
	FVoxelMaterialBuilder builder;
	builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	builder.SetSingleIndex(2);

	for (int i = 0; i < 10000; ++i) {
		for (int j = 0; j < 10000; ++j) {
			for (int k = 0; k < 10000; ++k) {
				UVoxelDataTools::SetMaterial((AVoxelWorld*)ref, FIntVector(i, j, k), )
			}
		}
	}
}
*/

///////////////////////////////////////////////////////////////////////////////

FVoxelCavesWorldGeneratorInstance::FVoxelCavesWorldGeneratorInstance(UWorldGenerator& MyGenerator) : Super(&MyGenerator), NoiseHeight(MyGenerator.NoiseHeight)
{
}

void FVoxelCavesWorldGeneratorInstance::Init(const FVoxelWorldGeneratorInit& InitStruct)
{
	USaveWorld* loadWorldInstance = Cast<USaveWorld>(UGameplayStatics::CreateSaveGameObject(USaveWorld::StaticClass()));
	loadWorldInstance = Cast<USaveWorld>(UGameplayStatics::LoadGameFromSlot(TEXT("currentSeed"), 0));

	if (loadWorldInstance)
	{
		Noise.SetSeed(loadWorldInstance->seed);
	}
	else
	{
		static const FName SeedName = "MySeed";
		srand(time(nullptr));
		Noise.SetSeed(InitStruct.Seeds.Contains(SeedName) ? InitStruct.Seeds[SeedName] : rand());
	}

	seed = Noise.GetSeed();
	/*
	USaveWorld* saveWorldInstance = Cast<USaveWorld>(UGameplayStatics::CreateSaveGameObject(USaveWorld::StaticClass()));

	if (saveWorldInstance)
	{
		saveWorldInstance->seed;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not loaded"));
	}
	//saveWorldInstance->seed = seed; //it crashes here
	UGameplayStatics::SaveGameToSlot(saveWorldInstance, TEXT("worldSeed"), 0);
	*/


	//worldReference;

	PerlinWormsNoise.SetSeed(seed / 2);
}

v_flt FVoxelCavesWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	//const float Height = Noise.GetPerlin_3D(X * 0.01f, Y * 0.01f, Z * 0.02f, 1.0f);

	const float Height = Noise.GetValueFractal_3D(X * 0.01f, Y * 0.01f, Z * 0.01f, 1.2f, 12);// * Noise.GetValueFractal_3D(X, Y, Z, 0.02f, 6);

	//VoxelBuffer::bufferFunction(Height);

	return Height;
}

FVoxelMaterial FVoxelCavesWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{ 
	FVoxelMaterialBuilder builder;
	builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);
	
	if (Noise.GetCellular_3D(X + 0.5f, Y + 0.5f, Z + 0.5f, 0.001f) < 0.5f) {
		builder.SetSingleIndex(0);
	}
	else {
		builder.SetSingleIndex(1);
	}

	if (Noise.GetValueFractal_3D(X * 0.07f + 0.5f, Y * 0.07f + 0.5f, Z * 0.07f + 0.5f, 1.0f, 1) > 0.9f) {
		builder.SetSingleIndex(2);
 

	}

	return builder.Build();

	/*
	if (Noise.GetPerlin_3D(X, Y, Z, 1.0f) < 0.9) {
		builder.SetSingleIndex(1);
	}
	else {
		builder.SetSingleIndex(2);
	}
	if (Noise.GetCellular_3D(X, Y, Z, 0.001f) < 0.5f) {
		return builder.Build();
	}
	*/

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

