#include "Convar.h"

namespace qk
{
	Convar* ConvarRegistry::operator[](const char* key)
	{
		// find the key
		return m_Convars[entt::hashed_string(key).value()];

	}

	Convar* ConvarRegistry::operator[](const std::string& key)
	{
		return m_Convars[entt::hashed_string(key.c_str()).value()];
	}





	size_t ConvarRegistry::size() {
		// some test code



		return m_Convars.size();

		
	}



	#ifdef _DEBUG
	const char* Convar::type() const
	{
		return m_Type.name().data();
	}
	const entt::id_type Convar::type_id() const
	{
		return m_Type.index();
	}
	const char* Convar::name() const { return m_Name; }

	const size_t Convar::name_size() const
	{
		return m_NameSize;
	}
	#endif



	QK_API ConvarRegistry convars;

}

namespace cl
{
	QK_API float fov_desired = 50.0f;
}

QK_DEFINE_CONVAR(fov_desired, "fov_desired", cl::fov_desired);