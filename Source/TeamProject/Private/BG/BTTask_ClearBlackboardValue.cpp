// Fill out your copyright notice in the Description page of Project Settings.


#include "BG/BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//BlackboardKey로 FName을 반환한다.
	//GetSelectedBlackboardKey();
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	//Succeeded를 반환한다.
	return EBTNodeResult::Succeeded;
}