#include "curves.h"
#include <algorithm>

// ============================================================
// Joystick Curve Implementations
// ============================================================
// All curves map input (-127..127) → output (-127..127).
// The sign is always preserved so negative stick = negative output.

int applyCurve(int input, CurveType curve, double param) {
    // Clamp input to valid joystick range
    input = std::clamp(input, -127, 127);

    // Normalize to -1.0 .. 1.0
    double x = input / 127.0;
    double sign = (x < 0) ? -1.0 : 1.0;
    double ax = std::abs(x);   // work with positive magnitude
    double result = 0.0;

    switch (curve) {

        // ── LINEAR ──────────────────────────────────────────
        // output = input  (no transformation)
        case CurveType::LINEAR:
            result = ax;
            break;

        // ── SQUARED ─────────────────────────────────────────
        // output = x²  — gentle low-end, full power at max
        // Great general-purpose curve for driving
        case CurveType::SQUARED:
            result = ax * ax;
            break;

        // ── CUBED ───────────────────────────────────────────
        // output = x³  — very gentle low-end, aggressive top-end
        // Best for precision tasks (lining up with goals, etc.)
        case CurveType::CUBED:
            result = ax * ax * ax;
            break;

        // ── EXPONENTIAL ─────────────────────────────────────
        // output = (e^(k*x) - 1) / (e^k - 1)
        // 'param' controls aggressiveness:
        //   k ≈ 0.5 → almost linear
        //   k ≈ 1.5 → nice default (similar to squared)
        //   k ≈ 3.0 → very aggressive dampening at low inputs
        case CurveType::EXPONENTIAL: {
            double k = (param > 0.01) ? param : 1.5;  // default k = 1.5
            result = (std::exp(k * ax) - 1.0) / (std::exp(k) - 1.0);
            break;
        }

        // ── S-CURVE (SIGMOID) ───────────────────────────────
        // Dampens both low AND high inputs; steep ramp in the middle.
        // Prevents jerky starts and accidental full-power.
        case CurveType::S_CURVE: {
            // Attempt a scaled tanh: tanh is naturally -1..1
            // We use tanh(k * (x - 0.5)) shifted/scaled to map 0→0 and 1→1
            double k = 3.0;  // steepness of the S
            double raw = std::tanh(k * (ax - 0.5));
            double lo  = std::tanh(k * (0.0 - 0.5));
            double hi  = std::tanh(k * (1.0 - 0.5));
            result = (raw - lo) / (hi - lo);
            break;
        }

        // ── PIECEWISE LINEAR ────────────────────────────────
        // Two linear zones:
        //   Zone 1 (0 to breakpoint):  gentle slope  (0→0.15)
        //   Zone 2 (breakpoint to 1):  steeper slope  (0.15→1.0)
        // 'param' sets the breakpoint (default 0.3 = 30% stick)
        case CurveType::PIECEWISE: {
            double bp = (param > 0.01) ? param : 0.3;   // breakpoint
            double low_out = 0.15;                        // output at breakpoint
            if (ax <= bp) {
                result = (low_out / bp) * ax;
            } else {
                result = low_out + ((1.0 - low_out) / (1.0 - bp)) * (ax - bp);
            }
            break;
        }
    }

    // Scale back to -127..127 and restore sign
    int output = static_cast<int>(sign * result * 127.0);
    return std::clamp(output, -127, 127);
}

// Human-readable names for the brain screen / controller display
std::string getCurveName(CurveType curve) {
    switch (curve) {
        case CurveType::LINEAR:      return "Linear";
        case CurveType::SQUARED:     return "Squared";
        case CurveType::CUBED:       return "Cubed";
        case CurveType::EXPONENTIAL: return "Exponential";
        case CurveType::S_CURVE:     return "S-Curve";
        case CurveType::PIECEWISE:   return "Piecewise";
        default:                     return "Unknown";
    }
}

// Cycle to the next curve (wraps back to LINEAR after PIECEWISE)
CurveType nextCurve(CurveType current) {
    int next = (static_cast<int>(current) + 1) % 6;
    return static_cast<CurveType>(next);
}
