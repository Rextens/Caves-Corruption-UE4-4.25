// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"
#include <ctime>
#include <cmath>
#include "VoxelTools/VoxelDataTools.h"
#include "SaveWorld.h"
#include "Kismet/GameplayStatics.h"
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

	initBiome(new NarrowCorridors());
	initBiome(new DarkCorridors());

	//worldReference;

	PerlinWormsNoise.SetSeed(seed / 2);
}

v_flt FVoxelCavesWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	float Height = Noise.GetValueFractal_3D(X * 0.01f + 0.5f, Y * 0.01f + 0.5f, Z * 0.01f + 0.5f, 1.2f, 12);
	
	float height = abs(Noise.GetCellular_3D(X + 0.5f, Y + 0.5f, Z + 0.5f, 0.001f)) * biomeFrequences;
	float summedBiomesHeight = 0;

	for (int i = 0; i < biomeReferences.Num(); ++i)
	{
		if (biomeReferences[i] != nullptr)
		{
			summedBiomesHeight += biomeReferences[i]->frequency;
			if (summedBiomesHeight >= height)
			{
				return biomeReferences[i]->generator(Noise, X, Y, Z);
			}
		}
	}

	return 0.0f;
}

FVoxelMaterial FVoxelCavesWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{ 
	FVoxelMaterialBuilder builder;
	builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);

	float height = abs(Noise.GetCellular_3D(X + 0.5f, Y + 0.5f, Z + 0.5f, 0.001f)) * biomeFrequences;
	float summedBiomesHeight = 0;
	
	for (int i = 0; i < biomeReferences.Num(); ++i)
	{
		summedBiomesHeight += biomeReferences[i]->frequency;
		if (summedBiomesHeight >= height)
		{
			builder.SetSingleIndex(biomeReferences[i]->meshID);


			return builder.Build();
		}
	}

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

void FVoxelCavesWorldGeneratorInstance::initBiome(Biome* biomeReference)
{
	biomeReferences.Add(biomeReference);
	biomeFrequences += biomeReference->frequency;
	biomeSizes += biomeReference->size;
}

