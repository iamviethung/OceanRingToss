#ifndef _GAME_H_
#define _GAME_H_
#include "stdafx.h"
#include <vector>


class Camera;
class BSPLevel;
class Frustum;
class GUI;
class NFGObject;

class Game
{	
public:
	Game();		//constructor
	~Game();	//detructor	

	void		Init(int width, int height);
	//update and render function
	void		Update(float dt);
	void		Render();
	void		Exit();	

	void			setRunning(bool running = true);
	void			setPause(bool isPause = false);
	void			Replay();

	inline bool		isInit()	{	return m_isInit;	};
	inline bool		isRunning()	{	return m_isRunning;	};
	float PointToLineDistance(Vector3 A, Vector3 B, Vector3 P);
	Vector3 BulletToVector(const btVector3 &vechihi);
	Vector3 UnProject(Vector3 winCoord);
	void Input(int x, int y);
	bool is_TurnOff;
private:
	bool			m_isInit;
	bool			m_isRunning;
	bool			m_isPause;
	bool m_isPress;
};

#endif