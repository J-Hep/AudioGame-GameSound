#include "Gameplay/Components/MovementBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"


void MovementBehaviour::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void MovementBehaviour::RenderImGui()
{
	return;
}

nlohmann::json MovementBehaviour::ToJson() const
{
	return {
		{ "impulse", _force }
	};
}

MovementBehaviour::MovementBehaviour() :
	IComponent(), _force(0.5f)
{
}

MovementBehaviour::~MovementBehaviour() = default;

MovementBehaviour::Sptr MovementBehaviour::FromJson(const nlohmann::json& blob)
{
	MovementBehaviour::Sptr result = std::make_shared<MovementBehaviour>();
	result->_force = blob["impulse"];
	return result;
}

void MovementBehaviour::Update(float deltaTime)
{
	_body->SetAngularVelocity(glm::vec3(0.0f));
	_body->SetLinearDamping(0.9f);

	if (InputEngine::GetKeyState(GLFW_KEY_W) == ButtonState::Down)
	{
		_body->ApplyImpulse(glm::vec3(_force, 0.0f, 0.0f));		
	}
	else if (InputEngine::GetKeyState(GLFW_KEY_S) == ButtonState::Down)
	{
		_body->ApplyImpulse(glm::vec3(-_force, 0.0f, 0.0f));		
	}

	if (InputEngine::GetKeyState(GLFW_KEY_A) == ButtonState::Down)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, _force, 0.0f));		
	}
	else if (InputEngine::GetKeyState(GLFW_KEY_D) == ButtonState::Down)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, -_force, 0.0f));
	}
}