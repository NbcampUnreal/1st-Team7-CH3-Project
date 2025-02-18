#include "CP_BodyInfo.h"

ACP_BodyInfo::ACP_BodyInfo()
{
    // 기본값 설정 (필요시 초기값 설정)
    PartName = "Unknown";
    Damage = 0.0f;
    MovementSpeed = 1.0f;

    // BodyMesh 초기화 (필요시)
    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
}

void ACP_BodyInfo::InitializeBodyInfo(const FString& MeshName)
{
    if (MeshName == "SK_BodyTesla")
    {
        // 데미지 100, 이동속도 1.0배
        PartName = "SK_BodyTesla";
        Damage = 100.0f;
        MovementSpeed = 1.0f;
    }
    else if (MeshName == "SK_BodyNormal")
    {
        // 데미지 130, 이동속도 0.9배
        PartName = "SK_BodyNormal";
        Damage = 130.0f;
        MovementSpeed = 0.9f;
    }
    else if (MeshName == "SK_BodyFire")
    {
        // 데미지 200, 이동속도 0.5배
        PartName = "SK_BodyFire";
        Damage = 200.0f;
        MovementSpeed = 0.5f;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Body: %s"), *MeshName);
    }
}


USkeletalMeshComponent* ACP_BodyInfo::GetBodyMesh() const
{
    return BodyMesh;
}

