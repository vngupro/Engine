/*
*  Asteroid revisited and max simplified
*/

#include <iostream>
#include <SDL.h>
#include <A4Engine/AnimationSystem.hpp>
#include <A4Engine/CameraComponent.hpp>
#include <A4Engine/ChipmunkBody.hpp>
#include <A4Engine/ChipmunkShape.hpp>
#include <A4Engine/ChipmunkSpace.hpp>
#include <A4Engine/CollisionShape.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/Model.hpp>
#include <A4Engine/PhysicsSystem.hpp>
#include <A4Engine/RenderSystem.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppImGui.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/SpritesheetComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/VelocityComponent.hpp>
#include <A4Engine/VelocitySystem.hpp>
#include <A4Engine/AudioSystem.hpp>
#include <A4Engine/Audio.hpp>
#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <AL/al.h>
#include <AL/alc.h>
//#include <dr_wav.h>
#include <../src/A4Engine/DrWavDefine.cpp>



entt::entity CreateBox(entt::registry& registry, std::shared_ptr<CollisionShape> shape);
entt::entity CreateCamera(entt::registry& registry);
entt::entity CreateHouse(entt::registry& registry);
entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet);
entt::entity CreatePlayer(entt::registry& registry);
entt::entity CreateBullet(entt::registry& registry);

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity);

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime);
void HandleRunnerMovement(entt::registry& registry, entt::entity runner, float deltaTime);
void HandlePlayerMovement(entt::registry& registry, entt::entity player, float deltaTime);

struct InputComponent
{
	bool left = false;
	bool right = false;
	bool jump = false;
	bool up = false;
	bool down = false;
	bool fire = false;
	bool rotateRight = false;
	bool rotateLeft = false;
};

struct PlayerControlled {};

void PlayerControllerSystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		//velocity.y = entityPhysics.GetLinearVelocity().y;

		if (entityInput.left)
			velocity.x -= 500.f;

		if (entityInput.right)
			velocity.x += 500.f;

		if (entityInput.jump && velocity.y < 1.f)
			velocity.y = -500.f;

		if (entityInput.up)
			velocity.y = -500.f;

		if (entityInput.down)
			velocity.y = 500.f;
		
		float angle = 0.f;
		
		if (entityInput.rotateLeft)
			angle += 400.f;

		if (entityInput.rotateRight)
			angle -= 400.0f;

		entityPhysics.SetLinearVelocity(velocity);
		entityPhysics.SetAngularVelocity(angle);
	}
}

void PlayerInputSystem(entt::registry& registry)
{
	auto view = registry.view<PlayerControlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.left = InputManager::Instance().IsActive("MoveLeft");
		entityInput.right = InputManager::Instance().IsActive("MoveRight");
		entityInput.jump = InputManager::Instance().IsActive("Jump");
		entityInput.up = InputManager::Instance().IsActive("MoveUp");
		entityInput.down = InputManager::Instance().IsActive("MoveDown");
		entityInput.fire = InputManager::Instance().IsActive("Fire");
		entityInput.rotateRight = InputManager::Instance().IsActive("RotateRight");
		entityInput.rotateLeft = InputManager::Instance().IsActive("RotateLeft");
	}
}

std::string GetError(int err)
{
	switch (err)
	{
	case AL_NO_ERROR: return "AL_NO_ERROR";
	case ALC_INVALID_DEVICE: return "AL_INVALID_DEVICE";
	case ALC_INVALID_CONTEXT: return "AL_INVALID_CONTEXT";
	//case AL_INVALID_ENUM: return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE: return "AL_INVALID_VALUE";
	case AL_OUT_OF_MEMORY: return "AL_OUT_OF_MEMORY";
	}

	return "unknown error";
}

