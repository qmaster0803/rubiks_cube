#include "cube_bg_model.h"

Cube_bg_model::Cube_bg_model()
{
    reset();
}

bool Cube_bg_model::operator==(const Cube_bg_model& lhs)
{
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i) {
        if (_cube_data[i] != lhs._cube_data[i])
            return false;
    }

    return true;
}

Cube_bg_model& Cube_bg_model::operator=(const Cube_bg_model& lhs)
{
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i)
        _cube_data[i] = lhs._cube_data[i];
    
    return *this;
}

void Cube_bg_model::reset()
{
    for (std::size_t i = 0;  i < 1 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::W; }
    for (std::size_t i = 9;  i < 2 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::O; }
    for (std::size_t i = 18; i < 3 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::G; }
    for (std::size_t i = 27; i < 4 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::R; }
    for (std::size_t i = 36; i < 5 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::B; }
    for (std::size_t i = 45; i < 6 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ECOLOUR::Y; }
}

bool Cube_bg_model::solved() const
{
    Cube_bg_model solved_cube;
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i) {
        if (_cube_data[i] != solved_cube._cube_data[i])
            return false;
    }

    return true;
}

std::array<Cube_bg_model::ECOLOUR, COLORS_PER_SIDE> Cube_bg_model::get_side(rotation_side side)
{
    std::size_t first_i = static_cast<std::size_t>(side) * 9;

    std::array<ECOLOUR, COLORS_PER_SIDE> result;
    for (std::size_t i = 0; i < 9; ++i)
        result[i] = _cube_data[first_i + i];

    return result;
}

Cube_bg_model::ECOLOUR Cube_bg_model::operator[](unsigned index)
{
    if(index >= TOTAL_COLOR_CELLS)
        throw std::invalid_argument("Wrong index" + std::to_string(index));

    return _cube_data[index];
}

void Cube_bg_model::rotate(rotation_side side, rotation_type rot)
{
    int n = (rot == rotation_type::ROTATION_R) ? 1 : 3;
    for(int i = 0; i < n; i++) {
        // rotate selected side
        _rotate_side(side);

        // swap elements in the adjacent sides
        _rotate_adjacent(side);
    }
}

void Cube_bg_model::rotate(EMOVE move)
{
    switch (move) {
    // upper
    case EMOVE::U:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    case EMOVE::Up:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_L);
        break;
    case EMOVE::U2:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    
    // left
    case EMOVE::L:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    case EMOVE::Lp:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_L);
        break;
    case EMOVE::L2:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    
    // front
    case EMOVE::F:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    case EMOVE::Fp:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_L);
        break;
    case EMOVE::F2:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    
    // right
    case EMOVE::R:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    case EMOVE::Rp:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_L);
        break;
    case EMOVE::R2:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    
    // back
    case EMOVE::B:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    case EMOVE::Bp:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    case EMOVE::B2:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    
    // down
    case EMOVE::D:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    case EMOVE::Dp:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_L);
        break;
    case EMOVE::D2:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    
    case EMOVE::NO_MOVE:
        break;
    
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Cube_bg_modelCube::rotate Invalid enum value: " + value);
    }
}

void Cube_bg_model::revert_rotate(EMOVE move)
{
    // make inverse move to given
    switch (move) {
    // upper
    case EMOVE::U:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_L);
        break;
    case EMOVE::Up:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    case EMOVE::U2:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    
    // left
    case EMOVE::L:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_L);
        break;
    case EMOVE::Lp:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    case EMOVE::L2:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    
    // front
    case EMOVE::F:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_L);
        break;
    case EMOVE::Fp:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    case EMOVE::F2:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    
    // right
    case EMOVE::R:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_L);
        break;
    case EMOVE::Rp:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    case EMOVE::R2:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    
    // back
    case EMOVE::B:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    case EMOVE::Bp:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    case EMOVE::B2:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    
    // down
    case EMOVE::D:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_L);
        break;
    case EMOVE::Dp:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    case EMOVE::D2:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;

    case EMOVE::NO_MOVE:
        break;
    
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Cube_bg_modelCube::revert_rotate Invalid enum value: " + value);
    }
}

/*
 * Action of the function:
 * 0 1 2    cw    6 3 0
 * 3 4 5   ---->  7 4 1
 * 6 7 8          8 5 2
 *
 * Or in the array form:
 * {0, 1, 2, 3, 4, 5, 6, 7, 8}
 *              |
 * {6, 3, 0, 7, 4, 1, 8, 5, 2}
 */
