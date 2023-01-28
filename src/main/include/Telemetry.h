#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "DriveTrain.h"
#include <ctre/phoenix/sensors/PigeonIMU.h>
#include "DataPacket.h"
#include "Timer.h"
#include <queue>
#include <list>

class Telemetry
{

public:
    Telemetry(DriveTrain *drvt);
    ~Telemetry();
    SparkMaxPacket *exportTelemetry(); // Exports the pointer to the telemetry struct
    void runMetrics();                 // Main function for updating data

private:
    void captureSnapshot();
    void manageRewind();
    DriveTrain *drivebase; // Object pointer to hold reference to our drive base
    ctre::phoenix::sensors::PigeonIMU *gyro;
    SparkMaxPacket *drivetrain_data; // Holds the robot telemetry data
    Timer *snapshot_timer;           // Timer for managing snapshots of robo data
    unsigned int timer_interval;     // How often we should take robot snapshots
    struct Snapshot
    {
        double left_pos;
        double left_speed;
        double right_pos;
        double right_speed;
        double x_rot;
    };

    struct Snapshot *new_capture; // Holds data from the latest snapshot
    std::queue<struct Snapshot *> instruction_queue;
    std::list<struct Snapshot *> rewind_steps;
    unsigned int max_rewind_time;  // Sets how long we store data of previous positioning
    unsigned int max_rewind_steps; // Changes depending on poll time to store 5s of past position data
};

#endif // TELEMETRY_H