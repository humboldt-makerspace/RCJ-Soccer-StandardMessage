#include <RCJSoccerProtocol.h>

RCJSoccerProtocolClass RCJSoccerProtocol(&Serial3);

BluetoothProtocol blueData;
BluetoothProtocol blueDataRecieve;
unsigned long t1 = millis();

void setData() {
  //currently just a dummy for call and response, you have to insert your data
  blueData.data_team_number = blueDataRecieve.data_team_number + 1;
  blueData.data_team_id = blueDataRecieve.data_team_id + 1;
  blueData.data_robot_number = blueDataRecieve.data_robot_number + 1;
  blueData.data_robot_position_x = blueDataRecieve.data_robot_position_x + 1;
  blueData.data_robot_position_y = blueDataRecieve.data_robot_position_y + 1;
  blueData.data_robot_position_z = blueDataRecieve.data_robot_position_z + 1;
  blueData.data_robot_velocity_x = blueDataRecieve.data_robot_velocity_x + 1;
  blueData.data_robot_velocity_y = blueDataRecieve.data_robot_velocity_y + 1;
  blueData.data_robot_status = blueDataRecieve.data_robot_status + 1;
  blueData.data_robot_role = blueDataRecieve.data_robot_role + 1;
  for (int i = 0; i < 11; i++) {
    blueData.data_robot_suggestion[i] = blueDataRecieve.data_robot_suggestion[i] + 1;
  }
  blueData.data_ball_has = blueDataRecieve.data_ball_has + 1;
  blueData.data_ball_age = blueDataRecieve.data_ball_age + 1;
  blueData.data_ball_position_x = blueDataRecieve.data_ball_position_x + 1;
  blueData.data_ball_position_y = blueDataRecieve.data_ball_position_y + 1;
  blueData.data_ball_velocity_x = blueDataRecieve.data_ball_velocity_x + 1;
  blueData.data_ball_velocity_y = blueDataRecieve.data_ball_velocity_y + 1;
  blueData.timestamp = blueDataRecieve.timestamp + 1;
}


void setup() {
  
  Serial.begin(115200);

  //Setup for BlueMate/BlueSmirf 
  Serial3.begin(115200);
  delay(50);
  Serial3.print("$$$");//enter internal mode
  delay(50);
  Serial3.println("SM,0");//Slavemode
  delay(500);
  Serial3.println("---");//exit internal mode
}

void loop() {
  
  if (millis() > t1 + 100) {
    setData();
    RCJSoccerProtocol.sendData(&blueData);
    Serial.println("Send Message");
    t1 = millis();
  }

  while (Serial3.available()) {
      String message = Serial3.readStringUntil('\n');
      Serial.println("Recieved Message:" + message);
      RCJSoccerProtocol.getData(message,&blueDataRecieve);
  }

}