void Cube_bg_model::_rotate_side(rotation_side side)
{
    std::size_t first_i = static_cast<std::size_t>(side) * 9;

    ECOLOUR new_side_data[9] = {
        _cube_data[first_i + 6],
        _cube_data[first_i + 3],
        _cube_data[first_i + 0],
        _cube_data[first_i + 7],
        _cube_data[first_i + 4],
        _cube_data[first_i + 1],
        _cube_data[first_i + 8],
        _cube_data[first_i + 5],
        _cube_data[first_i + 2]
    };

    // insert reodered data back into the _cube_data
    for (std::size_t i = 0; i < 9; ++i) {
        _cube_data[first_i + i] = new_side_data[i];
    }
}

/*
 * Action of the function:
 *          a0 a1 a2                           a0 a1 a2         
 *          a3 a4 a5                           a3 a4 a5         
 *          a6 a7 a8                           b8 b5 b2         
 *         ----------                         ----------        
 * b0 b1 b2|[] [] []|c0 c1 c2   cw    b0 b1 d0|[] [] []|a6 c1 c2
 * b3 b4 b5|[] [] []|c3 c4 c5  ---->  b3 b4 d1|[] [] []|a7 c4 c5
 * b6 b7 b8|[] [] []|c6 c7 c8         b6 b7 d2|[] [] []|a8 c7 c8
 *         ----------                         ----------        
 *          d0 d1 d2                           c6 c3 c0         
 *          d3 d4 d5                           d3 d4 d5         
 *          d6 d7 d8                           d6 d7 d8         
 */
 void Cube_bg_model::_rotate_adjacent(rotation_side side)
 {
     // a lot of swapping here...
     // (God pls trust me with the diagrams below...)
     ECOLOUR tmp1, tmp2, tmp3; // for swapping
     switch(side) {
         case rotation_side::SIDE_U:
             /* BEFORE:
              *    38 37 36
              *   ----------
              * 9 |[] [] []|29
              * 10|[] [] []|28
              * 11|[] [] []|27
              *   ----------
              *    18 19 20
              */
             tmp1 = _cube_data[38];
             tmp2 = _cube_data[37];
             tmp3 = _cube_data[36];
             // top
             _cube_data[38] = _cube_data[11];
             _cube_data[37] = _cube_data[10];
             _cube_data[36] = _cube_data[9 ];
             // left
             _cube_data[11] = _cube_data[20];
             _cube_data[10] = _cube_data[19];
             _cube_data[9 ] = _cube_data[18];
             // bottom
             _cube_data[20] = _cube_data[29];
             _cube_data[19] = _cube_data[28];
             _cube_data[18] = _cube_data[27];
             // right
             _cube_data[29] = tmp1;
             _cube_data[28] = tmp2;
             _cube_data[27] = tmp3;
             break;
         case rotation_side::SIDE_L:
             /* BEFORE:
              *    0  3  6
              *   ----------
              * 38|[] [] []|18
              * 41|[] [] []|21
              * 44|[] [] []|24
              *   ----------
              *    51 48 45
              */
             tmp1 = _cube_data[0];
             tmp2 = _cube_data[3];
             tmp3 = _cube_data[6];
             // top
             _cube_data[0] = _cube_data[44];
             _cube_data[3] = _cube_data[41];
             _cube_data[6] = _cube_data[38];
             // left
             _cube_data[44] = _cube_data[45];
             _cube_data[41] = _cube_data[48];
             _cube_data[38] = _cube_data[51];
             // bottom
             _cube_data[45] = _cube_data[18];
             _cube_data[48] = _cube_data[21];
             _cube_data[51] = _cube_data[24];
             // right
             _cube_data[18] = tmp1;
             _cube_data[21] = tmp2;
             _cube_data[24] = tmp3;
             break;
         case rotation_side::SIDE_F:
             /* BEFORE:
              *    6  7  8
              *   ----------
              * 11|[] [] []|27
              * 14|[] [] []|30
              * 17|[] [] []|33
              *   ----------
              *    45 46 47
              */
             tmp1 = _cube_data[6];
             tmp2 = _cube_data[7];
             tmp3 = _cube_data[8];
             // top
             _cube_data[6] = _cube_data[17];
             _cube_data[7] = _cube_data[14];
             _cube_data[8] = _cube_data[11];
             // left
             _cube_data[17] = _cube_data[47];
             _cube_data[14] = _cube_data[46];
             _cube_data[11] = _cube_data[45];
             // bottom
             _cube_data[47] = _cube_data[27];
             _cube_data[46] = _cube_data[30];
             _cube_data[45] = _cube_data[33];
             // right
             _cube_data[27] = tmp1;
             _cube_data[30] = tmp2;
             _cube_data[33] = tmp3;
             break;
         case rotation_side::SIDE_R:
             /* BEFORE:
              *    8  5  2
              *   ----------
              * 20|[] [] []|36
              * 23|[] [] []|39
              * 26|[] [] []|42
              *   ----------
              *    47 50 53
              */
             tmp1 = _cube_data[8];
             tmp2 = _cube_data[5];
             tmp3 = _cube_data[2];
             // top
             _cube_data[8] = _cube_data[26];
             _cube_data[5] = _cube_data[23];
             _cube_data[2] = _cube_data[20];
             // left
             _cube_data[26] = _cube_data[53];
             _cube_data[23] = _cube_data[50];
             _cube_data[20] = _cube_data[47];
             // bottom
             _cube_data[53] = _cube_data[36];
             _cube_data[50] = _cube_data[39];
             _cube_data[47] = _cube_data[42];
             // right
             _cube_data[36] = tmp1;
             _cube_data[39] = tmp2;
             _cube_data[42] = tmp3;
             break;
         case rotation_side::SIDE_B:
             /* BEFORE:
              *    2  1  0
              *   ----------
              * 29|[] [] []|9
              * 32|[] [] []|12
              * 35|[] [] []|15
              *   ----------
              *    53 52 51
              */
             tmp1 = _cube_data[2];
             tmp2 = _cube_data[1];
             tmp3 = _cube_data[0];
             // top
             _cube_data[2] = _cube_data[35];
             _cube_data[1] = _cube_data[32];
             _cube_data[0] = _cube_data[29];
             // left
             _cube_data[35] = _cube_data[51];
             _cube_data[32] = _cube_data[52];
             _cube_data[29] = _cube_data[53];
             // bottom
             _cube_data[51] = _cube_data[9 ];
             _cube_data[52] = _cube_data[12];
             _cube_data[53] = _cube_data[15];
             // right
             _cube_data[9 ] = tmp1;
             _cube_data[12] = tmp2;
             _cube_data[15] = tmp3;
             break;
         case rotation_side::SIDE_D:
             /* BEFORE:
              *    24 25 26
              *   ----------
              * 17|[] [] []|33
              * 16|[] [] []|34
              * 15|[] [] []|35
              *   ----------
              *    44 43 42
              */
             tmp1 = _cube_data[24];
             tmp2 = _cube_data[25];
             tmp3 = _cube_data[26];
             // top
             _cube_data[24] = _cube_data[15];
             _cube_data[25] = _cube_data[16];
             _cube_data[26] = _cube_data[17];
             // left
             _cube_data[15] = _cube_data[42];
             _cube_data[16] = _cube_data[43];
             _cube_data[17] = _cube_data[44];
             // bottom
             _cube_data[42] = _cube_data[33];
             _cube_data[43] = _cube_data[34];
             _cube_data[44] = _cube_data[35];
             // right
             _cube_data[33] = tmp1;
             _cube_data[34] = tmp2;
             _cube_data[35] = tmp3;
             break;
     }
 }

