//#include <Commands/AutoCommands/DriveOutsideOpp.h>
//
//#define DEFAULT_DIST 0
//#define DISTANCE_OFFSET 5
//
//DriveOutsideOpp::DriveOutsideOpp() {
//	Requires(robotDrive);
//	Requires(cube);
//	Initialize();
//}
//
//void DriveOutsideOpp::Initialize() {
//	for (int i = 0; i < 4; i++) {
//		dist[i] =  CommandBase::prefs->GetFloat(
//				"distance" + (i + DISTANCE_OFFSET), DEFAULT_DIST);
//	}
//	leftOrRight = oi->getGamePrefs();
//	turnAngle = -leftOrRight * robotDrive->autoTurnAngle;
//	state = -1;
//	IncrementState();
//}
//
//void DriveOutsideOpp::Execute() {
//	switch (state) {
//	case Startup:
//		if (cube->Pickup()) // returns true when finished
//			IncrementState();
//		break;
//	case DriveForwardOne:
//		if (robotDrive->encoderDistance() < dist[0]) {
//			Drive(robotDrive->autoDriveSpeed);
//		} else {
//			IncrementState();
//		}
//		break;
//	case TurnOne:
//		done = robotDrive->advancedTurnBot(robotDrive->autoTurnSpeed,
//				-turnAngle);
//		if (done) {
//			IncrementState();
//		}
//		break;
//	case DriveForwardTwo:
//		if (robotDrive->encoderDistance() < dist[1]) {
//			Drive(robotDrive->autoDriveSpeed);
//		} else {
//			IncrementState();
//		}
//		break;
//	case TurnTwo:
//		done = robotDrive->advancedTurnBot(robotDrive->autoTurnSpeed,
//				turnAngle);
//		if (done) {
//			IncrementState();
//		}
//		break;
//	case DriveForwardThree:
//		if (robotDrive->encoderDistance() < dist[2]) {
//			Drive(robotDrive->autoDriveSpeed);
//		} else {
//			IncrementState();
//		}
//		break;
//	case TurnThree:
//		done = robotDrive->advancedTurnBot(robotDrive->autoTurnSpeed,
//				turnAngle);
//		if (done) {
//			IncrementState();
//		}
//		break;
//	case DriveForwardFour:
//		if (robotDrive->encoderDistance() < dist[3]) {
//			Drive(robotDrive->autoTurnSpeed);
//		} else {
//			IncrementState();
//		}
//		break;
//	case DropCube: //drop cube
//		if (cube->Drop())
//			IncrementState();
//		break;
//	default:
//		End();
//	}
//
//}
//
//bool DriveOutsideOpp::IsFinished() {
//	return finished;
//}
//
//void DriveOutsideOpp::End() {
//	Drive(0);
//	finished = true;
//	timer.Stop();
//}
//
//void DriveOutsideOpp::Interrupted() {
//
//}
//
//void DriveOutsideOpp::IncrementState() {
//	state++;
//	timer.Reset();
//	timer.Start();
//	robotDrive->gyroReset();
//	robotDrive->encoderReset();
//}
//
//void DriveOutsideOpp::Drive(float speed) {
//	robotDrive->advancedDriveBot(speed, speed, 0);
//}
