#ifndef __SCENE_MGR_H__
#define __SCENE_MGR_H__

#include <list>
#include <map>
using std::list;
using std::map;

class SceneMgr
{
	struct Object {
		Object(int id, int x, int y, int radius) : _id(id), _x(x), _y(y), _radius(radius){}

		int _id;
		int _x;
		int _y;
		int _radius;

		list<Object*>::iterator _xIter;
		list<Object*>::iterator _yIter;
	};

public:
	SceneMgr();
	~SceneMgr();

	void Enter(int id, int x, int y, int dist);
	void Leave(int id);
	void Moving(int id, int newX, int newY);

	void printXList() const;
	void printYList() const;

private:
	void Update(Object *obj);
	void UpdateNewPosition(Object *obj, int x, int y);
	void GetRangeSet(Object *obj, map<int, Object*> &setRet);

private:
	list<Object*> _xList;
	list<Object*> _yList;
	map<int, Object*> _objects;

	map<int, Object*> _enterSet;
	map<int, Object*> _leaveSet;
	map<int, Object*> _movingSet;
};

#endif
