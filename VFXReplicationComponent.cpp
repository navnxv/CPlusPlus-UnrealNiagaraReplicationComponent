// Copyright (C) Navpreet Singh 2023, All Rights Reserved

#include "VFXReplicationComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "OOA/Utils/CustomUtils.h"

void UVFXReplicationComponent::ExecuteNiagaraOnServer_Implementation(ENiagaraType NiagaraType, UNiagaraSystem* NiagaraSystem,
	USceneComponent* AttachtoComponent, FName AttachPointname, FVector Location, FRotator Rotation, bool bAutoDestroy)
{
	ExecuteNiagaraOnNetMulticast(NiagaraType, NiagaraSystem, AttachtoComponent, AttachPointname, Location, Rotation, bAutoDestroy);
}

void UVFXReplicationComponent::ExecuteNiagaraOnNetMulticast_Implementation(ENiagaraType NiagaraType, UNiagaraSystem* NiagaraSystem,
	USceneComponent* AttachtoComponent, FName AttachPointname, FVector Location, FRotator Rotation, bool bAutoDestroy)
{
	if(!IsValid(NiagaraSystem)) return;
	
	UWorld* World = GetWorld();
	if(!IsValid(World)) return;
	
	// Checking and spawning niagara
	switch (NiagaraType)
	{
	case ENiagaraType::AtLocation:
		NiagaraEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, NiagaraSystem, Location, Rotation, FVector(1, 1, 1), bAutoDestroy);
		break;

	case ENiagaraType::SystemAttached:
		NiagaraEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraSystem, AttachtoComponent, AttachPointname, Location, Rotation, EAttachLocation::KeepWorldPosition, bAutoDestroy, true);
		break;

	default:
		PRINT_DEBUG_MESSAGE("Error spawning Niagara");
	}
}
