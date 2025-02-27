#include "CP_Guns.h"

/** 생성자 */
ACP_Guns::ACP_Guns()
{
    PrimaryActorTick.bCanEverTick = true;

    /** 루트 씬 설정 */
    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    RootComponent = RootScene;

    /** 무기 파츠 생성 */
    BarrelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BarrelMesh"));
    BarrelMesh->SetupAttachment(RootScene);

    BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootScene);

    TriggerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TriggerMesh"));
    TriggerMesh->SetupAttachment(RootScene);

    /** 파츠 정보 생성 */
    BarrelInfo = CreateDefaultSubobject<ACP_BarrelInfo>(TEXT("BarrelInfo"));
    BodyInfo = CreateDefaultSubobject<ACP_BodyInfo>(TEXT("BodyInfo"));
    TriggerInfo = CreateDefaultSubobject<ACP_TriggerInfo>(TEXT("TriggerInfo"));

    /** 나이아가라 이펙트 설정 */
    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootScene);

    /** 오디오 컴포넌트 설정 */
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootScene);

    /** Tactical Light 설정 */
    TacticalLightComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("TacticalLight"));
    TacticalLightComponent->SetupAttachment(BodyMesh, FName("Light"));

    static ConstructorHelpers::FClassFinder<AActor> LightBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BP_TacticalLight.BP_TacticalLight_C'"));
    if (LightBPClass.Succeeded())
    {
        TacticalLightComponent->SetChildActorClass(LightBPClass.Class);
    }

    /** 발사 타이머 설정 */
    FireTimer = 0.0f;

    /** 발사할 프로젝타일 설정 */
    static ConstructorHelpers::FClassFinder<ACP_Projectile> ProjectileBPClass(TEXT("Blueprint'/Game/Gun_BluePrint/BP_Projectile.BP_Projectile_C'"));
    if (ProjectileBPClass.Succeeded())
    {
        ProjectileClass = ProjectileBPClass.Class;
    }

    /** 발사 사운드 설정 */
    static ConstructorHelpers::FObjectFinder<USoundCue> FireSoundCueAsset(TEXT("SoundCue'/Game/Gun_BluePrint/MuzzleFlash/Demo/FPWeapon/Cue/FirstPersonTemplateWeaponFire02_Cue.FirstPersonTemplateWeaponFire02_Cue'"));
    if (FireSoundCueAsset.Succeeded() && AudioComponent)
    {
        AudioComponent->SetSound(FireSoundCueAsset.Object);
    }

    /** 기본 파츠 로드 */
    LoadGunParts();
}

/** 기본 파츠 로드 */
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

        UNiagaraSystem* NiagaraAsset = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, TEXT("NiagaraSystem'/Game/Gun_BluePrint/MuzzleFlash/MuzzleFlash/Niagara/NS_MuzzleFlash.NS_MuzzleFlash'")));
        if (NiagaraAsset)
        {
            NiagaraEffect->SetAsset(NiagaraAsset);
            NiagaraEffect->SetupAttachment(BarrelMesh, FName("Muzzle"));
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

/** 틱 함수 */
void ACP_Guns::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    NiagaraEffect->Deactivate();

    FireTimer += DeltaTime;
    if (FireTimer >= 0.1f)
    {
        Fire();
        FireTimer = 0.0f;
    }
}

/** 무기 발사 */
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

/** 프로젝타일 발사 */
void ACP_Guns::FireProjectile()
{
    FVector MuzzleLocation = BarrelMesh->GetSocketLocation(FName("Muzzle"));

    /** 머즐의 Right 벡터를 가져와서 발사 방향 계산 */
    FVector RightVector = BarrelMesh->GetSocketTransform(FName("Muzzle")).GetRotation().GetRightVector();
    FVector LaunchDirection = RightVector;
    FVector Velocity = LaunchDirection * 8000.f;

    /** 나이아가라 이펙트 활성화 */
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate();

        /** 0.1초 후에 나이아가라 이펙트 비활성화 */
        GetWorld()->GetTimerManager().SetTimer(
            TimerHandle,
            this,
            &ACP_Guns::DeactivateNiagaraEffect,
            0.1f,
            false
        );
    }

    /** 발사 사운드 재생 */
    if (AudioComponent)
    {
        AudioComponent->Play();
    }

    /** 프로젝타일 스폰 */
    if (ProjectileClass)
    {
        FRotator ProjectileRotation = LaunchDirection.Rotation();
        ACP_Projectile* Projectile = GetWorld()->SpawnActor<ACP_Projectile>(ProjectileClass, MuzzleLocation, ProjectileRotation);
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

/** 나이아가라 이펙트 비활성화 */
void ACP_Guns::DeactivateNiagaraEffect()
{
    if (NiagaraEffect)
    {
        NiagaraEffect->Deactivate();
    }
}
