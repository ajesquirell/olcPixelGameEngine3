#include "hw_mouse.h"

//! START IMPLEMENTATION
namespace olc::hw
{
    const Button& Mouse::GetButton(const int nButton) const
    {
        return buttons.at(nButton);
    }

    const olc::vf2d& Mouse::GetPosition() const
    {
        return position;
    }

    int32_t Mouse::GetWheel() const
    {
        return wheel;
    }

    const olc::vf2d& Mouse::GetRelativeDelta() const
    {
        return relative_delta;
    }

    bool Mouse::IsRelativeModeEnabled() const
    {
        return relative_mode_enabled;
    }

    void Mouse::SetRelativeModeEnabled(bool enabled)
    {
        relative_mode_enabled = enabled;
        relative_delta = {0.0f, 0.0f};
        relative_delta_in = {0.0f, 0.0f};
    }

    void Mouse::SetPosition(const olc::vf2d& pos)
    {
        position_in = pos;
    }

    void Mouse::SetButton(const int nButton, bool state)
    {        
        buttons_new[nButton] = state;            
    }

    void Mouse::SetWheel(const int32_t w)
    {
        wheel_in = w;
    }

    void Mouse::AddRelativeDelta(const olc::vf2d& delta)
    {
        relative_delta_in += delta;
    }

    void Mouse::UpdateState()
    {
        for (size_t i=0; i<buttons.size(); i++)
        {
            buttons[i].bPressed = false;
            buttons[i].bReleased = false;
            if (buttons_new[i] != buttons_old[i])
            {
                if (buttons_new[i])
                {
                    buttons[i].bPressed = !buttons[i].bHeld;
                    buttons[i].bHeld = true;
                }
                else
                {
                    buttons[i].bReleased = true;
                    buttons[i].bHeld = false;
                }
            }
            buttons_old[i] = buttons_new[i];
        }

        position = position_in;
        wheel = wheel_in;
        wheel_in = 0;
        relative_delta = relative_delta_in;
        relative_delta_in = {0.0f, 0.0f};
    }
}
//! END IMPLEMENTATION
