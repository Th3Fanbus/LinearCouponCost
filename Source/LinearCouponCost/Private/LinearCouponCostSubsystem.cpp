/* SPDX-License-Identifier: MPL-2.0 */

#include "LinearCouponCostSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ALinearCouponCostSubsystem* ALinearCouponCostSubsystem::Get(const UObject* WorldContext)
{
	return Cast<ALinearCouponCostSubsystem>(UGameplayStatics::GetActorOfClass(WorldContext, ALinearCouponCostSubsystem::StaticClass()));
}

void ALinearCouponCostSubsystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALinearCouponCostSubsystem, CouponCost_DefaultTrack);
	DOREPLIFETIME(ALinearCouponCostSubsystem, CouponCost_ExplorationTrack);
}

int64 ALinearCouponCostSubsystem::GetCouponCostForSinkTrack(EResourceSinkTrack SinkTrack) const
{
	switch (SinkTrack) {
	case EResourceSinkTrack::RST_Default:
		return CouponCost_DefaultTrack;
	case EResourceSinkTrack::RST_Exploration:
		return CouponCost_ExplorationTrack;
	default:
		return 0;
	}
}
