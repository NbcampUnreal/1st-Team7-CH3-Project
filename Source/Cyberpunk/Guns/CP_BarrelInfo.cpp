#include "CP_BarrelInfo.h"

ACP_BarrelInfo::ACP_BarrelInfo()
{
    // 기본값 설정 (필요시 초기값 설정)
    PartName = "Unknown";
    bIsHitscan = false;
    Damage = 0.0f;

    // BarrelMesh 초기화 (필요시)
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
}

void ACP_BarrelInfo::InitializeBarrelInfo(const FString& MeshName)
{
    if (MeshName == "SK_BarrelBeam")
    {
        // 히트스캔, 데미지 50
        PartName = "SK_BarrelBeam";
        bIsHitscan = true;
        Damage = 50.0f;
    }
    else if (MeshName == "SK_BarrelBeamScatter")
    {
        // 히트스캔, 데미지 70
        PartName = "SK_BarrelBeamScatter";
        bIsHitscan = true;
        Damage = 70.0f;
    }
    else if (MeshName == "SK_BarrelBulletScatter")
    {
        // 프로젝타일, 데미지 100
        PartName = "SK_BarrelBulletScatter";
        bIsHitscan = false;
        Damage = 100.0f;
    }
    else if (MeshName == "SK_BarrelRocketScatter")
    {
        // 프로젝타일, 데미지 150
        PartName = "SK_BarrelRocketScatter";
        bIsHitscan = false;
        Damage = 150.0f;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Barrel: %s"), *MeshName);
    }
}


USkeletalMeshComponent* ACP_BarrelInfo::GetBarrelMesh() const
{
    return BarrelMesh;
}
