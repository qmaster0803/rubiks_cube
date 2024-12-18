#pragma once

#include <string>
#include <iostream>
#include <array>

#include "../database/database.h"
#include "../Goals/goal.h"

#include "thistlethwaite/utilities/timer.h"
#include "thistlethwaite/utilities/searchutil.h"

/* 
 * Searches the cube (IDDFS) for all possible states and stores the depth of each state in a file
 */
class DB_generator {
public:
    // if a cube isn't passed the database will be generated using a solved cube
    void generate(const Goal& goal, Database& database) const;

private:
    bool _db_searcher(Cube_bg_model cube, Cube_bg_model::EMOVE last_move,
                      const Goal& goal, Database& database,
                      uint8_t depth, uint8_t max_depth,
                      std::vector<bool>& visited) const;
};