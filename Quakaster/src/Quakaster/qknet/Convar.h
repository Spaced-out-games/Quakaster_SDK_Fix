#pragma once
#include "../Core.h"
#include <entt/entt.hpp>
#include <sstream>
#include "../qklog/logging.h"
#include <enet/enet.h>
namespace qk
{

	struct QK_API Convar;



	/// <summary>
	/// Holds a collection of convars. Good for globally scoped console variables
	/// </summary>
	class QK_API ConvarRegistry
	{
		friend class Convar;
		// hidden from public view. But for now, public:
	public:
		std::unordered_map<entt::id_type, Convar*> m_Convars;
        Convar& operator[](entt::id_type hash);

		public:
			Convar* operator[](const char* key);
            Convar* operator[](const std::string& key);
            size_t size();
	};


    // A default convar list to work with. Might make it a static pointer you assign. Or not. IDK.
	extern QK_API ConvarRegistry convars;





    struct QK_API Convar
    {
        void* const m_Data;
        const entt::type_info& m_Type;
        #ifdef _DEBUG
            const char* m_Name;
            const size_t m_NameSize;
        #endif

        template <typename T>
        Convar(const char* key, T& object):
            m_Data(&object),
            m_Type(entt::type_id<T>()),
            #ifdef _DEBUG
            m_Name(entt::hashed_string{ key }.data()),
                m_NameSize(entt::hashed_string{ key }.size())
            #endif
        {
//            convars[]
           convars.m_Convars[entt::hashed_string{ key }.value()] = this;
        }

        #ifdef _DEBUG
            // Gets the convar's typename
            const char* name() const;
            const char* type() const;
            const size_t name_size() const;
            const entt::id_type type_id() const;
        #endif


        template <typename T>
        T* try_get() {
            const auto& T_typeinfo = entt::type_id<T>();
            if (m_Type == T_typeinfo && m_Data) {
                return static_cast<T*>(m_Data);
            }
            else {
                return nullptr;
            }
        }

        template <typename T>
        T& get() {
            const auto& T_typeinfo = entt::type_id<T>();
            if (m_Type == T_typeinfo && m_Data) {
                return *static_cast<T*>(m_Data);
            }
            else {
                __debugbreak();
                std::terminate();
            }
        }

        template <typename T>
        bool set(const T& item)
        {
            const auto& T_typeinfo = entt::type_id<T>();
            if (m_Type == T_typeinfo && m_Data)
            {
                *(T*)m_Data = item;
                return true;
            }
            // don't need an if since it's safe to not set.
            return false;
        }
    };

}

/*
namespace cl
{
	extern QK_API float fov_desired;
}

QK_DECLARE_CONVAR(fov_desired);
*/