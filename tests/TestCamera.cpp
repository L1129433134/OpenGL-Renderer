#include <glErrors.h>
#include <TestCamera.h>

#include <GL/glew.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Renderer.h>
#include <Shader.h>
#include <Texture.h>
#include <Camera.h>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace test {

	TestCamera::TestCamera() :
		//m_Camera{{-1.0f,1.0f},{-1.0f,1.0f},{1.0f,-1.0f},true}{
		m_Camera{45.0f,1.0f,0.0f,3.0f}{
		float positions[] = {
			-0.5f, -0.5f, -1.0f, 0.0f, 0.0f, //0
			 0.5f, -0.5f, -1.0f, 1.0f, 0.0f, //1
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, //2
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //3
		};


		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(positions,5*4*sizeof(*positions));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO,layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices,6);

		m_Shader = std::make_unique<Shader>("./tests/Basic.shader");
		m_Texture = std::make_unique<Texture>("./res/textures/T1.png");
		
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture",0);

		Camera::setCurrentCamera(&m_Camera);
	}
	TestCamera::~TestCamera() {

	}

	void TestCamera::OnUpdate(float deltaTime) {
	}
	void TestCamera::OnRender() {

		glCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		glm::mat4 mvp = m_Camera.getVP();

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP",mvp);
		renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

		//std::cout<<glm::to_string(mvp)<<std::endl;

	}
	void TestCamera::OnImGuiRender() {
		m_Camera.OnImGuiRender();
	}

}