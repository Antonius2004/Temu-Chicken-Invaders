//
// Created by patur on 12/9/2025.
//

#ifndef GFXFRAMEWORK_ENUMS_H
#define GFXFRAMEWORK_ENUMS_H

namespace m1
{
    enum class TurnOrientation {
        NE,
        NV,
        SE,
        SV
    };

    enum class TerrainType {
        Grass,
        Mountain,
        Water,
        None
    };

    enum class Type {
        Straight,
        Turn
    };

    enum class StraightOrientation {
        NS,
        VE
    };

    enum class Headings {
        N,
        E,
        S,
        V
    };
} // m1

#endif //GFXFRAMEWORK_ENUMS_H