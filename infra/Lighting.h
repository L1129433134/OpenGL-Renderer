#pragma once

#include <glErrors.h>
#include <Shader.h>
#include <GL/glew.h>

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <string>
#include <unordered_set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {

	protected:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

		glm::vec3 m_Color;
	public:
		Light();
		Light(glm::vec3 Color);
		~Light(){}


		void OnUpdateAmbient(glm::vec3 ambient);
		void OnUpdateDiffuse(glm::vec3 diffuse);
		void OnUpdateSpecular(glm::vec3 specular);

		void OnUpdateColor(glm::vec3 Color);

		virtual std::string getUniformName() {return std::string("u_Light");}

		virtual void OnRender(std::vector<Shader*>& shaders);
		virtual void OnImGuiRender();
};


class PointLight : public Light{
	private:
		static std::unordered_set <unsigned int> m_PointLightIdAssigned;
		static unsigned int m_PointLightIdCount;
		unsigned int m_PointLightId;
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_AttenuationQuadraticCoefficients;//x*d^2 + y*d + z;
	public:

		PointLight(glm::vec3 Position,glm::vec3 Color);
		~PointLight();

		std::string getUniformName();
		
		void OnUpdatePosition(glm::vec3 pos_or_speed,bool is_pos=false);
		void OnUpdateAttenuation(glm::vec3 attenuationQuadraticCoefficients);

		void OnRender(std::vector<Shader*>& shaders);
		void OnImGuiRender();
};

class DirectionLight :public Light{
	private:
		static std::unordered_set <unsigned int> m_DirectionLightIdAssigned;
		static unsigned int m_DirectionLightIdCount;
		unsigned int m_DirectionLightId;
	protected:
		glm::vec3 m_Direction;

	public:

		DirectionLight(glm::vec3 Direction,glm::vec3 Color);
		~DirectionLight();

		std::string getUniformName();

		void OnUpdateDirection(glm::vec3 direction);

		void OnRender(std::vector<Shader*>& shaders);
		void OnImGuiRender();
};

class LightList :public Light{
	private:
		std::vector<std::shared_ptr<Light>> m_Lights;

	public:

		LightList();
		~LightList();

		void OnRender(std::vector<Shader*>& shaders);
		void OnImGuiRender();
};