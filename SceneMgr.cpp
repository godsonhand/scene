#include "stdafx.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "SceneMgr.h"

SceneMgr::SceneMgr()
{
}

SceneMgr::~SceneMgr()
{
	map<int, Object*>::iterator iter = _objects.begin();
	while(iter != _objects.end())
	{
		delete iter++->second;
	}
}


void SceneMgr::Enter(int id, int x, int y, int dist)
{
	if(_objects.find(id) != _objects.end())
		return;

	Object *newObj = new Object(id, x, y, dist);
	_objects[id] = newObj;

	map<int, Object*> xSet;

	bool flag = false;
	list<Object*>::iterator posXIter = _xList.end();
	for(list<Object*>::iterator iter = _xList.begin(); iter != _xList.end(); ++iter)
	{
		int distDiff = (*iter)->_x - x;
		if(!flag && distDiff > 0)
		{
			posXIter = iter;
			flag = true;
		}
		if(abs(distDiff) <= dist)
			xSet[(*iter)->_id] = *iter;
		if(distDiff > dist)
			break;
	}

	newObj->_xIter = _xList.insert(posXIter, newObj);

	flag = false;
	list<Object*>::iterator posYIter = _yList.end();
	for(list<Object*>::iterator iter = _yList.begin(); iter != _yList.end(); ++iter)
	{
		int distDiff = (*iter)->_y - y;
		if(!flag && distDiff > 0)
		{
			posYIter = iter;
			flag = true;
		}

		if(abs(distDiff) <= dist && xSet.find((*iter)->_id) != xSet.end())
			_enterSet[(*iter)->_id] = *iter;

		if(distDiff > distDiff)
			break;
	}
	
	newObj->_yIter = _yList.insert(posYIter, newObj);

	Update(newObj);
}

void SceneMgr::Leave(int id)
{
	map<int, Object*>::iterator objIter = _objects.find(id);
	if(objIter == _objects.end())
		return;
	
	Object *leaveObj = objIter->second;
	GetRangeSet(leaveObj, _leaveSet);
	Update(leaveObj);

	_objects.erase(id);
	_xList.erase(leaveObj->_xIter);
	_yList.erase(leaveObj->_yIter);
	delete leaveObj;
}

void SceneMgr::Moving(int id, int newX, int newY)
{
	map<int, Object*>::iterator objIter = _objects.find(id);
	if(objIter == _objects.end())
		return;

	Object *moveOjb = objIter->second;
	map<int, Object*> oldSet, newSet;
	GetRangeSet(moveOjb, oldSet);

	//set new position for the object
	UpdateNewPosition(moveOjb, newX, newY);

	GetRangeSet(moveOjb, newSet);

	//move set
	for(map<int, Object*>::iterator iter = oldSet.begin(); iter != oldSet.end(); ++iter)
	{
		if(newSet.find(iter->first) != newSet.end())
		{
			_movingSet[iter->first] = iter->second;
		}
	}

	//leave set
	for(map<int, Object*>::iterator iter = oldSet.begin(); iter != oldSet.end(); ++iter)
	{
		if(_movingSet.find(iter->first) == _movingSet.end())
		{
			_leaveSet[iter->first] = iter->second;
		}
	}

	//enter set
	for(map<int, Object*>::iterator iter = newSet.begin(); iter != newSet.end(); ++iter)
	{
		if(_movingSet.find(iter->first) != _movingSet.end())
		{
			_movingSet[iter->first] = iter->second;
		}
	}

	Update(moveOjb);
}

void SceneMgr::Update(Object *obj)
{
	for(map<int, Object*>::iterator iter = _enterSet.begin(); iter != _enterSet.end(); ++iter)
	{
		printf("new object[%d, (%d, %d)] enter to [%d, (%d, %d)]\n", obj->_id, obj->_x, obj->_y, 
			(iter->second)->_id, (iter->second)->_x, (iter->second)->_y);

		printf("new object[%d, (%d, %d)] enter to [%d, (%d, %d)]\n", (iter->second)->_id, (iter->second)->_x, (iter->second)->_y,
			obj->_id, obj->_x, obj->_y);
	}

	for(map<int, Object*>::iterator iter = _leaveSet.begin(); iter != _leaveSet.end(); ++iter)
	{
		printf("notify [%d, (%d, %d) object[%d, (%d, %d) has left\n",  (iter->second)->_id, (iter->second)->_x, (iter->second)->_y,
			obj->_id, obj->_x, obj->_y);
	}

	for(map<int, Object*>::iterator iter = _movingSet.begin(); iter != _movingSet.end(); ++iter)
	{
		printf("notify [%d, (%d, %d) object[%d, (%d, %d) is moving\n",  (iter->second)->_id, (iter->second)->_x, (iter->second)->_y,
			obj->_id, obj->_x, obj->_y);
	}

	_enterSet.clear();
	_leaveSet.clear();
	_movingSet.clear();
}

