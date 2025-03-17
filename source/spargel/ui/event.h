#pragma once

namespace spargel::ui {

    enum KeyboardAction {
        press,
        release,
    };

    enum PhysicalKey {
        escape,
        key_a,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,
        space,
        key_delete,

        unknown,
    };

    struct KeyboardEvent {
        KeyboardAction action;
        PhysicalKey key;

        // todo: hack
        char toChar();
    };

}  // namespace spargel::ui
