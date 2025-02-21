#include "CP_Guns.h"

ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootScene);  

    FireTimer = 0.0f;
 
    // 기본 파츠 로드 (배럴, 바디, 트리거)
    LoadGunParts();
}

void ACP_Guns::LoadGunParts()
{
    USkeletalMesh* BarrelSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BarrelBulletScatter.SK_BarrelBulletScatter")));
    if (BarrelSkeletalMesh)
    {
        BarrelMesh->SetSkeletalMesh(BarrelSkeletalMesh);
        if (BarrelInfo)
        {
            BarrelInfo->Initialize("SK_BarrelBulletScatter");
        }
    }

    USkeletalMesh* BodySkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_BodyFire.SK_BodyFire")));
    if (BodySkeletalMesh)
    {
        BodyMesh->SetSkeletalMesh(BodySkeletalMesh);
    }

    USkeletalMesh* TriggerSkeletalMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/DUWepCustSys/Meshes/SK_TriggerSingle.SK_TriggerSingle")));
    if (TriggerSkeletalMesh)
    {
        TriggerMesh->SetSkeletalMesh(TriggerSkeletalMesh);
    }

    
}

void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    NiagaraEffect->Deactivate();
    FireTimer += DeltaTime;
    if (FireTimer >= 0.3f)
    {
        Fire();
        FireTimer = 0.0f;
    }
}

void ACP_Guns::Fire()
{
    if (BarrelInfo)
    {
        if (BarrelInfo->bIsHitscan)
        {
            // FireHitscan();
        }
        else
        {
            FireProjectile();
        }
    }
}

void ACP_Guns::FireProjectile()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));
    FVector ForwardVector = BarrelMesh->GetSocketRotation(FName("Muzzle")).Vector();
    FVector LaunchDirection = ForwardVector;
    FVector Velocity = LaunchDirection * 8000.f;

    // 나이아가라 이펙트 활성화
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();

        // 0.1초 후에 비활성화하는 타이머 설정
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            this,
            &ACP_Guns::DeactivateNiagaraEffect,
            0.1f,
            false
        );
    }

    if (ProjectileClass)
    {
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, FRotator::ZeroRotator);
        if (Projectile)
        {
            Projectile->SetOwner(this);

            if (Projectile->ProjectileMovement)
            {
                Projectile->ProjectileMovement->Velocity = Velocity;
                Projectile->ProjectileMovement->Activate();
            }
        }
    }
}

void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
    }
}