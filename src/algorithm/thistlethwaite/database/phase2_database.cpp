#include "phase2_database.h"

uint32_t Phase2_database::id(const Cube_bg_model& cube) const
{
    using EPIECE  = Cube_bg_model::EPIECE;

    // stores the orientation of all corners (by position, regardless of which corner is where)
    std::array<uint8_t, 7> corner_orientation_perm = {
        cube.corner_orientation(cube.corner(EPIECE::ULB)),
        cube.corner_orientation(cube.corner(EPIECE::ULF)),
        cube.corner_orientation(cube.corner(EPIECE::DLF)),
        cube.corner_orientation(cube.corner(EPIECE::DLB)),
        cube.corner_orientation(cube.corner(EPIECE::URF)),
        cube.corner_orientation(cube.corner(EPIECE::URB)),
        cube.corner_orientation(cube.corner(EPIECE::DRB))
    };

    // stores the edges that are currently occupying each position
    std::array<uint8_t, 12> edge_perm = {
        cube.piece_index(EPIECE::UB),
        cube.piece_index(EPIECE::UF),
        cube.piece_index(EPIECE::DB),
        cube.piece_index(EPIECE::DF),
        cube.piece_index(EPIECE::UR),
        cube.piece_index(EPIECE::UL),
        cube.piece_index(EPIECE::DR),
        cube.piece_index(EPIECE::DL),
        cube.piece_index(EPIECE::RF),
        cube.piece_index(EPIECE::LF),
        cube.piece_index(EPIECE::RB),
        cube.piece_index(EPIECE::LB)
    };

    // stores the positions of the 4 edges that need to be brought back to the M-slice
    std::array<uint8_t, 4> edge_pos_comb;

    for (uint8_t i = 0, e = 0; i < 12 && e < 4; ++i) {
        // indices of the M-slice edges are 8, 9, 10, 11
        if (edge_perm[i] == 8  || edge_perm[i] == 9 ||
            edge_perm[i] == 10 || edge_perm[i] == 11)
            edge_pos_comb[e++] = i + 1;
    }

    uint32_t edge_index = combIndexer4.id(edge_pos_comb);   // edge
    uint32_t corner_index = 0;                              // corner

    // treats corner orientations as ternary numbers and converts it to decimal
    corner_index +=
        corner_orientation_perm[0] +
        corner_orientation_perm[1] * 3 +
        corner_orientation_perm[2] * 9 +
        corner_orientation_perm[3] * 27 +
        corner_orientation_perm[4] * 81 +
        corner_orientation_perm[5] * 243 +
        corner_orientation_perm[6] * 729;

    // (0..3^7 - 1) * 12C4 + (0..12C4 - 1) = 0..1082564
    return corner_index * 495 + edge_index;
}