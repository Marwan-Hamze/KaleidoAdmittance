#include "KaleidoAdmittance.h"

KaleidoAdmittance::KaleidoAdmittance(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::fsm::Controller(rm, dt, config)
{

  config_.load(config);

  // Activedof_ = config("active_dof");

  Activedof_ = {"Root", "L_CROTCH_Y", "L_CROTCH_R", "L_CROTCH_P", "L_KNEE_P", "L_ANKLE_R", "L_ANKLE_P", 
                      "R_CROTCH_Y", "R_CROTCH_R", "R_CROTCH_P", "R_KNEE_P", "R_ANKLE_R", "R_ANKLE_P"};

  // Setting the anchor frame for the Kinematic Inertial estimator

  // datastore().make_call("KinematicAnchorFrame::" + robot().name(),
  //                         [this](const mc_rbdyn::Robot & robot)
  //                         {
  //                           return sva::interpolate(robot.surfacePose("LeftFoot"),
  //                                                   robot.surfacePose("RightFoot"),
  //                                                   leftFootRatio);
  //                         });

  comTask_ = std::make_shared<mc_tasks::CoMTask>(robots(), robots().robot().robotIndex(), 2, 1e7);
  baseTask_ = std::make_shared<mc_tasks::OrientationTask>("BODY", robots(), robots().robot().robotIndex(), 2, 1e7);
  chestTask_ = std::make_shared<mc_tasks::OrientationTask>("CHEST_P_LINK", robots(), robots().robot().robotIndex(), 0, 1e7);

  rightArm_PosTask_ = std::make_shared<mc_tasks::PositionTask>("R_HAND_LINK", robots(), robots().robot().robotIndex(), 2, 1e9);
  rightArm_OrTask_ = std::make_shared<mc_tasks::OrientationTask>("R_HAND_LINK", robots(), robots().robot().robotIndex(), 2, 1e9);
  rightArm_ForceTask_ = std::make_shared<mc_tasks::force::AdmittanceTask>("RightHand", robots(), robots().robot().robotIndex(), 2.0, 1e9);


  logger().addLogEntry("Kaleido_CoM", [this]() { return realRobots().robot().com(); });
  logger().addLogEntry("RightHand_Force", [this]() {return realRobots().robot().forceSensor("RightHandForceSensor").wrenchWithoutGravity(realRobots().robot()).force();});

  mc_rtc::log::success("KaleidoAdmittance init done ");
  
}

bool KaleidoAdmittance::run()
{

  if(armPos) {

      rightArm_ForceTask_->targetWrench(sva::ForceVecd({0, 0, 0}, {0, 0, 30}));    

      // mc_rtc::log::info("Applied 30N of Force\n");

  }

  t_ += timeStep;

  return mc_control::fsm::Controller::run();
}

void KaleidoAdmittance::reset(const mc_control::ControllerResetData & reset_data)
{

  comTask_->reset();
  baseTask_->reset();
  chestTask_->reset();


  // Add the CoM and Base Tasks permanently to not cause the drifting of the base of the robot when the controller is disabled

  comTask_->selectActiveJoints(Activedof_);
  baseTask_->selectActiveJoints(Activedof_);

  solver().addTask(comTask_);
  solver().addTask(baseTask_);

  // const auto & observerp = observerPipeline(observerPipelineName_);
  
  // if(observerp.success())
  // {
  //   mc_rtc::log::info("Pipeline \"{}\" for real robot observation loaded!", observerPipelineName_);
  // }

  if (!start) {

    gui()->addElement({"Controller"}, mc_rtc::gui::Button("MoveRightArm", [this]() {


      // comTask_->com(comTask_->com() + Eigen::Vector3d{0.05, 0.00, 0});
      rightArm_PosTask_->position({600, -0.20, 1.00});
      

      if(rightArm_PosTask_->eval().norm() < 1e-20) {

      mc_rtc::log::info("Moved the Right Arm into Position\n");


      start = true;
      armPos = true;
      }

   }));
  }

  // Plot related code in RViz

  using Color = mc_rtc::gui::Color;

  gui()->addPlot(
    "Right Hand Force (t)", mc_rtc::gui::plot::X("t", [this]() { return t_; }),
    mc_rtc::gui::plot::Y(
        "f_RH(z)", [this]() { return realRobots().robot().forceSensor("RightHandForceSensor").wrenchWithoutGravity(realRobots().robot()).force().z(); }, Color::Red), 
    mc_rtc::gui::plot::Y(
        "f_RH(x)", [this]() { return realRobots().robot().forceSensor("RightHandForceSensor").wrenchWithoutGravity(realRobots().robot()).force().x(); }, Color::Green),
    mc_rtc::gui::plot::Y(
        "f_RH(y)", [this]() { return realRobots().robot().forceSensor("RightHandForceSensor").wrenchWithoutGravity(realRobots().robot()).force().y(); }, Color::Blue)
        ); 

  mc_control::fsm::Controller::reset(reset_data);

}


