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

// ��ü Ǯ Ŭ����
class ObjectPool {
private:
    std::vector<Object*> objects; // ��ü �����͸� �����ϴ� ����
    int poolSize; // ��ü Ǯ ũ��

public:
    ObjectPool(int size) : poolSize(size) {
        // ��ü Ǯ�� �ʱ�ȭ�մϴ�.
        for (int i = 0; i < poolSize; ++i) {
            objects.push_back(new Object());
        }
    }

    ~ObjectPool() {
        // ��ü Ǯ�� �޸𸮸� �����մϴ�.
        for (Object* obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    Object* AcquireObject() {
        // ��� ������ ��ü�� �����ɴϴ�.
        if (objects.empty()) {
            // ��ü�� �����ϸ� ���� �����մϴ�.
            Object* newObj = new Object();
            objects.push_back(newObj);
            return newObj;
        }
        else {
            // ��ü�� �����մϴ�.
            Object* obj = objects.back();
            objects.pop_back();
            return obj;
        }
    }

    void ReleaseObject(Object* obj) {
        // ��ü�� �ٽ� Ǯ�� ��ȯ�մϴ�.
        objects.push_back(obj);
    }
};

int main() {
    ObjectPool pool(5); // ��ü Ǯ ũ�⸦ 5�� �����մϴ�.

    // ��ü Ǯ���� ��ü�� ������ ����մϴ�.
    Object* obj1 = pool.AcquireObject();
    obj1->DoSomething();

    Object* obj2 = pool.AcquireObject();
    obj2->DoSomething();

    // ����� ���� ��ü�� Ǯ�� ��ȯ�մϴ�.
    pool.ReleaseObject(obj1);
    pool.ReleaseObject(obj2);

    // �ٽ� ��ü�� ������ ����մϴ�.
    Object* obj3 = pool.AcquireObject();
    obj3->DoSomething();

    // �޸� ������ ���� ��ü Ǯ�� �����մϴ�.
    delete obj3;

    return 0;
}*/