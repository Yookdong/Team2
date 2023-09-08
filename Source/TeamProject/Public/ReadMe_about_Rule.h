// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class TEAMPROJECT_API ReadMe_about_Rule
{
public:
	/*******
	* 
	* https://docs.unrealengine.com/4.27/ko/ProductionPipelines/DevelopmentSetup/CodingStandard/
	* 언리얼 공식 문서 한 번 보고 오시면 됩니다.
	* 그 외 규칙
	*
	코드 작성 규칙

	1. 네이밍 규칙 - 얼리얼 API 사용 시 제외하고
		1) 클래스 멤버 변수 및 함수
			대문자 시작
			띄어쓰기 없이 대/소문자로 구분
			줄임말 사용 X
			ex) PlayerController
		
		2) 지역 변수
			소문자 시작
			띄어쓰기 없이 대/소문자로 구분
			줄임말 사용
			ex) pContr -> player controller 를 의미함

		3) 함수의 매개변수
			모두 소문자
			줄임말 사용
			ex) void Test(APlayerController pc); pc -> player controller 를 의미함

		4) enum / #define 사용 시 모두 대문자
			ex) enum class ITEMTYPE {} / #define BASICHP 10;

	2. 변수 생성 시 유의사항
		1) 모든 변수는 Private / Protected 로 생성한다. public 으로 생성 금지
		어짜피 모든 변수는 에디터에서 사용가능
			private -> 더 이상 상속을 주지 않을 변수
			protected -> 상속 받은 클래스에서도 사용할 변수

		2) 그래서 모든 변수는 Getter 와 Setter 함수를 가진다.
		2-1) Getter 와 Setter 함수의 경우에는 한 줄로 작성하면 된다.
		굳이 cpp 에 정의할 필요 없다.
			ex)
			private:
				int CurrentHP
				class AnimMontage* ReloadAnimMontage;
			
			public:
			// Getter
			int GetCurrentHP() { return CurrentHP; }
			AnimMontage* GetReloadAnimMontage() { return ReloadAnimMontage; }

			// Setter
			void SetCurrentHP(int curhp) { CurrentHP = curhp; }
			void SetReloadAnimMontage(AnimMontage* reloadanim) { ReloadAnimMontage = reloadanim; }


		3) 모든 언리얼 변수는 전방 선언 및 포인터로 생성한다.
			언리얼 변수 생성 시 class 키워드 필수
			ex) StaticMeshComponent 변수 생성 시
				class StaticMeshComponent* StaticMesh;

		4) bool, enum 등 특정 변수의 경우 이름에 알려준다.
			ex) bool bIsCanUse;
			ITEMTYPE eItemType;

		5) 특정 상황 제외하고 모든 변수는 생성자에서 초기화한다.
		가끔 포인터 변수의 경우에는 쓰레기 값 방지용으로 nullptr 로 초기화하기도 함


		더 필요하다고 생각하는 규칙 있으면 추가해주시면 됩니다!!!!!!
			
	

	******/
};
