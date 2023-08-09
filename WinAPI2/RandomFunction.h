#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// GetTickCount() : API ���� �Լ�
		// �� API �Լ��� OS�� ���õ� ���� ��� �ð��� üũ�� �ش�
		// �� �и����� ������ üũ �����ϸ� �и����� ������ �ð� ���� ��ȯ�ϱ� ������ �Ը� ũ�� ���� ������ �����Ѵ�.
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

	inline int getFromIntTo(int fromNum, int toNum) //���� ���� ����
	{
		//if �� üũ�ؾ��Ұ�??
		// 0 0 ������ �ȴ�
		// �ǵ������� ��Ʈ���� �ƴϸ� if �����ʿ����
		// ���� ����
		//0�� ��������
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
