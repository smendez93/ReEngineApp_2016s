#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//used for non timer based rotation
	/*/Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences */

	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock

#pragma endregion
#pragma region YOUR CODE GOES HERE
	//m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

#pragma region ROTATION USING GLM ROTATE
	/*
	float fStartTime = 0.0f;
	float fEndTime = 5.0f;
	float fAngle = MapValue(static_cast<float>(dTotalTime), fStartTime, fEndTime, 0.0f, 360.0f);
	m_m4Steve = glm::rotate(IDENTITY_M4, fAngle, REAXISZ);

	static float fStartHeight = 0.0f;
	static float fEndHeight = 5.0f;
	float fPercent = MapValue(static_cast<float>(dTotalTime), fStartTime, fEndTime, 0.0f, 1.0f);
	float fHeight = glm::lerp(fStartHeight, fEndHeight, fPercent);
	m_m4Steve = m_m4Steve * glm::translate(vector3(0.0f, fHeight, 0.0f));
	if (fPercent > 1.0f)
	{
		std::swap(fStartHeight, fEndHeight);
		dTotalTime = 0.0;
	}*/
#pragma endregion 
#pragma region ROTATION USING QUARTERNIONS
	//Setting up the start and end position vectors
	static vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	static vector3 v3End = vector3(0.0f, 3.0f, 0.0f);
	
	//Creating the percentage by which the model will move each frame
	float fPercentage = MapValue(fTimer, 0.0f, 2.0f, 0.0f, 1.0f);

	//rotation via quarternions- 2 full rotations along the z-axis
	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f)); //angle of the starting rotation along the z-axis
	quaternion q2 = glm::angleAxis(180.0f, REAXISZ); //angle of final rotation along the z-axis
	quaternion q3 = glm::mix(q1, q2, fPercentage); // get the interpolation between these two points

	//Translation
	vector3 v3Current = glm::lerp(v3Start, v3End, fPercentage);

	//apply matrices to model translate then rotate 
	m_m4Steve = glm::translate(m_m4Steve, v3Current) * ToMatrix4(q3); //toMatrix4 converts the quaternion q3 into a 4x4 matrix

	if (fPercentage > 1.0)
	{
		fTimer = 0.0f;
		std::swap(v3Start, v3End);
	}
#pragma endregion
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	//m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
