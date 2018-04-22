#include "RCJSoccerProtocol.h"


RCJSoccerProtocolClass::RCJSoccerProtocolClass(Stream* stream){
	myStream = stream;
}
RCJSoccerProtocolClass::~RCJSoccerProtocolClass(){}

boolean RCJSoccerProtocolClass::sendData(BluetoothProtocol *messageData){
  aJsonStream serial_stream(myStream);	
  aJsonObject* root = aJson.createObject();
  aJsonObject* data;
  aJsonObject* team;
  aJsonObject* robot;
  aJsonObject* robotPosition;
  aJsonObject* robotVelocity;
  aJsonObject* suggestion = aJson.createIntArray(messageData->data_robot_suggestion, 11);
  aJsonObject* ball;
  aJsonObject* ballPosition;
  aJsonObject* ballVelocity;
  aJsonObject* customData;

  aJson.addStringToObject(root, "header", messageData->header.c_str());
  aJson.addStringToObject(root, "version", messageData->version.c_str());

  aJson.addItemToObject(root, "data", data = aJson.createObject());
  aJson.addItemToObject(data, "team", team = aJson.createObject());
  aJson.addNumberToObject(team, "number", messageData->data_team_number);
  aJson.addNumberToObject(team, "id", messageData->data_team_id);
  aJson.addItemToObject(data, "robot", robot = aJson.createObject());
  aJson.addNumberToObject(robot, "number", messageData->data_robot_number);
  aJson.addItemToObject(robot, "position", robotPosition = aJson.createObject());
  aJson.addItemToObject(robot, "velocity", robotVelocity = aJson.createObject());
  aJson.addNumberToObject(robotPosition, "x", messageData->data_robot_position_x);
  aJson.addNumberToObject(robotPosition, "y", messageData->data_robot_position_y);
  aJson.addNumberToObject(robotPosition, "z", messageData->data_robot_position_z);
  aJson.addNumberToObject(robotVelocity, "x", messageData->data_robot_velocity_x);
  aJson.addNumberToObject(robotVelocity, "y", messageData->data_robot_velocity_y);
  aJson.addNumberToObject(robot, "status", messageData->data_robot_status);
  aJson.addNumberToObject(robot, "role", messageData->data_robot_role);
  aJson.addItemToObject(robot, "suggestion", suggestion);
  aJson.addItemToObject(data, "ball", ball = aJson.createObject());
  aJson.addNumberToObject(ball, "has", messageData->data_ball_has);
  aJson.addNumberToObject(ball, "age", messageData->data_ball_age);
  aJson.addItemToObject(ball, "position", ballPosition = aJson.createObject());
  aJson.addItemToObject(ball, "velocity", ballVelocity = aJson.createObject());
  aJson.addNumberToObject(ballPosition, "x", messageData->data_ball_position_x);
  aJson.addNumberToObject(ballPosition, "y", messageData->data_ball_position_y);
  aJson.addNumberToObject(ballVelocity, "x", messageData->data_ball_velocity_x);
  aJson.addNumberToObject(ballVelocity, "y", messageData->data_ball_velocity_y);
  aJson.addNumberToObject(root, "timestamp", messageData->timestamp);
  aJson.addItemToObject(root, "customData", customData = aJson.createObject());

  aJson.print(root, &serial_stream);
  myStream->println();
  aJson.deleteItem(root);
}

