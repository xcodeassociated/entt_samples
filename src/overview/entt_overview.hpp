#pragma once
#include <entt/entt.hpp>
 
namespace sample{
#ifndef _WINDOWS
    // callback manager class for `c_Velocity` component
    struct CallbackManager {
        void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity);
    };
#endif

    void s_update(entt::DefaultRegistry &registry);
    void s_update(std::uint64_t dt, entt::DefaultRegistry &registry);
    void s_printout_position(entt::DefaultRegistry &registry);
    void s_printout_has_velocity(entt::DefaultRegistry &registry);
#ifndef _WINDOWS
    void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity);
    void s_iterate_orphans(entt::DefaultRegistry &registry);
    void s_iterate_using_persistant_view(entt::DefaultRegistry &registry);
    void s_iterate_using_raw_view(entt::DefaultRegistry &registry);
#endif
    void s_remove_velocity(entt::DefaultRegistry &registry);
    void s_iterate_over_each(entt::DefaultRegistry &registry);
}
