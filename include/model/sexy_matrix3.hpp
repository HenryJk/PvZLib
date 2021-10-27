#pragma once

namespace pvz {
    struct SexyMatrix3_u_0_s_1 {
        float m00;
        float m01;
        float m02;
        float m10;
        float m11;
        float m12;
        float m20;
        float m21;
        float m22;
    };

    struct SexyMatrix3 {
        union SexyMatrix3_u_0 {
            float m[3][3];
            SexyMatrix3_u_0_s_1 _s_1;
        };
    };
} // namespace pvz
