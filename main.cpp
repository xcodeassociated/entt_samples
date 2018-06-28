#include "overview/components.hpp"
#include "overview/entt_overview.hpp"
#include <entt/entt.hpp>
#include <iostream>
#include <cstdint>

using namespace sample;

void entt_overview() {
        // create default registry for the ECS
        entt::DefaultRegistry registry;

#ifndef _WINDOWS
        // add component dependencies -- add c_Velocity when c_Position is assiged to the entity
        entt::dependency<c_Velocity>(registry.construction<c_Position>());

        // remove component dependencies
        entt::dependency<c_Velocity>(entt::break_t{}, registry.construction<c_Position>());

        // register callback for `c_Velocity` component - if the component is created the callback function will be triggered
        registry.construction<c_Velocity>().connect<&velocity_create_callback>();

        // register callback member function form callback manager
        CallbackManager callbackManager;
        registry.construction<c_Velocity>().connect<CallbackManager, &CallbackManager::velocity_create_callback>(
                &callbackManager);

        // dissconnect `c_Velocity` create callback function (uncomment)
        registry.construction<c_Velocity>().disconnect<&velocity_create_callback>();
#endif

        //some value to used by system
        std::uint64_t dt = 1;

        for (auto i = 0; i < 10; ++i) {
            // create entity
            auto entity = registry.create();

            // assigne component
            registry.assign<c_Position>(entity, i * 1.f, i * 1.f);

            // assigne `velocity component` to the even enities
            if (i % 2 == 0) {
                if (!registry.has<c_Velocity>(entity)) {
                    auto v = registry.assign<c_Velocity>(entity, i * 1.f, i * 1.f);

                    // let's check replace the `velocity` on the same one
                    auto v_r = registry.replace<c_Velocity>(entity, i * 1.f, i * 1.f);
                }
            }
        }

        // assigne one more enitity -- without any component - orphans to iterate
        auto empty_entity = registry.create();
        (void) empty_entity;

        // sort the entities by pos.x -- note: this will be seen only when iterating over the view with `Postion` only,
        //      entities that has also velocity will not be affected
        registry.sort<c_Position>([](const auto &lhs, const auto &rhs) {
            return lhs.x < rhs.y;
        });

        // sort the entities with `velocity` as well. if the above sort will not be present only view that has c_Velocity will be sorted.
        //      the view with `c_Position` only will not be sorted.
        registry.sort<c_Velocity>([](const auto &lhs, const auto &rhs) {
            return lhs.dx < rhs.dx;
        });

        // invoke system update with given param -- first iterate over `velocity` and update the components
        s_update(dt, registry);

        // invoke system update no params -- scond iterate over `velocity` and `position` to update position using velocity
        s_update(registry);

        // print out system -- all enities - all have `position`
        s_printout_position(registry);

        std::cout << std::endl;

        // print out system -- entities that has `velocity` - even
        s_printout_has_velocity(registry);


        s_remove_velocity(registry);
        s_remove_velocity(registry); // can be called many times - this time there is no `velocity` so the view is empty


        std::cout << std::endl;

        // print out system -- entities that has `velocity` - even, but now the component is removed, so no entity will be printed
        s_printout_has_velocity(registry);


        // other way for iterating over the entities in the registry
        s_iterate_over_each(registry);

#ifndef _WINDOWS
        // iterate over `orphans1 in registry -- entities that have no assigned components
        s_iterate_orphans(registry);

        // iterate over entities in the registry using persistent view
        s_iterate_using_persistant_view(registry);

        // iterate over the entities using raw view
        s_iterate_using_raw_view(registry);
#endif

}

int main(int argc, char * argv[]) {
    (void) argc;
    (void) argv;

    ::entt_overview();

    return 0;
}
