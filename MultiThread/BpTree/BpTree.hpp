//
// Created by DUAN Yuxuan & YAN Ge on 2018.5.15.
//

#ifndef DATABASECODE_BPTREE_HPP
#define DATABASECODE_BPTREE_HPP

#include "bpt.h"
#include <cstring>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <utility>

typedef int key_type;
typedef value_t value_type;

class BpTree
{
private:
	bpt::bplus_tree *tree;
	mutable std::shared_mutex treeMutex;
	std::map<key_type, std::unique_ptr<std::shared_mutex>> mutexMap;
	
	bool haveMutex;
	
public:
	BpTree(const char* filename, bool setMutex)
	{
		tree = new bpt::bplus_tree(filename);
		haveMutex = setMutex;
		if(haveMutex)
			mutexMap.clear();
	}
	
	bool find(const key_type & key)
	{
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			return true;
		else
			return false;
	}
	
	value_type get(const key_type & key)
	{
		if(haveMutex)
			std::shared_lock<std::shared_mutex> lock(*mutexMap[key]);
		
		value_type *p = new value_type("");
		int temp = tree->search(key, p);
		if(temp != 0)
			return value_type("");
		else
		{
			return (*p);
		}
	}
	
	bool insert(const key_type & key, const value_type & value)
	{
		if(haveMutex)
		{
			std::unique_lock<std::shared_mutex> bigLock(treeMutex);
			
			std::shared_mutex *mtx = new std::shared_mutex;
			
			mutexMap.emplace(key, mtx);
			std::unique_lock<std::shared_mutex> lock(*mtx);
		}
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			tree->update(key, value);
		else
			tree->insert(key, value);
		return 1;
	}
	
	bool update(const key_type & key, const value_type & value)
	{
		if(haveMutex)
			std::unique_lock<std::shared_mutex> lock(*mutexMap[key]);
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
			tree->update(key, value);
		else
			tree->insert(key, value);
		return 1;
	}
	
	bool erase(const key_type & key)
	{
		if(haveMutex)
		{
			std::unique_lock<std::shared_mutex> bigLock(treeMutex);
			std::unique_lock<std::shared_mutex> lock(*mutexMap[key]);
		}
		
		value_type *p = new value_type("");
		int rtn = tree->search(key, p);
		if(rtn == 0)
		{
			tree->remove(key);
			mutexMap.erase(key);
			return true;
		}
		else
			return false;
	}
	
	~BpTree()
	{
		if(tree)
			delete tree;
	}
};


#endif //DATABASECODE_BPTREE_HPP
