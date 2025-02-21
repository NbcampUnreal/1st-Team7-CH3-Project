#include "CP_Projectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ACP_Projectile::ACP_Projectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // 충돌 컴포넌트 설정 (루트 컴포넌트로 사용)
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(10.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));  // 충돌 설정
    RootComponent = CollisionComponent;

    // 나이아가라 이펙트 설정
    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootComponent);

    // 나이아가라 시스템 할당
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystem(TEXT("/Game/Gun_BluePrint/NS_bullet.NS_bullet"));
    if (NiagaraSystem.Succeeded())
    {
        NiagaraEffect->SetAsset(NiagaraSystem.Object);
    }

    // 프로젝타일 움직임 설정
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 2000.f;
    ProjectileMovement->MaxSpeed = 2000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.0f;  // 중력 영향 제거

    // 충돌 이벤트 바인딩
    CollisionComponent->OnComponentHit.AddDynamic(this, &ACP_Projectile::OnHit);
}

void ACP_Projectile::BeginPlay()
{
    Super::BeginPlay();

    // 2초 후 자동 제거
    SetLifeSpan(2.0f);

    // 나이아가라 이펙트 시작
    if (NiagaraEffect)
    {
        NiagaraEffect->Activate(true);
        UE_LOG(LogTemp, Warning, TEXT("NiagaraEffect 활성화!"));
    }
}

// 발사 함수
void ACP_Projectile::LaunchProjectile(const FVector& LaunchDirection)
{
    if (ProjectileMovement)
    {
        // 발사 방향 설정
        FVector LaunchVelocity = LaunchDirection * 2000.f;
        ProjectileMovement->Velocity = LaunchVelocity;
        ProjectileMovement->Activate();

        UE_LOG(LogTemp, Warning, TEXT("프로젝트 발사! 방향: %s"), *LaunchDirection.ToString());
    }
}

// 충돌 시 호출될 함수
void ACP_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {

        // 여기서 충돌 효과 추가 가능
        // 
        Destroy();  // 충돌 시 삭제
    }
}
