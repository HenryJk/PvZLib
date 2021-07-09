#include "pvz_base.h"

pvz::Base& pvz::Base::GetInstance() {
    return **(pvz::Base **)BASE_PTR_ADDRESS;
}
