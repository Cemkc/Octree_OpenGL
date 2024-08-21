#include "scenes/Scene.h"

namespace scene {

	class SceneMenu : public Scene {
	public:
		SceneMenu(Scene*& currenScenePtr);
		~SceneMenu();

		void OnRender() override;
		void OnImGuiRender() override;

		template <typename T>
		void RegisterScene(const std::string& sceneName)
		{
			std::cout << "Registering Scene: " << sceneName << std::endl;

			m_Scenes.push_back(std::make_pair(sceneName, []() {return new T; }));
		}

	private:
		Scene*& m_CurrentScene;
		std::vector<std::pair<std::string, std::function<Scene* ()>>> m_Scenes; // For the second type of the pair I could just go with Scene* 
		// but that would mean I need a Scene object which already exists to assign to that pair
		// since I want to create the Scenes as I call them I use a lambda function that creates and returns Scene*
	};
}