Cube_bg_model::ECOLOUR Cube_bg_model::colour(ECORNER index) const
{
    return _cube_data[(uint8_t)index];
}

Cube_bg_model::ECOLOUR Cube_bg_model::colour(EEDGE index) const
{
    return _cube_data[(uint8_t)index];
}

uint8_t Cube_bg_model::edge_orientation(const edge_t& edge) const
{
    return
         (( edge[0] == ECOLOUR::G || edge[0] == ECOLOUR::B) ||
          ((edge[0] == ECOLOUR::W || edge[0] == ECOLOUR::Y) &&
           (edge[1] == ECOLOUR::R || edge[1] == ECOLOUR::O)));

    // checks if a facelet has one of the colours from the R/L axis, if not, checks if it's from the U/D axis and
    // that the adjacent edge facelet has a colour from the F/B axis
}

uint8_t Cube_bg_model::corner_orientation(const corner_t& corner) const
{
    // www.ryanheise.com/cube/cube_laws.html
    // orientation is determined by the twist of the corner, but this follows
    // a differnet logic to avoid unnecessary extra code

    // retrun 0 / 1 / 2 based on which axis the L/R colour is on
    for (uint8_t i = 0; i < 3; ++i) {
        if (corner[i] == ECOLOUR::R || corner[i] == ECOLOUR::O)
            return i;
    }

    throw std::logic_error("Cube_bg_model::corner_orientation unable to get orientation, corner must have a R / O facelet");
}

