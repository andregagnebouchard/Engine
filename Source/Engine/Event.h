#pragma once
namespace Engine
{
  class Event
  {
  public:
    enum class Id
    {
      // KeyEventPressed
      KEY_A_PRESS,
      KEY_B_PRESS,
      KEY_C_PRESS,
      KEY_D_PRESS,
      KEY_E_PRESS,
      KEY_F_PRESS,
      KEY_G_PRESS,
      KEY_H_PRESS,
			KEY_I_PRESS,
      KEY_J_PRESS,
      KEY_K_PRESS,
      KEY_L_PRESS,
      KEY_M_PRESS,
      KEY_N_PRESS,
      KEY_O_PRESS,
      KEY_P_PRESS,
      KEY_Q_PRESS,
      KEY_R_PRESS,
      KEY_S_PRESS,
      KEY_T_PRESS,
      KEY_U_PRESS,
      KEY_V_PRESS,
      KEY_W_PRESS,
      KEY_X_PRESS,
      KEY_Y_PRESS,
      KEY_Z_PRESS,
      KEY_NUM0_PRESS,
      KEY_NUM1_PRESS,
      KEY_NUM2_PRESS,
      KEY_NUM3_PRESS,
      KEY_NUM4_PRESS,
      KEY_NUM5_PRESS,
      KEY_NUM6_PRESS,
      KEY_NUM7_PRESS,
      KEY_NUM8_PRESS,
      KEY_NUM9_PRESS,
      KEY_ESCAPE_PRESS,
      KEY_LCONTROL_PRESS,
      KEY_LSHIFT_PRESS,
      KEY_LALT_PRESS,
      KEY_LSYSTEM_PRESS,
      KEY_RCONTROL_PRESS,
      KEY_RSHIFT_PRESS,
      KEY_RALT_PRESS,
      KEY_RSYSTEM_PRESS,
      KEY_MENU_PRESS,
      KEY_LBRACKET_PRESS,
      KEY_RBRACKET_PRESS,
      KEY_SEMICOLON_PRESS,
      KEY_COMMA_PRESS,
      KEY_PERIOD_PRESS,
      KEY_QUOTE_PRESS,
      KEY_SLASH_PRESS,
      KEY_BACKSLASH_PRESS,
      KEY_TILDE_PRESS,
      KEY_EQUAL_PRESS,
      KEY_DASH_PRESS,
      KEY_SPACE_PRESS,
      KEY_RETURN_PRESS,
      KEY_BACKSPACE_PRESS,
      KEY_TAB_PRESS,
      KEY_PAGEUP_PRESS,
      KEY_PAGEDOWN_PRESS,
      KEY_END_PRESS,
      KEY_HOME_PRESS,
      KEY_INSERT_PRESS,
      KEY_DELETE_PRESS,
      KEY_ADD_PRESS,
      KEY_SUBSTRACT_PRESS,
      KEY_MULTIPLY_PRESS,
      KEY_DIVIDE_PRESS,
      KEY_LEFT_PRESS,
      KEY_RIGHT_PRESS,
      KEY_UP_PRESS,
      KEY_DOWN_PRESS,
      KEY_NUMPAD0_PRESS,
      KEY_NUMPAD1_PRESS,
      KEY_NUMPAD2_PRESS,
      KEY_NUMPAD3_PRESS,
      KEY_NUMPAD4_PRESS,
      KEY_NUMPAD5_PRESS,
      KEY_NUMPAD6_PRESS,
      KEY_NUMPAD7_PRESS,
      KEY_NUMPAD8_PRESS,
      KEY_NUMPAD9_PRESS,
      KEY_F1_PRESS,
      KEY_F2_PRESS,
      KEY_F3_PRESS,
      KEY_F4_PRESS,
      KEY_F5_PRESS,
      KEY_F6_PRESS,
      KEY_F7_PRESS,
      KEY_F8_PRESS,
      KEY_F9_PRESS,
      KEY_F10_PRESS,
      KEY_F11_PRESS,
      KEY_F12_PRESS,
      KEY_F13_PRESS,
      KEY_F14_PRESS,
      KEY_F15_PRESS,
      KEY_PAUSE_PRESS,

