#pragma once

#include "BaseScene.h"

#include <string>
/// <summary>
/// �V�[���H��i�T�O�j
/// </summary>
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;

	/// <summary>
	/// �V�[������
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	/// <returns>���������V�[��</returns>
	virtual BaseScene* CreateScene(const std::string& sceneName) = 0;
};