int main()
{
	// Initialization
	SDLpp sdl;

	SDLppWindow window("A4Engine", 1280, 720);
	SDLppRenderer renderer(window, "direct3d11", SDL_RENDERER_PRESENTVSYNC);

	ResourceManager resourceManager(renderer);
	InputManager inputManager;

	SDLppImGui imgui(window, renderer);

	ImGui::SetCurrentContext(imgui.GetContext());
	entt::registry registry;

	AnimationSystem animSystem(registry);
	RenderSystem renderSystem(renderer, registry);
	VelocitySystem velocitySystem(registry);
	PhysicsSystem physicsSystem(registry);


	AudioSystem audioSystem(registry);
	std::shared_ptr<Audio> audio = ResourceManager::Instance().GetAudio("assets/siren.wav");
	//audioSystem.Play(audio);
	audio->Play();
	//audio.get()->Play();
	
	// Player Input
	InputManager::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_z, "MoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_s, "MoveDown");
	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "Fire");
	InputManager::Instance().BindKeyPressed(SDLK_e, "RotateRight");
	InputManager::Instance().BindKeyPressed(SDLK_a, "RotateLeft");

	// Camera Input
	InputManager::Instance().BindKeyPressed(SDLK_LEFT, "CameraMoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "CameraMoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_UP, "CameraMoveUp");
	InputManager::Instance().BindKeyPressed(SDLK_DOWN, "CameraMoveDown");

	entt::entity cameraEntity = CreateCamera(registry);
	entt::entity playerEntity = CreatePlayer(registry);
	registry.get<RigidBodyComponent>(playerEntity).TeleportTo(Vector2f(1280.f / 2.f, 720.f / 2.f));

	// Game Loop
	Uint64 lastUpdate = SDL_GetPerformanceCounter();
	bool isOpen = true;

	while (isOpen)
	{
		// Frame
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = (float) (now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

		// Event
		SDL_Event event;
		while (SDLpp::PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isOpen = false;

			imgui.ProcessEvent(event);

			InputManager::Instance().HandleEvent(event);
		}

		// Render
		imgui.NewFrame();
		renderer.SetDrawColor(0, 0, 0, 255);
		renderer.Clear();

		// Input
		HandleCameraMovement(registry, cameraEntity, deltaTime);
		HandlePlayerMovement(registry, playerEntity, deltaTime);

		// System Update
		animSystem.Update(deltaTime);
		velocitySystem.Update(deltaTime);
		physicsSystem.Update(deltaTime);
		renderSystem.Update(deltaTime);
		//audioSystem.Update(deltaTime);

		PlayerInputSystem(registry);
		PlayerControllerSystem(registry);

		ImGui::LabelText("FPS", "%f", 1.f / deltaTime);

		EntityInspector("Camera", registry, cameraEntity);
		
		physicsSystem.DebugDraw(renderer, registry.get<Transform>(cameraEntity).GetTransformMatrix().Inverse());
		imgui.Render();
		renderer.Present();
	}
	return 0;
}
//int main()
//{
//	SDLpp sdl;
//
//	SDLppWindow window("A4Engine", 1280, 720);
//	SDLppRenderer renderer(window, "direct3d11", SDL_RENDERER_PRESENTVSYNC);
//
//	ResourceManager resourceManager(renderer);
//	InputManager inputManager;
//
//	SDLppImGui imgui(window, renderer);
//
//	// Si on initialise ImGui dans une DLL (ce que nous faisons avec la classe SDLppImGui) et l'utilisons dans un autre exécutable (DLL/.exe)
//	// la bibliothèque nous demande d'appeler ImGui::SetCurrentContext dans l'exécutable souhaitant utiliser ImGui, avec le contexte précédemment récupéré
//	// Ceci est parce qu'ImGui utilise des variables globales en interne qui ne sont pas partagées entre la .dll et l'exécutable (comme indiqué dans sa documentation)
//	ImGui::SetCurrentContext(imgui.GetContext());
//
//	// ZQSD
//	InputManager::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
//	InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
//	InputManager::Instance().BindKeyPressed(SDLK_z, "MoveUp");
//	InputManager::Instance().BindKeyPressed(SDLK_s, "MoveDown");
//
//	// Touches directionnelles (caméra)
//	InputManager::Instance().BindKeyPressed(SDLK_LEFT, "CameraMoveLeft");
//	InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "CameraMoveRight");
//	InputManager::Instance().BindKeyPressed(SDLK_UP, "CameraMoveUp");
//	InputManager::Instance().BindKeyPressed(SDLK_DOWN, "CameraMoveDown");
//
//	std::shared_ptr<Spritesheet> spriteSheet = std::make_shared<Spritesheet>();
//	spriteSheet->AddAnimation("idle", 5, 0.1f, Vector2i{ 0, 0 },  Vector2i{ 32, 32 });
//	spriteSheet->AddAnimation("run",  8, 0.1f, Vector2i{ 0, 32 }, Vector2i{ 32, 32 });
//	spriteSheet->AddAnimation("jump", 4, 0.1f, Vector2i{ 0, 64 }, Vector2i{ 32, 32 });
//
//	entt::registry registry;
//
//	AnimationSystem animSystem(registry);
//	RenderSystem renderSystem(renderer, registry);
//	VelocitySystem velocitySystem(registry);
//	PhysicsSystem physicsSystem(registry);
//	physicsSystem.SetGravity({ 0.f, 981.f });
//	physicsSystem.SetDamping(0.9f);
//
//	entt::entity cameraEntity = CreateCamera(registry);
//
//	entt::entity house = CreateHouse(registry);
//	registry.get<RigidBodyComponent>(house).TeleportTo({ 750.f, 275.f });
//	registry.get<Transform>(house).SetScale({ 2.f, 2.f });
//
//	entt::entity runner = CreateRunner(registry, spriteSheet);
//	registry.get<Transform>(runner).SetPosition({ 300.f, 250.f });
//
//	std::shared_ptr<CollisionShape> boxShape = std::make_shared<BoxShape>(256.f, 256.f);
//	
//	entt::entity box = CreateBox(registry, boxShape);
//	registry.get<RigidBodyComponent>(box).TeleportTo({ 400.f, 400.f }, 15.f);
//
//	InputManager::Instance().BindKeyPressed(SDL_KeyCode::SDLK_r, "PlayRun");
//
//	InputManager::Instance().OnAction("PlayRun", [&](bool pressed)
//	{
//		if (pressed)
//		{
//			entt::entity box2 = CreateBox(registry, boxShape);
//			registry.get<RigidBodyComponent>(box2).TeleportTo({ 400.f, 400.f }, 15.f);
//
//			registry.get<SpritesheetComponent>(runner).PlayAnimation("run");
//		}
//		else
//			registry.get<SpritesheetComponent>(runner).PlayAnimation("idle");
//	});
//
//	// Création du sol
//	std::shared_ptr<CollisionShape> groundShape = std::make_shared<SegmentShape>(Vector2f(0.f, 720.f), Vector2f(10'000.f, 720.f));
//
//	entt::entity groundEntity = registry.create();
//	auto& groundPhysics = registry.emplace<RigidBodyComponent>(groundEntity, RigidBodyComponent::Static{});
//	groundPhysics.AddShape(groundShape);
//	
//	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "Jump");
//
//	Uint64 lastUpdate = SDL_GetPerformanceCounter();
//
//	bool isOpen = true;
//	while (isOpen)
//	{
//		Uint64 now = SDL_GetPerformanceCounter();
//		float deltaTime = (float) (now - lastUpdate) / SDL_GetPerformanceFrequency();
//		lastUpdate = now;
//
//		SDL_Event event;
//		while (SDLpp::PollEvent(&event))
//		{
//			if (event.type == SDL_QUIT)
//				isOpen = false;
//
//			imgui.ProcessEvent(event);
//
//			InputManager::Instance().HandleEvent(event);
//		}
//
//		imgui.NewFrame();
//
//		renderer.SetDrawColor(127, 0, 127, 255);
//		renderer.Clear();
//
//		HandleCameraMovement(registry, cameraEntity, deltaTime);
//		//HandleRunnerMovement(registry, runner, deltaTime);
//
//		animSystem.Update(deltaTime);
//		velocitySystem.Update(deltaTime);
//		physicsSystem.Update(deltaTime);
//		renderSystem.Update(deltaTime);
//
//		PlayerInputSystem(registry);
//		PlayerControllerSystem(registry);
//
//		ImGui::LabelText("FPS", "%f", 1.f / deltaTime);
//
//		EntityInspector("Box", registry, box);
//		EntityInspector("Camera", registry, cameraEntity);
//		EntityInspector("Runner", registry, runner);
//
//		physicsSystem.DebugDraw(renderer, registry.get<Transform>(cameraEntity).GetTransformMatrix().Inverse());
//
//		imgui.Render();
//
//		renderer.Present();
//	}
//
//	return 0;
//}

