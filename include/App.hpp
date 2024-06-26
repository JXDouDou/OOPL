#ifndef APP_HPP
#define APP_HPP

#include "Level/Character/Pacman.hpp"
#include "Level/ghost/Ghost.hpp"
#include "Level/life/LifeSystem.hpp"
#include "Level/fruit/FruitSystem.hpp"
#include "Level/score/ScoreSystem.hpp"
#include "Level/LevelManager.hpp"
#include "UI/UISystem.hpp"

#include "Util/Renderer.hpp"
#include "Level/map/Map.hpp"
#include "LevelBuilder.hpp"

class App {
public:
    enum class State {
        UI,//起始UI介面或返回後的UI(會一直更新直到切換)
        START,//遊戲地圖載入或切換地圖
        UPDATE,//處理遊戲過程(正常要回到UI才會到END)
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void UIUpdate();

    void Update();


    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
  
    State m_CurrentState = State::UI;

    Util::Renderer root;

//
    std::shared_ptr<UISystem> NowUI;
    bool IsBackFromGame = true;
    int nowLevel = 1;
    std::string playerID = "player001";
    std::shared_ptr<LevelManager> levelManager;

};

#endif
