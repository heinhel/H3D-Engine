#pragma once
#include "base_alloc.hpp"
/////////////////////////////////////////////////////////////////
// Pool Allocator
/////////////////////////////////////////////////////////////////
namespace h3d{
	class pool_allocator : public base_alloc
	{
	private:
		pool_allocator(const pool_allocator&) = delete;
	public:
		inline pool_allocator();
		inline ~pool_allocator();
	};
}
/////////////////////////////////////////////////////////////////