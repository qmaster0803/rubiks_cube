#include "phase4_database.h"

uint32_t Phase4_database::id(const Cube_bg_model& cube) const
{
    // stores which edge is currently occupying each position in it's slice
    
    // E-slice
    std::array<uint8_t, 4> E_posPermE = {
        cube.piece_index(epiece::LF),
        cube.piece_index(epiece::LB),
        cube.piece_index(epiece::RF),
        cube.piece_index(epiece::RB),
    };
    // M-slice
    std::array<uint8_t, 4> E_posPermM = {
        cube.piece_index(epiece::UF),
        cube.piece_index(epiece::DF),
        cube.piece_index(epiece::DB),
        cube.piece_index(epiece::UB),
    };
    // S-slice
    // only half the pieces in the S-slice are stored, the positions of the first 10
    // edges dictate the positions of the last 2 (they have to have even parity)
    std::array<uint8_t, 2> E_posPermS = {
        cube.piece_index(epiece::UL),
        cube.piece_index(epiece::DL),
    };

    // stores which corner is currently occupying which position in it's tetrad
    std::array<uint8_t, 4> C_tetradPosPerm = {
        cube.piece_index(epiece::ULB),
        cube.piece_index(epiece::DLF),
        cube.piece_index(epiece::DRB),
        cube.piece_index(epiece::URF),
    };

    // sets the indices of all edge and corner pieces to a value between 0 and 3
    for (auto& c : C_tetradPosPerm) c >>= 1;
    for (auto& e : E_posPermE) e &= 3;
    for (auto& e : E_posPermM) e &= 3;
    // indices of the S-slice edges are 0..3 by default

    // for every permutation of the first tetrad the second tetrad will start 
    // with either 0/1/2/3 which dictates the "rank" of the permutation
    uint8_t C_tetradRank = cube.piece_index(epiece::ULF);
    uint8_t E_sliceRankS = perm_indexer4p2.index(E_posPermS);

    // (0..4! - 1) * 4 + 0..3 = 0..96
    uint32_t C_ind = perm_indexer4.index(C_tetradPosPerm) * 4 + (C_tetradRank >> 1);
    // (0..4! - 1) * (4!^2 / 2) + (0..4! - 1) * (4! / 2) + (0..4! / 2) = 0..6911
    uint32_t E_ind = perm_indexer4.index(E_posPermM) * 288 + perm_indexer4.index(E_posPermE) * 12 + E_sliceRankS;
    // 0..9611 * 96 + 0..95 = 0..663551
    return E_ind * 96 + C_ind;
}
