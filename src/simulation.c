#include "simulation.h"
#include "circle_verlet.h"
#include "error_handler.h"

vector gravity = {.x = 0, .y = 1000};


void apply_gravity(simulation *sim){
    for (size_t i = 0; i < sim->circle_count; i++)
    {
        accelerate_circle(sim->circles + i, &gravity);
    }
}

void update_positions(simulation *sim, float dt){
    for (size_t i = 0; i < sim->circle_count; i++)
    {
        update_position_circle(sim->circles + i, dt);
    }
}


void update_simulation(simulation *sim, float dt){
    apply_gravity(sim);
    update_positions(sim, dt);
}

simulation *init_simulation(void){
    simulation *s = malloc(sizeof(simulation));
    _check_malloc(s, __LINE__, __FILE__);
    s->circle_count = 0;
    s->circles = malloc(sizeof(verlet_circle));
    _check_malloc(s->circles, __LINE__, __FILE__);
    s->allocated_circles = 1;

    return s;
}

void destroy_simulation(simulation *s){
    if (!s) return;
    if (s->circles) free(s->circles);
    free(s);
}

void add_circle(simulation *sim, uint radius, float px, float py, unsigned char red, unsigned char green, unsigned char blue, float acc_x, float acc_y){
    verlet_circle new_circle = {
        .radius = radius,
        .position_old.x = px,
        .position_old.y = py,
        .position_current.x = px,
        .position_current.y = py,
        .acceleration.x = acc_x,
        .acceleration.y = acc_y,
        .r = red,
        .g = green,
        .b = blue
    };
    sim->circles[sim->circle_count] = new_circle;

    sim->circle_count += 1;

    if(sim->circle_count == sim->allocated_circles){
        sim->circles = realloc(sim->circles, (sizeof(verlet_circle) * sim->allocated_circles * 2));
        _check_malloc(sim->circles, __LINE__, __FILE__);

        sim->allocated_circles *= 2;
    }

}