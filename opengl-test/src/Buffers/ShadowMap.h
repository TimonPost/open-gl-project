#pragma once
#include <cstddef>
#include <GL/glew.h>
#include "../Resources/Shader.h"
#include "../Resources/ShaderPool.h"
#include "../Constants.h"
#include "../World/Renderer.h"
#include "GameWindow.h"

/// <summary>
/// Manages shadow map generation for scene objects.
/// </summary>
class ShadowMap
{
	GLuint depthMapFBO{};
	GLuint depthMap{};

public:
	Shader* shadowShader{};
	
	/// <summary>
	/// Initializes the shadow map 
	/// </summary>
	/// <returns></returns>
	bool Initialize()
	{
		// create buffer.
		glGenFramebuffers(1, &depthMapFBO);
		
		// create depth texture
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// set shader
		shadowShader = ShaderPool::Instance()->GetShaderById(shadow_map_shaderID);

		const GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}
		return true;
	}

	/// <summary>
	/// Starts the shadow map pass.
	/// </summary>
	/// <param name="renderer"></param>
	void StartShadowMapPass(Renderer* renderer) const
	{
		const glm::mat4 depthMVP = renderer->LightSpaceMVP();
		
		shadowShader->Bind();
		shadowShader->SetUniformMatrix4fv("lightSpaceMatrix", depthMVP);
		
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	/// <summary>
	/// Ends the shadow map pass.
	/// </summary>
	void EndShadowMapPass() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, GameWindow::ScreenWidth, GameWindow::ScreenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowShader->Unbind();
	}

	/// <summary>
	/// Starts the scene pass.
	/// </summary>
	/// <param name="textureSlot"></param>
	void StartScenePass(GLint textureSlot) const
	{
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}
};
