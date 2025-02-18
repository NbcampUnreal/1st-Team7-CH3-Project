#include "CP_TriggerInfo.h"

ACP_TriggerInfo::ACP_TriggerInfo()
{
    // 기본값 설정 (필요시 초기값 설정)
    PartName = "Unknown";
    Damage = 0.0f;
    MagazineCapacity = 0;
}

void ACP_TriggerInfo::InitializeTriggerInfo(const FString& MeshName)
{
    if (MeshName == "SK_TriggerAuto")
    {
        // 데미지 10, 탄창 크기 70
        PartName = "SK_TriggerAuto";
        Damage = 10.0f;
        MagazineCapacity = 70;
    }
    else if (MeshName == "SK_TriggerBurst")
    {
        // 데미지 20, 탄창 크기 60
        PartName = "SK_TriggerBurst";
        Damage = 20.0f;
        MagazineCapacity = 60;
    }
    else if (MeshName == "SK_StockStandard")
    {
        // 데미지 25, 탄창 크기 50
        PartName = "SK_StockStandard";
        Damage = 25.0f;
        MagazineCapacity = 50;
    }
    else if (MeshName == "SK_StockHeavy")
    {
        // 데미지 30, 탄창 크기 30
        PartName = "SK_StockHeavy";
        Damage = 30.0f;
        MagazineCapacity = 30;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unknown Trigger: %s"), *MeshName);
    }

}
USkeletalMeshComponent* ACP_TriggerInfo::GetTriggerMesh() const
{
    return TriggerMesh;
}