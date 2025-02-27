#pragma once

#include "phase_info.h"
#include "../utilities/rankers.h"

struct Phase4_info : public Phase_info
{
	Phase4_info()
    {
        // G3: forbid all 90-degree turns
        allowed_moves = {
            emove::U2,
            emove::L2,
            emove::F2,
            emove::R2,
            emove::B2,
            emove::D2
        };
    }

    uint32_t id(const Cube_bg_model& cube) const override;

	// G3 -> G4 is solved only when the cube is solved
	bool solved(const Cube_bg_model& cube) const override;

private:
    PermRanker<4>           perm_ranker4;
    PermRankerPartial<4, 2> perm_ranker4p2;
};