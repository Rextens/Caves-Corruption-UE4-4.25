// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "VoxelFastNoise.h"
#include "VoxelWorldGenerators/VoxelWorldGeneratorHelpers.h"
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

private:
	const float NoiseHeight;
	FVoxelFastNoise Noise;
};