boolean RCJSoccerProtocolClass::getData(String message, BluetoothProtocol* blueDataRecieve){
  char cMessage[message.length() + 1];
  message.toCharArray(cMessage, message.length() + 1);
  aJsonObject* root = aJson.parse(cMessage);

  if (root != NULL) {

    aJsonObject* header = aJson.getObjectItem(root, "header");
    if (header != NULL) {
      blueDataRecieve->header = header->valuestring;
    }
    aJsonObject* version = aJson.getObjectItem(root, "version");
    if (version != NULL) {
      blueDataRecieve->version = version->valuestring;
    }

    aJsonObject* data = aJson.getObjectItem(root, "data");
    if (data != NULL) {
      aJsonObject* team = aJson.getObjectItem(data, "team");
      if (team != NULL) {
        aJsonObject* teamNumber = aJson.getObjectItem(team, "number");
        if (teamNumber != NULL) {
          blueDataRecieve->data_team_number = teamNumber->valueint;
        }
        aJsonObject* teamID = aJson.getObjectItem(team, "id");
        if (teamID != NULL) {
          blueDataRecieve->data_team_id = teamID->valueint;
        }
      }

      aJsonObject* robot = aJson.getObjectItem(data, "robot");
      if (robot != NULL) {
        aJsonObject* robotNumber = aJson.getObjectItem(robot, "number");
        if (robotNumber != NULL) {
          blueDataRecieve->data_robot_number = robotNumber->valueint;
        }

        aJsonObject* robotPosition = aJson.getObjectItem(robot, "position");
        if (robotPosition != NULL) {
          aJsonObject* robotPositionX = aJson.getObjectItem(robotPosition, "x");
          if (robotPositionX != NULL) {
            blueDataRecieve->data_robot_position_x = robotPositionX->valueint;
          }

          aJsonObject* robotPositionY = aJson.getObjectItem(robotPosition, "y");
          if (robotPositionY != NULL) {
            blueDataRecieve->data_robot_position_y = robotPositionY->valueint;
          }

          aJsonObject* robotPositionZ = aJson.getObjectItem(robotPosition, "z");
          if (robotPositionZ != NULL) {
            blueDataRecieve->data_robot_position_z = robotPositionZ->valueint;
          }
        }


        aJsonObject* robotVelocity = aJson.getObjectItem(robot, "velocity");
        if (robotVelocity != NULL) {
          aJsonObject* robotVelocityX = aJson.getObjectItem(robotVelocity, "x");
          if (robotVelocityX != NULL) {
            blueDataRecieve->data_robot_velocity_x = robotVelocityX->valueint;
          }

          aJsonObject* robotVelocityY = aJson.getObjectItem(robotVelocity, "y");
          if (robotVelocityY != NULL) {
            blueDataRecieve->data_robot_velocity_y = robotVelocityY->valueint;
          }
        }

        aJsonObject* robotStatus = aJson.getObjectItem(robot, "status");
        if (robotStatus != NULL) {
          blueDataRecieve->data_robot_status = robotStatus->valueint;
        }

        aJsonObject* robotRole = aJson.getObjectItem(robot, "role");
        if (robotRole != NULL) {
          blueDataRecieve->data_robot_role = robotRole->valueint;
        }

        for (int i = 0; i < 11; i++) {
          aJsonObject *suggestionVal = aJson.getObjectItem(robot, String(i).c_str());
          if (suggestionVal != NULL) {
            blueDataRecieve->data_robot_suggestion[i] = suggestionVal->valueint;
          }
        }
      }//robot

      aJsonObject* ball = aJson.getObjectItem(data, "ball");
      if (ball != NULL) {
        aJsonObject* ballHas = aJson.getObjectItem(ball, "has");
        if (ballHas != NULL) {
          blueDataRecieve->data_ball_has = ballHas->valueint;
        }

        aJsonObject* ballAge = aJson.getObjectItem(ball, "age");
        if (ballAge != NULL) {
          blueDataRecieve->data_ball_age = ballAge->valueint;
        }

        aJsonObject* ballPosition = aJson.getObjectItem(ball, "position");
        if (ballPosition != NULL) {
          aJsonObject* ballPositionX = aJson.getObjectItem(ballPosition, "x");
          if (ballPositionX != NULL) {
            blueDataRecieve->data_ball_position_x = ballPositionX->valueint;
          }

          aJsonObject* ballPositionY = aJson.getObjectItem(ballPosition, "y");
          if (ballPositionY != NULL) {
            blueDataRecieve->data_ball_position_y = ballPositionY->valueint;
          }
        }


        aJsonObject* ballVelocity = aJson.getObjectItem(ball, "velocity");
        if (ballVelocity != NULL) {
          aJsonObject* ballVelocityX = aJson.getObjectItem(ballVelocity, "x");
          if (ballVelocityX != NULL) {
            blueDataRecieve->data_ball_velocity_x = ballVelocityX->valueint;
          }

          aJsonObject* ballVelocityY = aJson.getObjectItem(ballVelocity, "y");
          if (ballVelocityY != NULL) {
            blueDataRecieve->data_ball_velocity_y = ballVelocityY->valueint;
          }
        }

      }//ball
    }//data
    aJsonObject* timestamp = aJson.getObjectItem(root, "timestamp");
    blueDataRecieve->timestamp = timestamp->valueint;
  }

  aJson.deleteItem(root);
	
	
}