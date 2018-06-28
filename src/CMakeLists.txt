## entt_overview lib 

set(entt_overview_sources 
    overview/entt_overview.cpp
    overview/components.cpp)

add_library(entt_overview ${entt_overview_sources})

set(entt_scene_graph_sources
    scene_graph/scene_graph.cpp)

add_library(entt_scene_graph ${entt_scene_graph_sources})
