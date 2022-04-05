#include "DarkScreenEffect.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Graphics/Framebuffer.h"

#include <GLM/glm.hpp>

DarkScreenEffect::DarkScreenEffect() :
	PostProcessingLayer::Effect()
{
	Name = "Dark Screen Effect";
	_format = RenderTargetType::ColorRgb8;

	memset(Filter, 0, sizeof(float) * 25);
	Filter[12] = 1.0f;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/dark_screen_effect.glsl" }
	});
}

DarkScreenEffect::~DarkScreenEffect() = default;

void DarkScreenEffect::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	_shader->SetUniform("u_Filter", Filter, 25);
	_shader->SetUniform("u_PixelSize", glm::vec2(1.0f) / (glm::vec2)gBuffer->GetSize());
}

void DarkScreenEffect::RenderImGui()
{/*
	ImGui::PushID(this);

	ImGui::Columns(5);
	for (int iy = 0; iy < 5; iy++) {
		for (int ix = 0; ix < 5; ix++) {
			ImGui::PushID(iy * 5 + ix);
			ImGui::PushItemWidth(-1);
			ImGui::InputFloat("", &Filter[iy * 5 + ix], 0.01f);
			ImGui::PopItemWidth();
			ImGui::PopID();
			ImGui::NextColumn();
		}
	}
	ImGui::Columns(1);

	if (ImGui::Button("Normalize")) {
		float sum = 0.0f;
		for (int ix = 0; ix < 25; ix++) {
			sum += Filter[ix];
		}
		float mult = sum == 0.0f ? 1 : sum;

		for (int ix = 0; ix < 25; ix++) {
			Filter[ix] /= mult;
		}
	}
	float* temp = ImGui::GetStateStorage()->GetFloatRef(ImGui::GetID("###temp-filler"), 0.0f);
	ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() * 0.75f);
	ImGui::InputFloat("", temp, 0.1f);
	ImGui::PopItemWidth();

	ImGui::SameLine();

	if (ImGui::Button("Fill")) {
		for (int ix = 0; ix < 25; ix++) {
			Filter[ix] = *temp;
		}
	}

	ImGui::PopID();
	*/
}

DarkScreenEffect::Sptr DarkScreenEffect::FromJson(const nlohmann::json & data)
{
	DarkScreenEffect::Sptr result = std::make_shared<DarkScreenEffect>();
	//result->Enabled = JsonGet(data, "enabled", true);
	//std::vector<float> filter = JsonGet(data, "filter", std::vector<float>(25, 0.0f));
	//for (int ix = 0; ix < 25; ix++) {
	//	result->Filter[ix] = filter[ix];
	//}
	return result;
}

nlohmann::json DarkScreenEffect::ToJson() const
{
	//std::vector<float> filter;
	//for (int ix = 0; ix < 25; ix++) {
	//	filter.push_back(Filter[ix]);
	//}
	return {
	//	{ "enabled", Enabled },
	//	{ "filter", filter }
	};
}