void EntityInspector(const char* windowName, entt::registry& registry, entt::entity entity)
{
	Transform& transform = registry.get<Transform>(entity);

	float rotation = transform.GetRotation();
	Vector2f pos = transform.GetPosition();
	Vector2f scale = transform.GetScale();

	ImGui::Begin(windowName);

	ImGui::LabelText("Position", "X: %f\nY: %f", pos.x, pos.y);

	if (ImGui::SliderFloat("Rotation", &rotation, -180.f, 180.f))
		transform.SetRotation(rotation);

	float scaleVal[2] = { scale.x, scale.y };
	if (ImGui::SliderFloat2("Scale", scaleVal, -5.f, 5.f))
		transform.SetScale({ scaleVal[0], scaleVal[1] });

	if (ImGui::Button("Reset"))
	{
		transform.SetScale({ 1.f, 1.f });
		transform.SetRotation(0.f);
		transform.SetPosition(Vector2f(0.f, 0.f));
	}

	ImGui::End();
}

entt::entity CreateBox(entt::registry& registry, std::shared_ptr<CollisionShape> shape)
{
	std::shared_ptr<Sprite> box = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/box.png"));
	box->SetOrigin({ 0.5f, 0.5f });

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(box));
	registry.emplace<Transform>(entity);

	auto& entityPhysics = registry.emplace<RigidBodyComponent>(entity, 250.f);
	entityPhysics.AddShape(std::move(shape));

	return entity;
}

