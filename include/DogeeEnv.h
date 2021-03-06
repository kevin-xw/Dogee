#ifndef __DOGEE_ENV_H_ 
#define __DOGEE_ENV_H_ 

#include "Dogee.h"
#include <vector>
#include <string>

namespace Dogee
{
	class SoStorage;
	class DSMCache;
	enum BackendType
	{
		SoBackendTest,
		SoBackendChunkMemcached,
		SoBackendMemcached,
	};
	enum CacheType
	{
		SoNoCache,
		SoWriteThroughCache,
	};
	extern THREAD_LOCAL int current_thread_id;
	extern int AllocThreadId();
	extern void RcPrepareNewThread();
	class DogeeEnv
	{
	private:
		static bool _isMaster;
	public:
		static SoStorage* backend;
		static DSMCache* cache;
		static int self_node_id;
		static int num_nodes;
		typedef void(*InitStorageCurrentThreadProc)();
		static InitStorageCurrentThreadProc InitStorageCurrentThread;


		static void InitCurrentThread()
		{
			if (current_thread_id == 0)
			{
				current_thread_id = AllocThreadId();
				RcPrepareNewThread();
				InitStorageCurrentThread();
			}

		}

		static bool isMaster()
		{
			return _isMaster;
		}
		static void SetIsMaster(bool is_master)
		{
			_isMaster=is_master;
		}
		static void InitStorage(BackendType backty, CacheType cachety, std::vector<std::string>& hosts, std::vector<int>& ports,
			std::vector<std::string>& mem_hosts, std::vector<int>& mem_ports, int node_id);
		static void CloseStorage();
	};
}

#endif 