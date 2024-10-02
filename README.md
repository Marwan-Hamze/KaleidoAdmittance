This is a simple admittance controller, commanding Kaleido (RHP7) to make apply a desired force using its right hand on the wall the robot is facing.
(This might be extended to moving the right foot to create a contact with another surface, still in progress)

The controller is written using the [mc_rtc](https://jrl-umi3218.github.io/mc_rtc/index.html) framework.
The finite state machine (FSM) states are written in the robot configuration file (YAML).