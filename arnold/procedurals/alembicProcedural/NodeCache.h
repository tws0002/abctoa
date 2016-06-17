#ifndef _nodeCache_h_
#define _nodeCache_h_

#include <ai.h>
#include <string>
#include <map>
#include <vector>

#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreFactory/All.h>

#include "json/value.h"


using namespace Alembic::AbcGeom;

/* 
This class is handling the caching of Arnold node
*/

class AtScopedLock{
public:
	AtScopedLock(AtCritSec cs) : m_critSec(cs) { AiCritSecEnter(&m_critSec); }
	~AtScopedLock()	{ AiCritSecLeave(&m_critSec); }
private:
	AtCritSec m_critSec;
};

class NodeCache
{
public:
	NodeCache(AtCritSec mycs);
	~NodeCache();

	AtNode* getCachedNode(const std::string& cacheId);
	void addNode(const std::string& cacheId, AtNode* node);


private:
	std::map<std::string, std::string> ArnoldNodeCache;
	AtCritSec lock;
};


class NodeCollector
{
public:
	NodeCollector(AtCritSec mycs, AtNode *proc);
	~NodeCollector();

	void addNode(AtNode* node);
	size_t getNumNodes();
	AtNode* getNode(int num);
	AtNode* getProcedural() { return proc ;};
	


private:
	std::vector<AtNode*> ArnoldNodeCollector;
	AtNode *proc;
	AtCritSec lock;
};


struct CachedNodeFile
{
	AtNode *node;
	AtArray *matrix;
};

class FileCache
{
public:
	FileCache(AtCritSec mycs);
	~FileCache();

	const std::vector<CachedNodeFile>& getCachedFile(const std::string& cacheId);
	void addCache(const std::string& cacheId, NodeCollector* createdNodes);

	const size_t hash(std::string const& s);

	std::string getHash(const std::string& fileName,     
						const std::map<std::string, AtNode*>& shaders,
						const std::map<std::string, AtNode*>& displacements,
						const Json::Value& attributesRoot,
						double frame
						);


private:
	std::map<std::string, std::vector<CachedNodeFile>* > ArnoldFileCache;
	std::map<std::string, AtNode* > ArnoldFileCacheProc; // This is used to check if the procedural creating the cache still exists. If not, chances are that the whole cache is not valid.
	AtCritSec lock;
};

#endif