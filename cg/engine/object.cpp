//////////////
// #INCLUDE //
//////////////


	// Object header file include
	#include "object.h"

	unsigned int ENG_API Object::m_helper_id = 0;


	ENG_API Object::Object(const std::string& name) :
		m_id{ ++m_helper_id },
		m_name{ name }
	{ 
		//Empty contructor
	}

	ENG_API Object::~Object()
	{
		//Empty decostructor: no external resources
	}

	void ENG_API Object::set_object_name(const std::string& name)
	{
		m_name = name;
	}

	const ENG_API std::string Object::get_object_name() {
		return m_name;
	}

	const ENG_API unsigned int Object::get_object_id()
	{
		return m_id;
	}