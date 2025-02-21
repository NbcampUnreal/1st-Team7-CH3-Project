#include "CP_BarrelInfo.h"


ACP_BarrelInfo::ACP_BarrelInfo()
{
    RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    RootComponent = RootSceneComponent; 
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootSceneComponent);  
}

void ACP_BarrelInfo::Initialize(const FString& MeshName)
{
    if (MeshName == "SK_BarrelBeam")
    {
        PartName = "SK_BarrelBeam";
        Damage = 100.0f;
        bIsHitscan = false;

        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeam.SK_BarrelBeam")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BarrelBeamScatter")
    {
        PartName = "SK_BarrelBeamScatter";
        Damage = 120.0f;
        bIsHitscan = true;

        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBeamScatter.SK_BarrelBeamScatter")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else if (MeshName == "SK_BarrelBulletScatter")
    {
        PartName = "SK_BarrelBulletScatter";
        Damage = 150.0f;
        bIsHitscan = false;

        USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
        if (LoadedMesh)
        {
            BarrelMesh->SetSkeletalMesh(LoadedMesh);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to load Mesh: %s"), *MeshName);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Barrel: %s"), *MeshName);
    }
}

USkeletalMeshComponent* ACP_BarrelInfo::GetMesh() const
{
    return BarrelMesh;
}
