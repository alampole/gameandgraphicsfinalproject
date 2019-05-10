#ifndef __GamePCH_H__
#define __GamePCH_H__

#include "../../Libraries/Framework/Source/FrameworkPCH.h"

#include "../../Libraries/Box2D/Box2D/Box2D.h"


//ENGINE INCLUDES

//AUDIO
#include "../Engine/Audio/SoundChannel.h"
#include "../Engine/Audio/SoundObject.h"
#include "../Engine/Audio/SoundPlayer.h"
#include "../Engine/Audio/VoiceCallback.h"
#include "../Engine/Audio/WaveLoader.h"

//BASE COMPONENTS
#include "../Engine/Component/BehaviourComponent.h"
#include "../Engine/Component/Transform.h"
#include "../Engine/Component/Camera/CameraComponent.h"
#include "../Engine/Component/Light/Light.h"
//BASIC BEHAVIOUR COMPONENT
#include "../Engine/Component/Behaviour/FollowBehaviour.h"
#include "../Engine/Component/Behaviour/PlayerBehaviour.h"
//GAMEOBJECT
#include "../Engine/GameObject/GameObject.h"
//SCENE
#include "../Engine/Scene/Scene.h"
#include "../Engine/Scene/SceneManager.h"
//BULLET
#include "../Engine/Bullet/BulletManager.h"
#include "../Engine/Bullet/Component/Rigidbody.h"
#include "../Engine/Bullet/MotionState.h"
//MESH COMPONENTS
#include "../Engine/Mesh/Component/MeshComponent.h"
#include "../Engine/Mesh/Component/CubeComponent.h"
#include "../Engine/Mesh/Component/PlaneComponent.h"
#include "../Engine/Mesh/Component/OBJComponent.h"
#include "../Engine/Mesh/SquareComponent.h"
//MANGERS
#include "../Engine/Game/ResourceManager.h"
#include "../Engine/Game/LightManager.h"
#include "../Engine/EngineHelper.h"
//GAME INCLUDES 
#include "Mesh/Mesh.h"
#include "Mesh/Material.h"

#include "Component/Collectable.h"
#include "Component/RiseComponent.h"
#include "Component/ScoreManager.h"
#include "Helpers/TweenFuncs.h"

#if ANDROID
#include "android_native_app_glue.h"
#include "UtilityAndroid.h"
#endif

#endif //__GamePCH_H__
