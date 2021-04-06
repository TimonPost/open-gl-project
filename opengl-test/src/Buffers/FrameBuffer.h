#pragma once
#include <cstddef>
#include <GL/glew.h>

#include "GLRegisterable.h"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

class ShadowMapFBO
{

public:
	GLuint depthMapFBO;
	GLuint depthMap;
	Shader* _shadowShader;
	
	ShadowMapFBO()
	{
	}

	~ShadowMapFBO();

	bool Init()
	{
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
		
		_shadowShader = ShaderPool::Instance()->GetShaderById(shadowMapShaderID);
				
		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}
	}

	void ShadowMapPass(Renderer* renderer)
	{
		glm::mat4 depthMVP = renderer->LightSpaceMVP();
		
		_shadowShader->Bind();
		_shadowShader->SetUniformMatrix4fv("lightSpaceMatrix", depthMVP);
		
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void EndShadowMapPass()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_shadowShader->Unbind();
	}
	
	void ScenePassStart(GLint textureSlot)
	{
		glActiveTexture(textureSlot);
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}

private:

};
