// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <cmath>
#include "math.h"

//speed curve multiplicative value
double vel_Modifier = 1;

//calling drive with xbox stick input
  
  float inputModifier = 1;
  double steep = 3;
  double midSpeed = 0.1;

void Robot::RobotInit() {
  m_drive.SetNeutralMode(Coast);
  m_turn.SetNeutralMode(Brake);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  timer.Reset();
  timer.Start();

  inputModifier = m_drive.Get();
  vel_Modifier = 1/(1 + exp( (-steep)*( inputModifier - midSpeed )));

}
void Robot::AutonomousPeriodic() {
  std::cout<<"Starting Autonomous Routine"<<std::endl;

  std::cout<<"Autonomous Routine Complete"<<std::endl;
}

void Robot::TeleopInit() {
}

//std::units vel_Modifier = 1;


/*
void Robot::TeleopPeriodic() {
  //calling drive with xbox stick input
  m_drive.Set((0.8 * m_driverController.GetRightY()));
  m_turn.Set((
    (
      m_driverController.GetLeftBumper() -  
      m_driverController.GetRightBumper()
    )*
    (1)

  )
  *0.9
  );
  }
  */


  
  void Robot::TeleopPeriodic() {
  //calling drive with xbox stick input
  float inputModifier = fabs(m_drive.Get());

  //how quickly the acceleration will happen
  double steep = 3;

  //time when robot will reach 50% max speed
  double midSpeed = 0.1;

  double vel_Modifier = 1/(1 + exp( (-steep)*( inputModifier - midSpeed )));

  m_drive.Set(vel_Modifier*(0.8 * m_driverController.GetRightY()));
  m_turn.Set((
    (
      m_driverController.GetLeftBumper() -  
      m_driverController.GetRightBumper()
    )*
    (1)

  )
  *0.9
  );
  }
  
  

void Robot::DisabledInit() {
}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif