#include "pvz_base.h"

static pvz::Base& GetInstance() {
    return **(pvz::Base **)BASE_PTR_ADDRESS;
}