uint8_t Cube_bg_model::edge_index(const edge_t& edge) const
{ 
    // unique index based on colour combinations
    uint8_t index = ((1 << (uint8_t)edge[0]) + (1 << (uint8_t)edge[1]));

    switch (index) {
    case 3:
        return 0;
    case 34:
        return 1;
    case 40:
        return 2;
    case 9:
        return 3;
    case 6:
        return 4;
    case 18:
        return 5;
    case 12:
        return 6;
    case 24:
        return 7;
    case 5:
        return 8;
    case 36:
        return 9;
    case 48:
        return 10;
    case 17:
        return 11;
    default:
        std::string colors = colour_name(edge[0]) + colour_name(edge[1]);
        throw std::logic_error("Cube_bg_model::corner_index invalid combination of edge colours: " + colors);
    }
}

uint8_t Cube_bg_model::corner_index(const corner_t& corner) const
{
    // unique index based on colour combinations
    uint8_t index = ((1 << (uint8_t)corner[0]) + (1 << (uint8_t)corner[1]) + (1 << (uint8_t)corner[2]));

    // W = 0 = 1
    // O = 1 = 2
    // G = 2 = 4
    // R = 3 = 8
    // B = 4 = 16
    // Y = 5 = 32

    // ULB = WOB = 19 = 0
    // ULF = WOG = 7  = 1
    // DLF = YOG = 38 = 2
    // DLB =

    switch (index) {
    case 19:
        return 0;
    case 7:
        return 1;
    case 38:
        return 2;
    case 50:
        return 3;
    case 56:
        return 4;
    case 44:
        return 5;
    case 13:
        return 6;
    case 25:
        return 7;
    default:
        std::string colours = colour_name(corner[0]) + colour_name(corner[1]) + colour_name(corner[2]);
        throw std::logic_error("Cube_bg_model::corner_index invalid combination of edge colours:" + colours);
    }
}

uint8_t Cube_bg_model::piece_index(EPIECE piece) const
{
    switch (piece) {
    case EPIECE::UL:
        return edge_index({colour(EEDGE::UL), colour(EEDGE::LU)});
    case EPIECE::DL:
        return edge_index({colour(EEDGE::DL), colour(EEDGE::LD)});
    case EPIECE::DR:
        return edge_index({colour(EEDGE::DR), colour(EEDGE::RD)});
    case EPIECE::UR:
        return edge_index({colour(EEDGE::UR), colour(EEDGE::RU)});
    case EPIECE::LF:
        return edge_index({colour(EEDGE::LF), colour(EEDGE::FL)});
    case EPIECE::LB:
        return edge_index({colour(EEDGE::LB), colour(EEDGE::BL)});
    case EPIECE::RF:
        return edge_index({colour(EEDGE::RF), colour(EEDGE::FR)});
    case EPIECE::RB:
        return edge_index({colour(EEDGE::RB), colour(EEDGE::BR)});
    case EPIECE::UF:
        return edge_index({colour(EEDGE::UF), colour(EEDGE::FU)});
    case EPIECE::DF:
        return edge_index({colour(EEDGE::DF), colour(EEDGE::FD)});
    case EPIECE::DB:
        return edge_index({colour(EEDGE::DB), colour(EEDGE::BD)});
    case EPIECE::UB:
        return edge_index({colour(EEDGE::UB), colour(EEDGE::BU)});
    case EPIECE::ULB:
        return corner_index({colour(ECORNER::LUB), colour(ECORNER::ULB), colour(ECORNER::BLU)});
    case EPIECE::ULF:
        return corner_index({colour(ECORNER::LUF), colour(ECORNER::ULF), colour(ECORNER::FLU)});
    case EPIECE::DLF:
        return corner_index({colour(ECORNER::LDF), colour(ECORNER::DLF), colour(ECORNER::FLD)});
    case EPIECE::DLB:
        return corner_index({colour(ECORNER::LDB), colour(ECORNER::DLB), colour(ECORNER::BLD)});
    case EPIECE::DRB:
        return corner_index({colour(ECORNER::RDB), colour(ECORNER::DRB), colour(ECORNER::BRD)});
    case EPIECE::DRF:
        return corner_index({colour(ECORNER::RDF), colour(ECORNER::DRF), colour(ECORNER::FRD)});
    case EPIECE::URF:
        return corner_index({colour(ECORNER::RUF), colour(ECORNER::URF), colour(ECORNER::FRU)});
    case EPIECE::URB:
        return corner_index({colour(ECORNER::RUB), colour(ECORNER::URB), colour(ECORNER::BRU)});
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Cube_bg_model::piece_index invalid enum value: " + value);
    }
}

