#include "components.hpp"
#include "entt_overview.hpp"

#include <iostream>
#include <cstdint>

namespace sample {

#ifndef _WINDOWS
    void CallbackManager::velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
        std::cout << " c_Velocity created! - instance" << std::endl;
    };
#endif

    void s_update(entt::DefaultRegistry &registry) {
        // create view fo the register -- c_Position & c_Velocity are all of the components
        //      cannot be reduced -- all used components in the register as the template parameters
        auto view = registry.view<c_Position, c_Velocity>();

        // iterate over the view -> enitity after entity
        for (auto entity : view) {

            // get component `velocity` instance from created view
            auto &velocity = view.get<c_Velocity>(entity);

            velocity.dx *= 1.f;
            velocity.dy *= 1.f;

            std::tuple<c_Position&, c_Velocity&> elem = view.get<c_Position, c_Velocity>(entity);
            std::get<1>(elem).dx *= 1.f;
            std::get<1>(elem).dy *= 1.f;
        }
    }

    void s_update(std::uint64_t dt, entt::DefaultRegistry &registry) {
        // gets all the components of the view at once using `each` -- format: entity, COMP_1, (...), COMP_n
        //      cannot be reduced -- all used components in the register as the template parameters
        registry.view<c_Position, c_Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
            position.x += velocity.dx * dt;
            position.y += velocity.dy * dt;

        });

    }

    void s_printout_position(entt::DefaultRegistry &registry) {
        // TODO: it would be nice to have a logger able to print all the entity data and components to some kind of JSON format
        registry.view<c_Position>().each([](const auto& entity, const auto& position) {
            std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
                    << " } }" << std::endl;
        });
    }

    void s_printout_has_velocity(entt::DefaultRegistry &registry) {
        registry.view<c_Position, c_Velocity>().each([](const auto& entity, const auto& position, const auto& velocity) {
            std::cout << "{ entity: " << entity << ": position: { x: " << position.x << ", y: " << position.y
                    << " }, velocity: { dx: " << velocity.dx <<  ", dy: " << velocity.dy << " } }" << std::endl;
        });
    }

#ifndef _WINDOWS
    void velocity_create_callback(entt::DefaultRegistry &registry, entt::DefaultRegistry::entity_type entity) {
        std::cout << "c_Velocity created! - function" << std::endl;
    }
#endif

    void s_remove_velocity(entt::DefaultRegistry &registry) {
        auto view = registry.view<c_Velocity>();
        for (auto entity : view) {
            // remove `velocity` component form entity
            registry.remove<c_Velocity>(entity);
        }
    }

    void s_iterate_over_each(entt::DefaultRegistry &registry) {
        registry.each([&registry](auto entity) {

            // check if entity has component `c_Velocity` and replace with new one, if entity doesn't have it add new
            if(registry.has<c_Velocity>(entity)) {
                auto e = registry.replace<c_Velocity>(entity, 1., 1.);
                (void)e;
            } else {
                auto e = registry.assign<c_Velocity>(entity, 1., 1.);
                (void)e;
            }

#ifndef _WINDOWS
            // the same functionality can be done using accomadate
            // a) pass args to the call
            registry.accommodate<c_Velocity>(entity, 1., 1.);

            // b) make c_Velocity instance ant modify atributes later
            c_Velocity &velocity = registry.accommodate<c_Velocity>(entity);
            velocity.dx = 1.;
            velocity.dy = 1.;
#endif
        });
    }

#ifndef _WINDOWS
    void s_iterate_orphans(entt::DefaultRegistry &registry) {
        registry.orphans([](auto entity) {
            std::cout << "orphan: " << entity << std::endl;
        });
    }

    void s_iterate_using_persistant_view(entt::DefaultRegistry &registry) {
        // view should be saved somehow -- `persistent` means that the view container is prepared and created only once,
        // so it can increase performance if iterating over static entity sets
        auto view = registry.view<c_Position, c_Velocity>(entt::persistent_t{});
        for (auto entity : view) {
            (void)entity;
        }
    }

    void s_iterate_using_raw_view(entt::DefaultRegistry &registry) {
        auto raw = registry.view<c_Position>(entt::raw_t{});
        for (auto && component : raw) {
            (void)component;
        }
    }
#endif
}

// NOTE: Only core `entt` features works on WINDOWS!
// TODO:
// serialize -- can be used to save game state (game dump)
// identifires
// resource manager & scheduler-process
// signals delegate & event dispatcher
