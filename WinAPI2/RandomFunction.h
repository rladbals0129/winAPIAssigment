#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// GetTickCount() : API 공용 함수
		// ㄴ API 함수로 OS가 부팅된 후의 경과 시간을 체크해 준다
		// ㄴ 밀리세컨 단위로 체크 가능하며 밀리세컨 단위로 시간 값을 반환하기 때문에 규모가 크지 않은 로직에 부합한다.
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init(void) 
	{
		return S_OK;
	}

	inline int getInt(int num)
	{
		return rand() % num;
	}

	inline int getFromIntTo(int fromNum, int toNum) //범위 지정 랜덤
	{
		//if 로 체크해야할것??
		// 0 0 넣으면 안댐
		// 의도적으로 터트릴거 아니면 if 넣을필요없음
		// 따라서 생략
		//0을 조심하자
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;

	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}


};
