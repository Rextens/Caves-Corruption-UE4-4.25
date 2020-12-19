// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "VoxelFastNoise.h"
#include "VoxelWorldGenerators/VoxelWorldGeneratorHelpers.h"
#include "VoxelMaterialBuilder.h"
#include "Engine/World.h"
#include "VoxelTools/VoxelDataTools.h"
#include "VoxelData/VoxelData.h"
#include "VoxelWorld.h"
#include "Biome.h"
#include "DarkCorridors.h"
#include "NarrowCorridors.h"
#include <map>
#include "TestSubject.h"
#include "WorldGenerator.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UWorldGenerator : public UVoxelWorldGenerator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Generator")
		float NoiseHeight = 10.f;

	//~ Begin UVoxelWorldGenerator Interface
	virtual TVoxelSharedRef<FVoxelWorldGeneratorInstance> GetInstance() override;

	//~ End UVoxelWorldGenerator Interface
};

/*
class AdditionalGenerations 
{
public:
	AdditionalGenerations();
	AdditionalGenerations(const AVoxelWorld* worldReference);

	const AVoxelWorld *ref;

	void generatePerlinWorms(const float& X, const float& Y, const float& Z, const int& interval, const int& range, FVoxelFastNoise &PerlinWormsNoise);
	void setMaterialInArea(const FVector& start, const FVector& end, const int& range);
};

*/

class FVoxelCavesWorldGeneratorInstance : public TVoxelWorldGeneratorInstanceHelper<FVoxelCavesWorldGeneratorInstance, UWorldGenerator>
{
public:
	using Super = TVoxelWorldGeneratorInstanceHelper<FVoxelCavesWorldGeneratorInstance, UWorldGenerator>;

	explicit FVoxelCavesWorldGeneratorInstance(UWorldGenerator& MyGenerator);

	//~ Begin FVoxelWorldGeneratorInstance Interface
	virtual void Init(const FVoxelWorldGeneratorInit& InitStruct) override;

	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;

	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;

	virtual FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelWorldGeneratorInstance Interface
	
	TArray<TestSubject*> testReferences;
	TArray<Biome*> biomeReferences;
	float biomeFrequences;
	int32 biomeSizes;

	void initBiome(Biome* biomeReference);

	int32 seed;

	const float NoiseHeight;
	FVoxelFastNoise Noise;
	FVoxelFastNoise PerlinWormsNoise;
};
