#include "headers.hpp"

void Weapon::act(Player* player)
{
    if (Game::offProjectiles.empty())
        return;

    Game::onProjectiles.push_back(Game::offProjectiles.back());
    Game::offProjectiles.pop_back();
    Game::onProjectiles.back()->init(potato_swap,
                                     player->nickname,
                                     player->x,
                                     player->y,
                                     player->rotation,
                                     player_damage,
                                     unit_range,
                                     projectile_speed,
                                     projectile_falloff,
                                     headshot_multiplier,
                                     obstacle_multiplier,
                                     action);
}
