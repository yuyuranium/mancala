#include "strategy.h"

strategy_t get_strategy_by_name(const char *name)
{
    for (size_t i = 0; i < num_strategies; ++i) {
        if (strcmp(name, strategy_names[i]) == 0) {
            return *strategies[i];
        }
    }
    return NULL;
}
