#include "GamePCH.h"

#include "Events/GameEventTypes.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"
#include "Game/ImguiManager.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"


#include <time.h>

Game::Game(Framework* pFramework)
: GameCore( pFramework, new EventManager() )
{
    m_pImGuiManager = nullptr;
    m_Resource = nullptr;
    m_SceneManager = new SceneManager();;
    m_Debug = true;
    m_F9Current = false;
    m_F9Previous = false;
    m_GameOver = false;
    m_MainMenu = true;
    m_Score = 0;
}

Game::~Game()
{
    delete m_pImGuiManager;
    delete m_Resource;
    delete m_SceneManager;

    m_pImGuiManager = nullptr;
    m_Resource = nullptr;
    m_SceneManager = nullptr;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport( 0, 0, width, height );
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval( 1 );
#endif

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Enable back-face culling.
    //glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CW );

    // Create an ImGui object.
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    //Create Resource Manager
    m_Resource = new ResourceManager();

    //Shaders
    {
        m_Resource->AddShader("Texture", new ShaderProgram("Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag"));
        m_Resource->AddShader("Plain", new ShaderProgram("Data/Shaders/TextureOriginal.vert", "Data/Shaders/TextureOriginal.frag"));
    }

    //Textures
    {
        m_Resource->AddTexture("Megaman", new Texture("Data/Textures/Megaman.png"));
        m_Resource->AddTexture("LowPoly", new Texture("Data/Textures/lowpoly.png"));
        m_Resource->AddTexture("Lava", new Texture("Data/Textures/lava.png"));
        m_Resource->AddTexture("Water", new Texture("Data/Textures/water.png"));
        m_Resource->AddTexture("Rock", new Texture("Data/Textures/rock.png"));
        m_Resource->AddTexture("MainMenu", new Texture("Data/Textures/MainMenu.png"));
        m_Resource->AddTexture("EndGame", new Texture("Data/Textures/EndGame.png"));
        //All number textures ( should be one texture atlas but rushing)
        m_Resource->AddTexture("0", new Texture("Data/Textures/0.png"));
        m_Resource->AddTexture("1", new Texture("Data/Textures/1.png"));
        m_Resource->AddTexture("2", new Texture("Data/Textures/2.png"));
        m_Resource->AddTexture("3", new Texture("Data/Textures/3.png"));
        m_Resource->AddTexture("4", new Texture("Data/Textures/4.png"));
        m_Resource->AddTexture("5", new Texture("Data/Textures/5.png"));
        m_Resource->AddTexture("6", new Texture("Data/Textures/6.png"));
        m_Resource->AddTexture("7", new Texture("Data/Textures/7.png"));
        m_Resource->AddTexture("8", new Texture("Data/Textures/8.png"));
        m_Resource->AddTexture("9", new Texture("Data/Textures/9.png"));
    }

    //Materials
    {
        m_Resource->AddMaterial("Megaman", new Material(m_Resource->GetShader("Texture"), m_Resource->GetTexture("LowPoly")));
        m_Resource->AddMaterial("Water", new Material(m_Resource->GetShader("Texture"), m_Resource->GetTexture("Water")));
        m_Resource->AddMaterial("Lava", new Material(m_Resource->GetShader("Texture"), m_Resource->GetTexture("Lava")));
        m_Resource->AddMaterial("Rock", new Material(m_Resource->GetShader("Texture"), m_Resource->GetTexture("Rock")));
        m_Resource->AddMaterial("MainMenu", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("MainMenu")));
        m_Resource->AddMaterial("EndGame", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("EndGame")));
        //Named the same thing as the int so we can quickly convert int to string and get material
        m_Resource->AddMaterial("0", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("0")));
        m_Resource->AddMaterial("1", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("1")));
        m_Resource->AddMaterial("2", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("2")));
        m_Resource->AddMaterial("3", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("3")));
        m_Resource->AddMaterial("4", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("4")));
        m_Resource->AddMaterial("5", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("5")));
        m_Resource->AddMaterial("6", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("6")));
        m_Resource->AddMaterial("7", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("7")));
        m_Resource->AddMaterial("8", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("8")));
        m_Resource->AddMaterial("9", new Material(m_Resource->GetShader("Plain"), m_Resource->GetTexture("9")));
    }

    LoadMainMenu();

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );

    if( pEvent->GetEventType() == GameEventType_RemoveFromScene )
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = static_cast<RemoveFromSceneEvent*>( pEvent );

        Scene* pScene = pRemoveFromSceneEvent->GetScene();
        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();
       
    }

    //m_pActiveScene->OnEvent( pEvent );

