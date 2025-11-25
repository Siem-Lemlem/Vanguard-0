#ifndef DRONE_H
#define DRONE_H

#include "math/Vector3.h"
#include <iostream>

// NEIGHBOR: This is the GT-7 drone. It has a position (where it is), velocity (how fast
//           it's moving), mass (how heavy), and thrust (how much upward push).
//           Every frame, we calculate forces (gravity pulls down, thrust pushes up),
//           then update velocity and position using physics from your class.
//
// NEWTON: Point-mass rigid body simulation with 3-DOF translational dynamics.
//         Uses semi-implicit Euler integration for numerical stability.
//         F = ma → a = F/m → v_new = v_old + a·dt → x_new = x_old + v_new·dt

class Drone {
public:
    // Physical state
    Vector3 position;      // meters (x, y, z in world space)
    Vector3 velocity;      // meter per second
    double mass;           // kilograms

    // Control input
    double thrustPercent;  // 0.0 to 1.0 (0% to 100% power)

    // GT-7 Specifications
    static constexpr double MAX_THRUST = 32.0;   // Newtons (4 fans * 8N each)
    static constexpr double GRAVITY = 9.81;      // m/s^2 (Earth standard)

    // Constructor
    // NEIGHBOR: When we create a drone, we set its starting position and mass.
    //           It starts with zero velocity (not moving) and zero thrust (engines off).
    // NEWTON: Initialize state vector with given initial conditions.

    Drone(Vector3 startPos = Vector3::Zero(), double m = 1.5)
        : position(startPos),
          velocity(Vector3::Zero()),
          mass(m),
          thrustPercent(0.0)
    {}

    // NEIGHBOR: Set thrust as a percentage. 0.5 means 50% power.
    //           We clamp it between 0 and 1 so you can't accidentally set 500% thrust.
    // NEWTON: Normalized thrust control input ∈ [0,1] mapped to force magnitude.
    
    void setThrustPercent(double percent) {
        if (percent < 0.0) percent = 0.0;
        if (percent > 1.0) percent = 1.0;
        thrustPercent = percent;
    }

    // NEIGHBOR: Get the actual force in Newtons. If thrust is 50%, that's 16N.
    // NEWTON: Convert normalized control input to force vector magnitude.

    double getThrustNewtons() const {
        return thrustPercent * MAX_THRUST;
    }

    // NEIGHBOR: Calculate what thrust percentage we need to hover (not fall or rise).
    //           Hover means thrust exactly cancels gravity: T = m·g
    //           Then convert to percentage: T / MAX_THRUST
    // NEWTON: Equilibrium condition for vertical flight: ΣF = 0 → T = mg

    double getHoverThrust() const {
        double requiredForce = mass * GRAVITY;  // Force needed to cancel gravity
        return requiredForce / MAX_THRUST;      // Convert to percentage
    }

    // NEIGHBOR: This is the physics update. Called every frame (every dt seconds).
    //           Steps: 1) Calculate all forces (gravity + thrust)
    //                  2) Find acceleration (F = ma, so a = F/m)
    //                  3) Update velocity (v = v + a·dt) - SEMI-IMPLICIT EULER
    //                  4) Update position (x = x + v·dt) using NEW velocity
    // NEWTON: Numerical integration of equations of motion using semi-implicit Euler method.
    //         More stable than explicit Euler due to using updated velocity for position.

    void update(double dt) {
        // Step 1: Calculate forces
        Vector3 gravity = Vector3(0, 0, -GRAVITY * mass);   // Pull down (negative Z)
        Vector3 thrust = Vector3(0, 0, getThrustNewtons()); // Push up (positive Z)
        Vector3 totalForce = gravity + thrust;

        // Step 2: Calculate acceleration (Newton's 2nd law: a = F/m)
        Vector3 acceleration = totalForce / mass;

        // Step 3: Update velocity First (semi-implicit Euler)
        velocity += acceleration * dt;

        // Step 4: Update position using NEW velocity
        position += velocity * dt;
    }

    // Utility functions for data logging and display
    double getAltitude() const { return position.z; }
    double getSpeed() const { return velocity.magnitude(); }
    double getVerticalSpeed() const { return velocity.z; }

    // NEIGHBOR: Print current state to console for debugging
    void printState() const {
        std::cout << "Position: " << position << " m" << std::endl;
        std::cout << "Velocity: " << velocity << " m/s" << std::endl;
        std::cout << "Altitude: " << getAltitude() << " m" << std::endl;
        std::cout << "Speed: " << getSpeed() << " m/s" << std::endl;
        std::cout << "Thrust: " << (thrustPercent * 100) << "% (" 
                  << getThrustNewtons() << " N)" << std::endl;
    }
};

#endif