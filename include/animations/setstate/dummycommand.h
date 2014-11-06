/*! \file animations/setstate/dummycommand.h
	\author HiddenSeeker

	Defines a dummy command, which does nothing, when invoked
 */
#include "typedcommand.h"

namespace sad
{

namespace animations
{

namespace setstate
{

/*! A command, which does nothing, when invoked
 */
template<
	typename T
>
class DummyCommmand: public sad::animations::setstate::TypedCommmand<T>
{
public:
	/*! Invokes a command with specified command
		\param[in] a argument
	 */
	virtual void call(const T& a)
	{
		
	}
	/*! Can be inherited
	 */
	virtual ~DummyCommmand()
	{
		
	}
};

};

}

}
