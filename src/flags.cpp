#include "flags.hpp"

/// Usage:

FLAGS(PlayerState, active, idle, damaged, jumping);
FLAGS(Nt, boo);

int main ()
{
	using namespace PlayerState;

	State state = State();

	state.print();	
	state |= active;
	state.print();
	
	auto result = !idle;
	state |= result;
	state.print();
	
	auto another = damaged | !jumping;
	state |= another;
//	state |= Nt::boo;       //Error. (As expected)
	state.print();

	auto tripple = jumping | !active | active;
	state |= tripple;
	state.print();

	std::cout << ToString(state) << std::endl;

//	{
//		auto error = visible | !out_of_scope;
//		state |= error;
//		state.print();
//	}
//	{
//		auto error = Another::bad | MyFlags::active;
//		state |= error;
//		state.print();
//	}
	return 0;
}

