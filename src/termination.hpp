#ifndef AETAS_TERMINATION_HPP_
#define AETAS_TERMINATION_HPP_

#include <functional>
#include <vector>

namespace aetas {
bool null_termination(const double& fitness) { return false; }
bool maximize_termination(const double& fitness) { return (fitness >= 9.0); }
}  // namespace aetas

#endif  // AETAS_TERMINATION_HPP_
