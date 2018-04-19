# RCJ-Soccer-StandardMessage
This is a proposal for a standard message in RoboCupJunior Soccer.

##Protocol
JSON-based
```
{
  "header": "RCJ Soccer Open",
  "version": "1.0",
  "data": {
    "teamNumber": 1,
    "teamID": 1,
    "robot": {
      "number": 1,
      "position": {
        "x": 0,
        "y": 0,
        "z": 0
      },
      "velocity": {
        "x": 0,
        "y": 0
      },
      "status": 0,
      "role": 0,
      "intention": 0,
      "suggestion": [
        0,
        0,
        0,
        0,
        0
      ]
    },
    "ball": {
      "has": 0,
      "age": 0,
      "position": {
        "x": 0,
        "y": 0
      },
      "velocity": {
        "x": 0,
        "y": 0
      }
    }
  },
  "timestamp": 0,
  "customData": {}
}
```

##Description

teamNumber - 1(home team) and 2(guest team)
teamID - choosen by each team, has to be unique
robot:number - choosen in each game, similar to marker on robots
robot:position:x - absolute position on the field in mm
robot:position:y - absolute position on the field in mm
robot:position:z - in degree (-180 to 180)
robot:velocity:x - in mm/s
robot:velocity:y - in mm/s
robot:status - 0(not playing), 1(playing)
robot:role - 0(don't know), 1(goalie), 2(defender), 3(midfielder), 4(striker)
robot:intention - see robot:role
robot:suggestion - see robot:role, suggest each robot which role it should take
ball:has - in ms, how long the robot has the ball in his own control
ball:age - in ms, how long the robot sees the ball, 0(saw no ball) everthing greater indicates robot sees the ball
ball:position:x - relative position to the robot in mm
ball:position:y - relative position to the robot in mm
ball:velocity:x - in mm/s
ball:velocity:y - in mm/s
timestamp - time since kickoff started
customData - up to yourself :)

##Contribution

Feel free to do change requests or add a new example based on other libraries or platforms.

##Thanks

Thanks to the RoboCup SPL Community. This protocol is based on their approach.
https://github.com/bhuman/GameController/blob/master/include/SPLStandardMessage.h
