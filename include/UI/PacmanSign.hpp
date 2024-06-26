#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_PACMANSIGN_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_PACMANSIGN_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class PacmanSign : public Util::GameObject {
public:
    explicit PacmanSign() {
        SetImage(RESOURCE_DIR"/Image/UI/PacMan-removebg-preview.png");
        ResetPosition();
    };

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    };

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
    std::string m_ImagePath;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_PACMANSIGN_HPP
