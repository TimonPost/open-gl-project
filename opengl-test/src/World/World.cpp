#include "World.h"

World::World(std::shared_ptr<Renderer>& render)
{
	_render = render;

}

void World::AddBPRShape(ShapeBase& shape)
{
	_pbrShapes.push_back(&shape);
}

void World::AddShadowShape(ShapeBase& shape)
{
    _shadowShapes.push_back(&shape);
}

void World::AddObjectShape(ShapeBase& shape)
{
    _objectShapes.push_back(&shape);
}

Camera* World::MainCamera() const
{
	return _render->camera.get();
}

void World::DrawShapes()
{
    Graphics graphics;
    graphics.Render = _render.get();
    graphics.directionalLight = &directionalLight;
    graphics.spotLight = &spotLight;
    graphics.pointLights = &pointLights;
    	
    RenderShadowShapes(&graphics);
    RenderPBRShapes(&graphics);
    DrawObjectShapes(graphics);
}

void World::DrawObjectShapes(Graphics graphics)
{
    Shader* objectShader = ShaderPool::Instance()->GetShaderById(objectShaderID);
    objectShader->Bind();
    objectShader->SetUniformMatrix4fv("projection", _render->P());
    objectShader->SetUniformMatrix4fv("view", _render->V());

    graphics.activeShader = objectShader;

    for (int i = 0; i < _objectShapes.size(); i++)
    {
        objectShader->SetUniform3fv("lightPos", _render->LightPosition());

        auto* texture = TexturePool::Instance()->GetSimpleTextureById(_objectShapes[i]->TextureIdentifier);
        texture->Bind();
        _objectShapes[i]->Bind();
        _objectShapes[i]->Draw(&graphics);
        _objectShapes[i]->Unbind();
        texture->Unbind();
    }	
}

void World::RenderPBRShapes(Graphics* graphics)
{
    Shader* pbrShader = ShaderPool::Instance()->GetShaderById(pbrShaderID);
    pbrShader->Bind();
	
    graphics->ApplyLightsToShader(pbrShader);
    pbrShader->SetUniformMatrix4fv("projection", _render->P());
    pbrShader->SetUniformMatrix4fv("view", _render->V());
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

void World::RenderShadowShapes(Graphics* graphics)
{	
	// Start pass
    shadowMap.ShadowMapPass(graphics->Render);

    graphics->activeShader = shadowMap._shadowShader;

    RenderShadowScene(graphics);

    shadowMap.EndShadowMapPass();

    // Scene Pass
	
    shadowMap.ScenePassStart(GL_TEXTURE1);
	
    Shader* shadowMapShader = ShaderPool::Instance()->GetShaderById(shadowMappingShaderID);
    shadowMapShader->Bind();
    	
    shadowMapShader->SetUniformMatrix4fv("projection", _render->P());
    shadowMapShader->SetUniformMatrix4fv("view", _render->V());
    shadowMapShader->SetUniform3fv("viewPos", _render->camera->position);
    shadowMapShader->SetUniform3fv("lightPos", _render->LightPosition());
    shadowMapShader->SetUniformMatrix4fv("lightSpaceMatrix", _render->LightSpaceMVP());

    graphics->activeShader = shadowMapShader;
	
    // Render scene into shadow map
    RenderShadowScene(graphics);
}


void World::RenderShadowScene(Graphics* graphics)
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