      // KeyEventReleased
      // These need to be right next to the "Press" event to map them with an offset
      KEY_A_RELEASE,
      KEY_B_RELEASE,
      KEY_C_RELEASE,
      KEY_D_RELEASE,
      KEY_E_RELEASE,
      KEY_F_RELEASE,
      KEY_G_RELEASE,
      KEY_H_RELEASE,
			KEY_I_RELEASE,
      KEY_J_RELEASE,
      KEY_K_RELEASE,
      KEY_L_RELEASE,
      KEY_M_RELEASE,
      KEY_N_RELEASE,
      KEY_O_RELEASE,
      KEY_P_RELEASE,
      KEY_Q_RELEASE,
      KEY_R_RELEASE,
      KEY_S_RELEASE,
      KEY_T_RELEASE,
      KEY_U_RELEASE,
      KEY_V_RELEASE,
      KEY_W_RELEASE,
      KEY_X_RELEASE,
      KEY_Y_RELEASE,
      KEY_Z_RELEASE,
      KEY_NUM0_RELEASE,
      KEY_NUM1_RELEASE,
      KEY_NUM2_RELEASE,
      KEY_NUM3_RELEASE,
      KEY_NUM4_RELEASE,
      KEY_NUM5_RELEASE,
      KEY_NUM6_RELEASE,
      KEY_NUM7_RELEASE,
      KEY_NUM8_RELEASE,
      KEY_NUM9_RELEASE,
      KEY_ESCAPE_RELEASE,
      KEY_LCONTROL_RELEASE,
      KEY_LSHIFT_RELEASE,
      KEY_LALT_RELEASE,
      KEY_LSYSTEM_RELEASE,
      KEY_RCONTROL_RELEASE,
      KEY_RSHIFT_RELEASE,
      KEY_RALT_RELEASE,
      KEY_RSYSTEM_RELEASE,
      KEY_MENU_RELEASE,
      KEY_LBRACKET_RELEASE,
      KEY_RBRACKET_RELEASE,
      KEY_SEMICOLON_RELEASE,
      KEY_COMMA_RELEASE,
      KEY_PERIOD_RELEASE,
      KEY_QUOTE_RELEASE,
      KEY_SLASH_RELEASE,
      KEY_BACKSLASH_RELEASE,
      KEY_TILDE_RELEASE,
      KEY_EQUAL_RELEASE,
      KEY_DASH_RELEASE,
      KEY_SPACE_RELEASE,
      KEY_RETURN_RELEASE,
      KEY_BACKSPACE_RELEASE,
      KEY_TAB_RELEASE,
      KEY_PAGEUP_RELEASE,
      KEY_PAGEDOWN_RELEASE,
      KEY_END_RELEASE,
      KEY_HOME_RELEASE,
      KEY_INSERT_RELEASE,
      KEY_DELETE_RELEASE,
      KEY_ADD_RELEASE,
      KEY_SUBSTRACT_RELEASE,
      KEY_MULTIPLY_RELEASE,
      KEY_DIVIDE_RELEASE,
      KEY_LEFT_RELEASE,
      KEY_RIGHT_RELEASE,
      KEY_UP_RELEASE,
      KEY_DOWN_RELEASE,
      KEY_NUMPAD0_RELEASE,
      KEY_NUMPAD1_RELEASE,
      KEY_NUMPAD2_RELEASE,
      KEY_NUMPAD3_RELEASE,
      KEY_NUMPAD4_RELEASE,
      KEY_NUMPAD5_RELEASE,
      KEY_NUMPAD6_RELEASE,
      KEY_NUMPAD7_RELEASE,
      KEY_NUMPAD8_RELEASE,
      KEY_NUMPAD9_RELEASE,
      KEY_F1_RELEASE,
      KEY_F2_RELEASE,
      KEY_F3_RELEASE,
      KEY_F4_RELEASE,
      KEY_F5_RELEASE,
      KEY_F6_RELEASE,
      KEY_F7_RELEASE,
      KEY_F8_RELEASE,
      KEY_F9_RELEASE,
      KEY_F10_RELEASE,
      KEY_F11_RELEASE,
      KEY_F12_RELEASE,
      KEY_F13_RELEASE,
      KEY_F14_RELEASE,
      KEY_F15_RELEASE,
      KEY_PAUSE_RELEASE,

      UNKNOWN, // Unknown Id for initialisation purposes

      RENDER_SPRITE
    };

    static const int KEY_RELEASED_OFFSET = static_cast<int>(Id::KEY_A_RELEASE) - static_cast<int>(Id::KEY_A_PRESS);

    struct KeyEvent
    {
      enum class State { Pressed, Released };
      State alt;
      State control;
      State shift;
      State system;
    };

    struct RenderEvent
    {
      int spriteId;
    };

    enum class Type
    {
      Key,
      Rendering,
    };

    Event(Type type, Id id) : m_Type(type), m_Id(id) {}
    Event(Type type) : m_Type(type), m_Id(Id::UNKNOWN) {}

    union
    {
      KeyEvent key;
      RenderEvent render;
    };
    Type GetType() const { return m_Type; }
    Id GetId() const { return m_Id; }
    void SetId(Id id) { m_Id = id; }
  private:
    Type m_Type;
    Id m_Id;
  };
}