Cube_bg_model::edge_t Cube_bg_model::edge(EPIECE piece) const
{
    switch (piece) {
    case EPIECE::UL:
        return {colour(EEDGE::LU), colour(EEDGE::UL)};
    case EPIECE::DL:
        return {colour(EEDGE::LD), colour(EEDGE::DL)};
    case EPIECE::DR:
        return {colour(EEDGE::RD), colour(EEDGE::DR)};
    case EPIECE::UR:
        return {colour(EEDGE::RU), colour(EEDGE::UR)};
    case EPIECE::LF:
        return {colour(EEDGE::LF), colour(EEDGE::FL)};
    case EPIECE::LB:
        return {colour(EEDGE::LB), colour(EEDGE::BL)};
    case EPIECE::RF:
        return {colour(EEDGE::RF), colour(EEDGE::FR)};
    case EPIECE::RB:
        return {colour(EEDGE::RB), colour(EEDGE::BR)};
    case EPIECE::UF:
        return {colour(EEDGE::UF), colour(EEDGE::FU)};
    case EPIECE::DF:
        return {colour(EEDGE::DF), colour(EEDGE::FD)};
    case EPIECE::DB:
        return {colour(EEDGE::DB), colour(EEDGE::BD)};
    case EPIECE::UB:
        return {colour(EEDGE::UB), colour(EEDGE::BU)};
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Cube_bg_model::edge invalid enum value: " + value);
    }
}

Cube_bg_model::corner_t Cube_bg_model::corner(EPIECE piece) const
{
    // same as edge(), only requires the position of the edge / corner piece
    switch (piece) {
    case EPIECE::ULB:
        return {colour(ECORNER::LUB), colour(ECORNER::ULB), colour(ECORNER::BLU)};
    case EPIECE::ULF:
        return {colour(ECORNER::LUF), colour(ECORNER::ULF), colour(ECORNER::FLU)};
    case EPIECE::DLF:
        return {colour(ECORNER::LDF), colour(ECORNER::DLF), colour(ECORNER::FLD)};
    case EPIECE::DLB:
        return {colour(ECORNER::LDB), colour(ECORNER::DLB), colour(ECORNER::BLD)};
    case EPIECE::DRB:
        return {colour(ECORNER::RDB), colour(ECORNER::DRB), colour(ECORNER::BRD)};
    case EPIECE::DRF:
        return {colour(ECORNER::RDF), colour(ECORNER::DRF), colour(ECORNER::FRD)};
    case EPIECE::URF:
        return {colour(ECORNER::RUF), colour(ECORNER::URF), colour(ECORNER::FRU)};
    case EPIECE::URB:
        return {colour(ECORNER::RUB), colour(ECORNER::URB), colour(ECORNER::BRU)};
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Cube_bg_model::corner invalid enum value: " + value);
    }
}

std::string Cube_bg_model::colour_name(ECOLOUR colour) const
{
    switch (colour) {
    case ECOLOUR::W:
        return "W";
    case ECOLOUR::O:
        return "O";
    case ECOLOUR::G:
        return "G";
    case ECOLOUR::R:
        return "R";
    case ECOLOUR::B:
        return "B";
    case ECOLOUR::Y:
        return "Y";
    default:
        std::string value = std::to_string((int)colour);
        throw std::logic_error("Cube_bg_model::colour_name invalid enum value: " + value);
    }
}

std::string Cube_bg_model::move_name(EMOVE move) const
{
    switch (move) {
    case EMOVE::U:
        return "U";
    case EMOVE::Up:
        return "U'";
    case EMOVE::U2:
        return "U2";
    case EMOVE::L:
        return "L";
    case EMOVE::Lp:
        return "L'";
    case EMOVE::L2:
        return "L2";
    case EMOVE::F:
        return "F";
    case EMOVE::Fp:
        return "F'";
    case EMOVE::F2:
        return "F2";
    case EMOVE::R:
        return "R";
    case EMOVE::Rp:
        return "R'";
    case EMOVE::R2:
        return "R2";
    case EMOVE::B:
        return "B";
    case EMOVE::Bp:
        return "B'";
    case EMOVE::B2:
        return "B2";
    case EMOVE::D:
        return "D";
    case EMOVE::Dp:
        return "D'";
    case EMOVE::D2:
        return "D2";
    case EMOVE::NO_MOVE:
        return "";
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Cube_bg_model::move_name invalid enum value: " + value);
    }
}