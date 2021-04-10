#include "GameWorld.h"

GameWorld::GameWorld(std::shared_ptr<Renderer>& render)
{
	_render = render;

}

void GameWorld::Initialize()
{
	const glm::vec3 lightSize = glm::vec3(0.5, 0.5, 0.5);
	const glm::vec3 lightColor = glm::vec3(1.0, 1.0, 1.0);

	// Add point lights to the scene as physical objects for debugging purposes.
	for (auto& pointLight : pointLights)
	{
		auto* lightCube = new ColoredBox();
		lightCube->ambient_color = lightColor;
		lightCube->Scale(lightSize);
		lightCube->Translate(pointLight.position);

		_debugLights.push_back(lightCube);
	}

	// Add directional light to the scene as physical objects for debugging purposes.
	auto* lightCube = new ColoredBox();
	lightCube->ambient_color = glm::vec3(0.2f, 1.0f, 0.2f);
	lightCube->Scale(lightSize);
	lightCube->Translate(_render->LightPosition());
	_debugLights.push_back(lightCube);

	shadowMap.Initialize();
}

void GameWorld::AddBPRShape(ShapeBase& shape)
{
	_pbrShapes.push_back(&shape);
}

void GameWorld::AddShadowShape(ShapeBase& shape)
{
    _shadowShapes.push_back(&shape);
}

void GameWorld::AddObjectShape(ShapeBase& shape)
{
    _objectShapes.push_back(&shape);
}

Camera* GameWorld::MainCamera() const
{
	return _render->camera.get();
}

void GameWorld::Render()
{
    Graphics graphics;
    graphics.Render = _render.get();
    graphics.directionalLight = &directionalLight;
    graphics.spotLight = &spotLight;
    graphics.pointLights = &pointLights;
    	
    RenderShadowShapes(&graphics);
    RenderPBRShapes(&graphics);
    DrawObjectShapes(&graphics);
    DrawDebugLights(&graphics);
}

void GameWorld::DrawDebugLights(Graphics* graphics)
{
    Shader* objectShader = ShaderPool::Instance()->GetShaderById(object_no_texture_shaderID);
    objectShader->Bind();
    objectShader->SetUniformMatrix4fv("projection", _render->CameraProjection());
    objectShader->SetUniformMatrix4fv("view", _render->CameraView());
    graphics->activeShader = objectShader;

    for (auto& _debugLight : _debugLights)
    {
	    _debugLight->Bind();
	    _debugLight->Draw(graphics);
	    _debugLight->Unbind();
    }	
}

void GameWorld::DrawObjectShapes(Graphics* graphics)
{
    Shader* objectShader = ShaderPool::Instance()->GetShaderById(object_shaderID);
    objectShader->Bind();
    objectShader->SetUniformMatrix4fv("projection", _render->CameraProjection());
    objectShader->SetUniformMatrix4fv("view", _render->CameraView());

    graphics->activeShader = objectShader;

    for (int i = 0; i < _objectShapes.size(); i++)
    {
        objectShader->SetUniform3fv("lightPos", _render->LightPosition());

        auto* texture = TexturePool::Instance()->GetSimpleTextureById(_objectShapes[i]->TextureIdentifier);
        texture->Bind();
        _objectShapes[i]->Bind();
        _objectShapes[i]->Draw(graphics);
        _objectShapes[i]->Unbind();
        texture->Unbind();
    }	
}

void GameWorld::RenderPBRShapes(Graphics* graphics)
{
    Shader* pbrShader = ShaderPool::Instance()->GetShaderById(pbr_shaderID);
    pbrShader->Bind();
	
    graphics->ApplyLightsToShader(pbrShader);
    pbrShader->SetUniformMatrix4fv("projection", _render->CameraProjection());
    pbrShader->SetUniformMatrix4fv("view", _render->CameraView());
    pbrShader->SetUniform3fv("viewPos", _render->camera->position);
    pbrShader->SetUniform3fv("lightPos", _render->LightPosition());
    
    for (int i = 0; i < _pbrShapes.size(); i++)
    {
        auto* texture = TexturePool::Instance()->GetPBRById(_pbrShapes[i]->TextureIdentifier);
        texture->Bind();
        _pbrShapes[i]->Bind();
        _pbrShapes[i]->Draw(graphics);
        _pbrShapes[i]->Unbind();
        texture->Unbind();
    }
}

void GameWorld::RenderShadowShapes(Graphics* graphics)
{	
	// Start pass
    shadowMap.StartShadowMapPass(graphics->Render);

    graphics->activeShader = shadowMap.shadowShader;

    RenderShadowScene(graphics);

    shadowMap.EndShadowMapPass();

    // Scene Pass
	
    shadowMap.StartScenePass(GL_TEXTURE1);
	
    Shader* shadowMapShader = ShaderPool::Instance()->GetShaderById(shadow_passtrough_shaderID);
    shadowMapShader->Bind();
    	
    shadowMapShader->SetUniformMatrix4fv("projection", _render->CameraProjection());
    shadowMapShader->SetUniformMatrix4fv("view", _render->CameraView());
    shadowMapShader->SetUniform3fv("viewPos", _render->camera->position);
    shadowMapShader->SetUniform3fv("lightPos", _render->LightPosition());
    shadowMapShader->SetUniformMatrix4fv("lightSpaceMatrix", _render->LightSpaceMVP());

    graphics->activeShader = shadowMapShader;
	
    // Render scene into shadow map
    RenderShadowScene(graphics);
}


void GameWorld::RenderShadowScene(Graphics* graphics)
{
    for (int i = 0; i < _shadowShapes.size(); i++)
    {
        auto* texture = TexturePool::Instance()->GetSimpleTextureById(_shadowShapes[i]->TextureIdentifier);
        texture->Bind();

        _shadowShapes[i]->Bind();
        _shadowShapes[i]->Draw(graphics);
        _shadowShapes[i]->Unbind();

        texture->Unbind();
    }
}