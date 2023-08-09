#pragma once
#include "GameNode.h"

class Object : public GameNode
{
private:
	float _centerX;
	float _centerY;
	float _redius;	
	float _turnNum;
	

	bool _collider;

public:
	HRESULT init(void);

	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }
	float getRedius() { return _redius; }
	float getTurnNum() { return _turnNum; }
	bool getCollider() { return _collider; }
	

	void setCenterX(float centerX) { _centerX = centerX; }
	void setCenterY(float centerY) { _centerY = centerY; }
	void setRedius(float redius) { _redius = redius; }
	void setTurnNum(float turnNum) { _turnNum = turnNum; }
	void setCollider(bool collider) { _collider = collider; }

	Object();
	~Object();
};



/*class Object {
public:
    void DoSomething() {
        std::cout << "Object is doing something." << std::endl;
    }
};

// 객체 풀 클래스
class ObjectPool {
private:
    std::vector<Object*> objects; // 객체 포인터를 저장하는 벡터
    int poolSize; // 객체 풀 크기

public:
    ObjectPool(int size) : poolSize(size) {
        // 객체 풀을 초기화합니다.
        for (int i = 0; i < poolSize; ++i) {
            objects.push_back(new Object());
        }
    }

    ~ObjectPool() {
        // 객체 풀의 메모리를 정리합니다.
        for (Object* obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    Object* AcquireObject() {
        // 사용 가능한 객체를 가져옵니다.
        if (objects.empty()) {
            // 객체가 부족하면 새로 생성합니다.
            Object* newObj = new Object();
            objects.push_back(newObj);
            return newObj;
        }
        else {
            // 객체를 재사용합니다.
            Object* obj = objects.back();
            objects.pop_back();
            return obj;
        }
    }

    void ReleaseObject(Object* obj) {
        // 객체를 다시 풀에 반환합니다.
        objects.push_back(obj);
    }
};

int main() {
    ObjectPool pool(5); // 객체 풀 크기를 5로 설정합니다.

    // 객체 풀에서 객체를 가져와 사용합니다.
    Object* obj1 = pool.AcquireObject();
    obj1->DoSomething();

    Object* obj2 = pool.AcquireObject();
    obj2->DoSomething();

    // 사용이 끝난 객체를 풀에 반환합니다.
    pool.ReleaseObject(obj1);
    pool.ReleaseObject(obj2);

    // 다시 객체를 가져와 사용합니다.
    Object* obj3 = pool.AcquireObject();
    obj3->DoSomething();

    // 메모리 정리를 위해 객체 풀을 삭제합니다.
    delete obj3;

    return 0;
}*/