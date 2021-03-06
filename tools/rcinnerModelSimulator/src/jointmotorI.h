/*
 *    Copyright (C) 2006-2010 by RoboLab - University of Extremadura
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef JOINTMOTORI_H
#define JOINTMOTORI_H

// Qt includes
#include <QMutex>
#include <QObject>

// RoboComp includes
#include <Ice/Ice.h>
#include <JointMotor.h>
#include <innermodel/innermodel.h>

// Simulator includes
#include "config.h"

class SpecificWorker;
using namespace RoboCompJointMotor;

class JointMotorI : public QObject , public virtual RoboCompJointMotor::JointMotor
{
	Q_OBJECT
public:
	JointMotorI(std::shared_ptr<SpecificWorker> _worker, QObject *parent = 0);
	~JointMotorI();
	
	void add(QString id);
	void remove(QString id);
	
	void setPosition(const RoboCompJointMotor::MotorGoalPosition& goal, const Ice::Current & = Ice::Current());
	void setVelocity(const RoboCompJointMotor::MotorGoalVelocity& goal, const Ice::Current & = Ice::Current());
	void setSyncPosition(const RoboCompJointMotor::MotorGoalPositionList& listGoals, const Ice::Current & = Ice::Current());
	void setSyncVelocity(const RoboCompJointMotor::MotorGoalVelocityList& listGoals, const Ice::Current & = Ice::Current());
	RoboCompJointMotor::MotorParams getMotorParams(const std::string& motor, const Ice::Current & = Ice::Current());
	RoboCompJointMotor::MotorState getMotorState(const std::string& motor, const Ice::Current & = Ice::Current());
	RoboCompJointMotor::MotorStateMap getMotorStateMap(const RoboCompJointMotor::MotorList& mList, const Ice::Current & = Ice::Current());
	void getAllMotorState(MotorStateMap& mstateMap, const Ice::Current & = Ice::Current());
	RoboCompJointMotor::MotorParamsList getAllMotorParams(const Ice::Current & = Ice::Current());
	RoboCompJointMotor::BusParams getBusParams(const Ice::Current & = Ice::Current());
	
	void setZeroPos(const std::string&, const Ice::Current&) {}
	void setSyncZeroPos(const Ice::Current&) {}
	
	void stopAllMotors(const Ice::Current&) {}
	void stopMotor(const std::string&, const Ice::Current&) {}
	void releaseBrakeAllMotors(const Ice::Current&) {}
	void releaseBrakeMotor(const std::string&, const Ice::Current&) {}
	void enableBrakeAllMotors(const Ice::Current&) {}
	void enableBrakeMotor(const std::string&, const Ice::Current&) {}
	
private:
	std::shared_ptr<SpecificWorker> worker;
	QStringList jointIDs;
	
	MotorParamsList params;
	MotorStateMap states;
	BusParams busparams;
};

#endif
