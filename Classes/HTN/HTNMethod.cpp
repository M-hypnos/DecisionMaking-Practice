#include "HTNMethod.h"

HTNMethod::HTNMethod(string name,shared_ptr<HTNPrecondition> precondition)
: _name(name)
,_precondition(precondition)
{}

bool HTNMethod::checkPrecondition(const unique_ptr<HTNWorldState>& worldState) {
	if (_precondition) {
		return _precondition->check(worldState);
	}
	return true;
}