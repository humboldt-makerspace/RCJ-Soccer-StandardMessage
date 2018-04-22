/*
 LICENSE
 */

#ifndef RCJSoccerProtocol__h
#define RCJSoccerProtocol__h

#include <Arduino.h>
#include <aJSON.h>
#include <Stream.h>

struct BluetoothProtocol {
  String header = "RCJ Soccer Open";
  String version = "1.0";
  int data_team_number = 0;
  int data_team_id = 0;
  int data_robot_number = 0;
  int data_robot_position_x = 0;
  int data_robot_position_y = 0;
  int data_robot_position_z = 0;
  int data_robot_velocity_x = 0;
  int data_robot_velocity_y = 0;
  int data_robot_status = 0;
  int data_robot_role = 0;
  int data_robot_suggestion[11];
  int data_ball_has = 0;
  int data_ball_age = 0;
  int data_ball_position_x = 0;
  int data_ball_position_y = 0;
  int data_ball_velocity_x = 0;
  int data_ball_velocity_y = 0;
  int timestamp = 0;
  // customData
};


class RCJSoccerProtocolClass{
  public:
    RCJSoccerProtocolClass(Stream* stream);
    ~RCJSoccerProtocolClass();
    boolean sendData(BluetoothProtocol* data);
    boolean getData(String message, BluetoothProtocol* data);
	
  private:
  Stream* myStream;
    void buildJson();
    void parseJson();
};

#endif
