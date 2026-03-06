#pragma once
#include "../core.h"
#include <stdint.h>

namespace gfx {
	
	struct FSSBOAccessMode {
		union {
			struct {
				uint8_t readable : 1;
				uint8_t writable : 1;
				uint8_t read_locked : 1;
				uint8_t write_locked : 1;
				uint8_t reserved : 4;  // fill the byte
			};
			uint8_t value;
		};
	};


	class SSBO_impl {
		protected:
			size_t m_Size = 0;
			size_t m_Capacity = 0;
			void*  m_Data = nullptr;
			unsigned int m_Handle = 0;
			FSSBOAccessMode m_Mode = ESSBOAccessMode::None;
			
			
			void push_back_impl(size_t elem_size, const void* data);
			void upload_impl(const void* data, size_t size_bytes, unsigned int usage);
			void reserve_impl(size_t new_capacity, size_t elem_size);
			void* read_impl();
			void* write_impl();
			bool bind_impl();

			// |='s the mode, but respecting read and write locks. Returns true if actually changed
			bool set_mode(FSSBOAccessMode mode);

		public:
			void size();
			void capacity();
			static void unbind();
			void destroy();
			void lock(ESSBOAccessMode mode);
			void unlock(ESSBOAccessMode mode);

	};

}