entt::entity CreateCamera(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<CameraComponent>(entity);
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreateHouse(entt::registry& registry)
{
	std::shared_ptr<Model> house = ResourceManager::Instance().GetModel("assets/house.model");

	std::shared_ptr<CollisionShape> collider = std::make_shared<ConvexShape>(*house, Matrix3f::Scale({ 2.f, 2.f }));

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(house));
	registry.emplace<Transform>(entity);

	auto& entityPhysics = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Static{});
	entityPhysics.AddShape(std::move(collider));

	return entity;
}

entt::entity CreateRunner(entt::registry& registry, std::shared_ptr<Spritesheet> spritesheet)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/runner.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });
	sprite->Resize(256, 256);
	sprite->SetRect(SDL_Rect{ 0, 0, 32, 32 });

	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(128.f, 256.f);

	entt::entity entity = registry.create();
	registry.emplace<SpritesheetComponent>(entity, spritesheet, sprite);
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<PlayerControlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, 80.f, std::numeric_limits<float>::infinity());
	entityBody.AddShape(collider, Vector2f(0.f, 0.f), false);

	return entity;
}

entt::entity CreatePlayer(entt::registry& registry)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/ship.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });

	std::shared_ptr<CollisionShape> collider = std::make_shared<CircleShape>(16.f);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<PlayerControlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Kinematic{});
	entityBody.AddShape(collider, Vector2f(0.f, 0.f));

	return entity;
}

entt::entity CreateBullet(entt::registry& registry)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/bullet.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });

	std::shared_ptr<CollisionShape> collider = std::make_shared<BoxShape>(10.f, 50.f);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);

	return entity;
}

void HandleCameraMovement(entt::registry& registry, entt::entity camera, float deltaTime)
{
	Transform& cameraTransform = registry.get<Transform>(camera);

	if (InputManager::Instance().IsActive("CameraMoveDown"))
		cameraTransform.Translate(Vector2f(0.f, 500.f * deltaTime));

	if (InputManager::Instance().IsActive("CameraMoveLeft"))
		cameraTransform.Translate(Vector2f(-500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("CameraMoveRight"))
		cameraTransform.Translate(Vector2f(500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("CameraMoveUp"))
		cameraTransform.Translate(Vector2f(0.f, -500.f * deltaTime));
}

void HandlePlayerMovement(entt::registry& registry, entt::entity player, float deltaTime)
{
	Transform& transform = registry.get<Transform>(player);

	if (InputManager::Instance().IsActive("MoveDown"))
		transform.Translate(Vector2f(0.f, 500.f * deltaTime));

	if (InputManager::Instance().IsActive("MoveLeft"))
		transform.Translate(Vector2f(-500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("MoveRight"))
		transform.Translate(Vector2f(500.f * deltaTime, 0.f));

	if (InputManager::Instance().IsActive("MoveUp"))
		transform.Translate(Vector2f(0.f, -500.f * deltaTime));

	if (InputManager::Instance().IsActive("RotateRight"))
		transform.Rotate(50.f * deltaTime);

	if (InputManager::Instance().IsActive("RotateLeft"))
		transform.Rotate(-50.f * deltaTime);
	
	//if (InputManager::Instance().IsActive("Fire"))
	//	CreateBullet();

	//RigidBodyComponent& rb = registry.get<RigidBodyComponent>(player);

	//if (InputManager::Instance().IsActive("MoveDown"))
	//	rb.SetLinearVelocity(Vector2f(0.f, 50000.f * deltaTime));

	//if (InputManager::Instance().IsActive("MoveLeft"))
	//	rb.SetLinearVelocity(Vector2f(-50000.f * deltaTime, 0.f));

	//if (InputManager::Instance().IsActive("MoveRight"))
	//	rb.SetLinearVelocity(Vector2f(50000.f * deltaTime, 0.f));

	//if (InputManager::Instance().IsActive("MoveUp"))
	//	rb.SetLinearVelocity(Vector2f(0.f, -50000.f * deltaTime));

	//if(
	//	!InputManager::Instance().IsActive("MoveDown") && 
	//	!InputManager::Instance().IsActive("MoveLeft") && 
	//	!InputManager::Instance().IsActive("MoveRight") && 
	//	!InputManager::Instance().IsActive("MoveUp")
	//  )
	//	rb.SetLinearVelocity(Vector2f(0.f, 0.f));

	//if (InputManager::Instance().IsActive("RotateRight"))
	//	rb.SetAngularVelocity(400.f);

	//if (InputManager::Instance().IsActive("RotateLeft"))
	//	rb.SetAngularVelocity(-400.f);

	//if (
	//	!InputManager::Instance().IsActive("RotateRight") &&
	//	!InputManager::Instance().IsActive("RotateLeft")
	//   )
	//	rb.SetAngularVelocity(0.f);
}