# Line_follower_boat
 
 Overview
A simple robot that follows a black line using 3 IR sensors and detects harmful gases using a gas sensor (e.g., MQ-2). Alerts are triggered when gas levels exceed a safe threshold.

 Components
3× IR Sensors
1× Gas Sensor (MQ-2/MQ-3)
L293D Motor Driver
2× DC Motors + Wheels
Arduino/NodeMCU
Chassis + Battery Pack
Optional: Buzzer or LED

 Working
IR Sensors detect the line:
Middle active → Forward
Left active → Turn left
Right active → Turn right
Gas Sensor continuously monitors air:
High gas level → Trigger buzzer/LED alert

🔌 Connections
IR sensors → Digital pins
Gas sensor → Analog pin (A0)
Motor driver → Digital pins
Power → Battery/USB

 Usage
Upload code to controller
Place robot on a black line path
Power up → It follows the path and detects gas leaks

🏭 Industrial Application
This robot can be adapted for automated gas leakage detection in industries like:
Chemical plants
Oil refineries
Warehouses
It can autonomously patrol fixed paths (via line-following) and detect hazardous gas leaks, improving safety and early response without human exposure