#if WIN32
    // Enable/Disable V-Sync with F1 and F2.
    if( pEvent->GetEventType() == EventType_Input )
    {
        InputEvent* pInput = static_cast<InputEvent*>( pEvent );

        // Enable V-Sync.
        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F1 )
            wglSwapInterval( 1 );

        // Disable V-Sync.
        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F2 )
            wglSwapInterval( 0 );

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F9)
            m_F9Current = true;

        // Reset active scene.
        //if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'R' )
          //  m_pActiveScene->Reset();
    }
#endif //WIN32
}

void Game::Update(float deltaTime)
{
    // Once our events are processed, tell ImGui we're starting a new frame.
    m_pImGuiManager->StartFrame( (float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime );

   // if (m_F9Current && m_F9Previous == false)
      //  m_Debug = !m_Debug;

    if (m_pFramework->WasKeyPressed('P'))
    {
        //DEBUG_IMGUI = !DEBUG_IMGUI;
        m_Debug = !m_Debug;
    }

    if (m_pFramework->WasKeyPressed('R') && !m_MainMenu)
    {
        Reset();
        m_Score = 0;
    }

    if (m_pFramework->IsMouseButtonDown(0) && m_MainMenu)
    {
        m_MainMenu = false;
        Reset();
    }
    if (m_GameOver)
    {
        m_GameOver = false;
        LoadGameOver();
    }

    m_SceneManager->Update(deltaTime, (m_Debug));
    m_SceneManager->LateUpdate(deltaTime);

    //m_F9Previous = m_F9Current;
    //m_F9Current = false;
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // (red, green, blue, alpha) - dark blue.
#if WIN32
    glClearDepth( 1 ); // 1 is maximum depth.
#endif
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_SceneManager->Draw();

    // Tell imgui we're at the end of our frame, so it will draw all queued objects.
    m_pImGuiManager->EndFrame();

    CheckForGLErrors();
}

void Game::Reset()
{
    LoadGame();
}

void Game::LoadMainMenu()
{
    delete m_SceneManager;
    m_SceneManager = new SceneManager();
    m_SceneManager->SetGame(this);
    Scene* mainMenu = new Scene(1, "MainMenu");
    m_SceneManager->AddNewScene(mainMenu, true);

    GameObject* cameraGo = new GameObject("Camera", "Camera");
    CameraComponent* cameraComponent = new CameraComponent(cameraGo, m_pFramework);
    mainMenu->SetMainCamera(cameraComponent);
    mainMenu->AddGameObject(cameraGo);
    //Even tho we don't use lighting for menus we still need a light manager;
    LightManager* lightManager = new LightManager(Vector3(0.1f, 0.1f, 0.1f), 1);
    mainMenu->SetLightManager(lightManager);

    //Create gameobject to  display game over
    {
        GameObject* tempGO = new GameObject("MainMenu", "UI");
        mainMenu->AddGameObject(tempGO);
        tempGO->transform()->Scale(Vector3(2, 2, 2));
        SquareComponent* sc = new SquareComponent(tempGO, m_Resource->GetMaterial("MainMenu"), lightManager);
        sc->camera(cameraComponent);

        FollowBehaviour* followBehaviour = new FollowBehaviour(cameraGo, tempGO->transform());
        followBehaviour->SetOffset(Vector3(0.0f, 0.0f, -2.0f));
    }

    m_SceneManager->Start();
}

void Game::LoadGameOver()
{
    delete m_SceneManager;
    m_SceneManager = new SceneManager();
    m_SceneManager->SetGame(this);
    Scene* endGame = new Scene(1, "End");
    m_SceneManager->AddNewScene(endGame, true);

    GameObject* cameraGo = new GameObject("Camera", "Camera");
    CameraComponent* cameraComponent = new CameraComponent(cameraGo, m_pFramework);
    endGame->SetMainCamera(cameraComponent);
    endGame->AddGameObject(cameraGo);
    //Even tho we don't use lighting for menus we still need a light manager;
    LightManager* lightManager = new LightManager(Vector3(0.1f, 0.1f, 0.1f), 1);
    endGame->SetLightManager(lightManager);

    //Create gameobject to  display game over
    {
        GameObject* tempGO = new GameObject("EndGame", "UI");
        endGame->AddGameObject(tempGO);
        tempGO->transform()->Scale(Vector3(2, 2, 2));
        SquareComponent* sc = new SquareComponent(tempGO, m_Resource->GetMaterial("EndGame"), lightManager);
        sc->camera(cameraComponent);

        FollowBehaviour* followBehaviour = new FollowBehaviour(cameraGo, tempGO->transform());
        followBehaviour->SetOffset(Vector3(0.0f, 0.0f, -2.0f));
    }

    m_SceneManager->Start();
}

void Game::LoadGame()
{
    delete m_SceneManager;

    m_SceneManager = new SceneManager();
    m_SceneManager->SetGame(this);
    {
        //Create main scene, lowest weight possible to always draw game behind UI
        Scene* tempScene = new Scene(1, "Game");
        m_SceneManager->PushScene(tempScene);

        GameObject* cameraGo = new GameObject("Camera", "Camera");
        CameraComponent* cameraComponent = new CameraComponent(cameraGo, m_pFramework);
        tempScene->SetMainCamera(cameraComponent);
        tempScene->AddGameObject(cameraGo);

        LightManager* lightManager = new LightManager(Vector3(0.1f, 0.1f, 0.1f), 1);
        tempScene->SetLightManager(lightManager);

        //Create lights (can handle 10, but using 2 to not lag)
        for (int i = 0; i < 2; i++)
        {
            GameObject* tempLight = new GameObject("Light_Test", "Light");
            tempLight->transform()->Position(Vector3(2, 100 * i, 2));
            Light* tempLightComp = new Light(tempLight, Vector3(1, 1, 1), 0.2f);
            tempLightComp->SetGame(this);
            lightManager->AddLight(tempLightComp);
            tempScene->AddGameObject(tempLight);
        }

        //Create player
        GameObject* tempGO = new GameObject("Player", "Player");
        {
            tempScene->AddGameObject(tempGO);
            tempGO->transform()->Position(Vector3(9.0f, 3.0f, 6.0f));

            CubeComponent* cube = new CubeComponent(tempGO, m_Resource->GetMaterial("Megaman"), lightManager);
            cube->camera(cameraComponent);

            FollowBehaviour* followBehaviour = new FollowBehaviour(cameraGo, tempGO->transform());

            Rigidbody* rb = new Rigidbody(tempGO);
            rb->CreateBody(tempScene->GetPhysics()->GetWorld(), 0.01f, Vector3(0.5f, 0.5f, 0.5f));
            rb->FreezeRotation(true);
            rb->MaxLinearVelocity(Vector3(10, 2, 10));

            PlayerBehaviour* playerBehaviour = new PlayerBehaviour(tempGO, m_pFramework);
        }

        //Create spiral tower
        for (int i = 0; i < 200; i++)
        {
            float theta = 2.0f * 3.1415926f * float(i) / 20.0f;

            float x = 10.0f * cosf(theta);
            float y = -5.0f + (i * 2.5f);
            float z = 10.0f * sinf(theta);

            GameObject* floor = new GameObject("Floor", "World");
            //floor->transform()->Position(Vector3(0.0f, -5.0f, i * -6.0f));
            floor->transform()->Position(Vector3(x, y, z));
            floor->transform()->Scale(Vector3(2.0f, 2.0f, 2.0f));
            CubeComponent* cubeFloor = new CubeComponent(floor, m_Resource->GetMaterial("Rock"), lightManager);
            cubeFloor->camera(cameraComponent);
            Rigidbody* rbFloor = new Rigidbody(floor);
            rbFloor->CreateBody(tempScene->GetPhysics()->GetWorld(), 0.0f, Vector3(1.0f, 1.0f, 1.0f));
            rbFloor->SetFriction(1.1f);

            tempScene->AddGameObject(floor);
        }

        //Create collectabls
        for (int i = 1; i < 200; i++)
        {
            //Only put collectables on every 5 steps
            if ((i % 3) != 0)
                continue;

            float theta = 2.0f * 3.1415926f * float(i) / 20.0f;

            float x = 10.0f * cosf(theta);
            float y = -5.0f + (i * 2.5f) + 5;
            float z = 10.0f * sinf(theta);

            GameObject* heart = new GameObject("Heart", "Collectable");
            OBJComponent* heartObj = new OBJComponent(heart, m_Resource->GetMaterial("Water"), "Data/OBJs/sphere.obj", lightManager);
            heart->transform()->Position(Vector3(x, y, z));
            heart->transform()->Scale(Vector3(0.3f, 0.3f, 0.3f));
            Collectable* collectable = new Collectable(heart, 1.0f, tempGO->transform(), this);
            heartObj->camera(cameraComponent);

            srand(time(NULL));
            int tweenFunction = std::rand() % 9;

            if (tweenFunction == 0)
                collectable->SetTweenFunction(TweenFunc_Linear);
            else if (tweenFunction == 1)
                collectable->SetTweenFunction(TweenFunc_SineEaseIn);
            else if (tweenFunction == 2)
                collectable->SetTweenFunction(TweenFunc_SineEaseOut);
            else if (tweenFunction == 3)
                collectable->SetTweenFunction(TweenFunc_SineEaseInOut);
            else if (tweenFunction == 4)
                collectable->SetTweenFunction(TweenFunc_BounceEaseIn);
            else if (tweenFunction == 5)
                collectable->SetTweenFunction(TweenFunc_BounceEaseOut);
            else if (tweenFunction == 6)
                collectable->SetTweenFunction(TweenFunc_BounceEaseInOut);
            else if (tweenFunction == 7)
                collectable->SetTweenFunction(TweenFunc_ElasticEaseIn);
            else if (tweenFunction == 8)
                collectable->SetTweenFunction(TweenFunc_ElasticEaseOut);
            else if (tweenFunction == 9)
                collectable->SetTweenFunction(TweenFunc_ElasticEaseInOut);

            tempScene->AddGameObject(heart);
        }
        //Create lava
        {
            GameObject* lava = new GameObject("Lava", "World");
            //PlaneComponent* plane = new PlaneComponent(lava, m_Resource->GetMaterial("Lava"), lightManager);
            CubeComponent* cube = new CubeComponent(lava, m_Resource->GetMaterial("Lava"), lightManager);
            cube->camera(cameraComponent);

            RiseComponent* aRise = new RiseComponent(lava, 1.0f, this, tempGO->transform());

            lava->transform()->Position(Vector3(6, -5.0f, 6.0f));
            lava->transform()->Scale(Vector3(200, 0.1f, 200));
            tempScene->AddGameObject(lava);
        }

        //Score Screen
        {
            //higher weight to draw abive gane
            Scene* score = new Scene(100, "score");
            m_SceneManager->PushScene(score);

            GameObject* cameraGo = new GameObject("Camera", "Camera");
            CameraComponent* cameraComponent = new CameraComponent(cameraGo, m_pFramework);
            score->SetMainCamera(cameraComponent);
            score->AddGameObject(cameraGo);
            //Even tho we don't use lighting for menus we still need a light manager;
            LightManager* lightManager = new LightManager(Vector3(0.1f, 0.1f, 0.1f), 1);
            score->SetLightManager(lightManager);

            GameObject* scoreManager = new GameObject("Score", "Score");
            score->AddGameObject(scoreManager);

            ScoreManager* sm = new ScoreManager(scoreManager, m_Resource, this);

            FollowBehaviour* followBehaviour = new FollowBehaviour(cameraGo, scoreManager->transform());
            followBehaviour->SetOffset(Vector3(0.0f, 0.0f, -2.0f));

            //Create gameobject to  display game over
            for(int i = 0; i < 4; i++)
            {
                GameObject* tempGO = new GameObject("gameUI", "UI");
                score->AddGameObject(tempGO);
                tempGO->transform()->Scale(Vector3(0.5f, 0.5f, 0.5f));
                tempGO->transform()->Position(Vector3(-0.7 + (i * 0.25f), 0.7, 0));
                SquareComponent* sc = new SquareComponent(tempGO, m_Resource->GetMaterial("0"), lightManager);
                sc->camera(cameraComponent);

                sm->AddQuad(sc);
            }
        }
        m_SceneManager->Start();
    }
}