void SceneMgr::UpdateNewPosition(Object *obj, int x, int y)
{
	int oldX = obj->_x;
	int oldY = obj->_y;

	obj->_x = x;
	obj->_y = y;

	//x-axis
	list<Object*>::iterator pos, iter;
	if(oldX > x)
	{
		if(obj->_xIter != _xList.begin())
		{
			pos = _xList.begin();
			iter = obj->_xIter;
			--iter;
			_xList.erase(obj->_xIter);
			while(iter != _xList.begin())
			{
				if((*iter)->_x - x < 0)
				{
					pos = ++iter;
					break;
				}

				--iter;
			}

			obj->_xIter = _xList.insert(pos, obj);
		}
	}
	else if(oldX < x)
	{
		if(obj->_xIter != _xList.end())
		{
			pos = _xList.end();
			iter = obj->_xIter;
			++iter;
			_xList.erase(obj->_xIter);
			while(iter != _xList.end())
			{
				if(x - (*iter)->_x < 0)
				{
					pos = iter;
					break;
				}

				++iter;
			}

			obj->_xIter = _xList.insert(pos, obj);
		}
	}

	//y-axis
	if(oldY > y)
	{
		if(obj->_yIter != _yList.begin())
		{
			pos = _yList.begin();
			iter = obj->_yIter;
			--iter;
			_yList.erase(obj->_yIter);
			while(iter != _yList.begin())
			{
				if((*iter)->_y - y < 0)
				{
					pos = ++iter;
					break;
				}

				--iter;
			}

			obj->_yIter = _yList.insert(pos, obj);
		}
	}
	else if(oldY < y)
	{
		if(obj->_yIter != _yList.end())
		{
			pos = _yList.end();
			iter = obj->_yIter;
			++iter;
			_yList.erase(obj->_yIter);
			while(iter != _yList.end())
			{
				if(y - (*iter)->_y < 0)
				{
					pos = iter;
					break;
				}

				++iter;
			}

			obj->_yIter = _yList.insert(pos, obj);
		}
	}


// 	//iterator is invalid
// 	list<Object*>::iterator newXIter = obj->_xIter;
// 	if(oldX > x)		//left
// 	{
// 		while(newXIter != _xList.begin())
// 		{
// 			int distDiff = (*--newXIter)->_x - x;
// 			if(distDiff < 0)
// 				break;
// 		}
// 
// 		_xList.erase(obj->_xIter);
// 		obj->_xIter = _xList.insert(newXIter, obj);
// 	}
// 	else if(oldX < x)	//right
// 	{
// 		while(++newXIter != _xList.end())
// 		{
// 			int distDiff = x - (*newXIter)->_x;
// 			if(distDiff < 0)
// 				break;
// 		}
// 		_xList.erase(obj->_xIter);
// 		obj->_xIter = _xList.insert(--newXIter, obj);
// 	}
// 
// 	//find the new y-axis position
// 	list<Object*>::iterator newYIter = obj->_yIter;
// 	if(oldY > y)		//left
// 	{
// 		while(newYIter != _yList.begin())
// 		{
// 			int distDiff = (*--newYIter)->_y - y;
// 			if(distDiff < 0)
// 				break;
// 		}
// 
// 		_yList.erase(obj->_yIter);
// 		obj->_yIter = _yList.insert(newYIter, obj);
// 	}
// 	else if(oldY < y)	//right
// 	{
// 		while(++newYIter != _yList.end())
// 		{
// 			int distDiff = y - (*newYIter)->_y;
// 			if(distDiff < 0)
// 				break;
// 		}
// 		_yList.erase(obj->_yIter);
// 		obj->_yIter = _yList.insert(--newYIter, obj);
// 	}
}

void SceneMgr::GetRangeSet(Object *obj, map<int, Object*> &setRet)
{
	map<int, Object*> xSet;
	list<Object*>::iterator xIter = obj->_xIter;
	while(++xIter != _xList.end())
	{
		int distDiff = (*xIter)->_x - obj->_x;
		if(distDiff > obj->_radius)
			break;

		xSet[(*xIter)->_id] = *xIter;
	}

	xIter = obj->_xIter;
	while(xIter != _xList.begin())
	{
		int distDiff =  obj->_x - (*--xIter)->_x;
		if(distDiff > obj->_radius)
			break;

		xSet[(*xIter)->_id] = *xIter;
	}

	list<Object*>::iterator yIter = obj->_yIter;
	while(++yIter != _yList.end())
	{
		int distDiff = (*yIter)->_y - obj->_y;
		if(distDiff > obj->_radius)
			break;

		if(xSet.find((*yIter)->_id) != xSet.end())
		{
			setRet[(*yIter)->_id] = *yIter;
		}
	}

	yIter = obj->_yIter;
	while(yIter != _yList.begin())
	{
		int distDiff = obj->_y - (*--yIter)->_y;
		if(distDiff > obj->_radius)
			break;

		if(xSet.find((*yIter)->_id) != xSet.end())
		{
			setRet[(*yIter)->_id] = *yIter;
		}
	}
}

void SceneMgr::printXList() const
{
	list<Object*>::const_iterator iter = _xList.begin();
	while(iter != _xList.end())
	{
		printf("[%d, (%d, %d)]\n", (*iter)->_id, (*iter)->_x, (*iter)->_y);
		++iter;
	}
}

void SceneMgr::printYList() const
{
	list<Object*>::const_iterator iter = _yList.begin();
	while(iter != _yList.end())
	{
		printf("[%d, (%d, %d)]\n", (*iter)->_id, (*iter)->_x, (*iter)->_y);
		++iter;
	}
}

