#pragma once
namespace Engine
{
  class Event
  {
  public:
    enum class Id
    {
      // KeyEventPressed
      A_KEY_PRESS,
      B_KEY_PRESS,
      C_KEY_PRESS,
      D_KEY_PRESS,
      E_KEY_PRESS,
      F_KEY_PRESS,
      G_KEY_PRESS,
      H_KEY_PRESS,
      J_KEY_PRESS,
      K_KEY_PRESS,
      L_KEY_PRESS,
      M_KEY_PRESS,
      N_KEY_PRESS,
      O_KEY_PRESS,
      P_KEY_PRESS,
      Q_KEY_PRESS,
      R_KEY_PRESS,
      S_KEY_PRESS,
      T_KEY_PRESS,
      U_KEY_PRESS,
      V_KEY_PRESS,
      W_KEY_PRESS,
      X_KEY_PRESS,
      Y_KEY_PRESS,
      Z_KEY_PRESS,
      NUM0_KEY_PRESS,
      NUM1_KEY_PRESS,
      NUM2_KEY_PRESS,
      NUM3_KEY_PRESS,
      NUM4_KEY_PRESS,
      NUM5_KEY_PRESS,
      NUM6_KEY_PRESS,
      NUM7_KEY_PRESS,
      NUM8_KEY_PRESS,
      NUM9_KEY_PRESS,
      ESCAPE_KEY_PRESS,
      LCONTROL_KEY_PRESS,
      LSHIFT_KEY_PRESS,
      LALT_KEY_PRESS,
      LSYSTEM_KEY_PRESS,
      RCONTROL_KEY_PRESS,
      RSHIFT_KEY_PRESS,
      RALT_KEY_PRESS,
      RSYSTEM_KEY_PRESS,
      MENU_KEY_PRESS,
      LBRACKET_KEY_PRESS,
      RBRACKET_KEY_PRESS,
      SEMICOLON_KEY_PRESS,
      COMMA_KEY_PRESS,
      PERIOD_KEY_PRESS,
      QUOTE_KEY_PRESS,
      SLASH_KEY_PRESS,
      BACKSLASH_KEY_PRESS,
      TILDE_KEY_PRESS,
      EQUAL_KEY_PRESS,
      DASH_KEY_PRESS,
      SPACE_KEY_PRESS,
      RETURN_KEY_PRESS,
      BACKSPACE_KEY_PRESS,
      TAB_KEY_PRESS,
      PAGEUP_KEY_PRESS,
      PAGEDOWN_KEY_PRESS,
      END_KEY_PRESS,
      HOME_KEY_PRESS,
      INSERT_KEY_PRESS,
      DELETE_KEY_PRESS,
      ADD_KEY_PRESS,
      SUBSTRACT_KEY_PRESS,
      MULTIPLY_KEY_PRESS,
      DIVIDE_KEY_PRESS,
      LEFT_KEY_PRESS,
      RIGHT_KEY_PRESS,
      UP_KEY_PRESS,
      DOWN_KEY_PRESS,
      NUMPAD0_KEY_PRESS,
      NUMPAD1_KEY_PRESS,
      NUMPAD2_KEY_PRESS,
      NUMPAD3_KEY_PRESS,
      NUMPAD4_KEY_PRESS,
      NUMPAD5_KEY_PRESS,
      NUMPAD6_KEY_PRESS,
      NUMPAD7_KEY_PRESS,
      NUMPAD8_KEY_PRESS,
      NUMPAD9_KEY_PRESS,
      F1_KEY_PRESS,
      F2_KEY_PRESS,
      F3_KEY_PRESS,
      F4_KEY_PRESS,
      F5_KEY_PRESS,
      F6_KEY_PRESS,
      F7_KEY_PRESS,
      F8_KEY_PRESS,
      F9_KEY_PRESS,
      F10_KEY_PRESS,
      F11_KEY_PRESS,
      F12_KEY_PRESS,
      F13_KEY_PRESS,
      F14_KEY_PRESS,
      F15_KEY_PRESS,
      PAUSE_KEY_PRESS,

      // KeyEventReleased
      A_KEY_RELEASE,
      B_KEY_RELEASE,
      C_KEY_RELEASE,
      D_KEY_RELEASE,
      E_KEY_RELEASE,
      F_KEY_RELEASE,
      G_KEY_RELEASE,
      H_KEY_RELEASE,
      J_KEY_RELEASE,
      K_KEY_RELEASE,
      L_KEY_RELEASE,
      M_KEY_RELEASE,
      N_KEY_RELEASE,
      O_KEY_RELEASE,
      P_KEY_RELEASE,
      Q_KEY_RELEASE,
      R_KEY_RELEASE,
      S_KEY_RELEASE,
      T_KEY_RELEASE,
      U_KEY_RELEASE,
      V_KEY_RELEASE,
      W_KEY_RELEASE,
      X_KEY_RELEASE,
      Y_KEY_RELEASE,
      Z_KEY_RELEASE,
      NUM0_KEY_RELEASE,
      NUM1_KEY_RELEASE,
      NUM2_KEY_RELEASE,
      NUM3_KEY_RELEASE,
      NUM4_KEY_RELEASE,
      NUM5_KEY_RELEASE,
      NUM6_KEY_RELEASE,
      NUM7_KEY_RELEASE,
      NUM8_KEY_RELEASE,
      NUM9_KEY_RELEASE,
      ESCAPE_KEY_RELEASE,
      LCONTROL_KEY_RELEASE,
      LSHIFT_KEY_RELEASE,
      LALT_KEY_RELEASE,
      LSYSTEM_KEY_RELEASE,
      RCONTROL_KEY_RELEASE,
      RSHIFT_KEY_RELEASE,
      RALT_KEY_RELEASE,
      RSYSTEM_KEY_RELEASE,
      MENU_KEY_RELEASE,
      LBRACKET_KEY_RELEASE,
      RBRACKET_KEY_RELEASE,
      SEMICOLON_KEY_RELEASE,
      COMMA_KEY_RELEASE,
      PERIOD_KEY_RELEASE,
      QUOTE_KEY_RELEASE,
      SLASH_KEY_RELEASE,
      BACKSLASH_KEY_RELEASE,
      TILDE_KEY_RELEASE,
      EQUAL_KEY_RELEASE,
      DASH_KEY_RELEASE,
      SPACE_KEY_RELEASE,
      RETURN_KEY_RELEASE,
      BACKSPACE_KEY_RELEASE,
      TAB_KEY_RELEASE,
      PAGEUP_KEY_RELEASE,
      PAGEDOWN_KEY_RELEASE,
      END_KEY_RELEASE,
      HOME_KEY_RELEASE,
      INSERT_KEY_RELEASE,
      DELETE_KEY_RELEASE,
      ADD_KEY_RELEASE,
      SUBSTRACT_KEY_RELEASE,
      MULTIPLY_KEY_RELEASE,
      DIVIDE_KEY_RELEASE,
      LEFT_KEY_RELEASE,
      RIGHT_KEY_RELEASE,
      UP_KEY_RELEASE,
      DOWN_KEY_RELEASE,
      NUMPAD0_KEY_RELEASE,
      NUMPAD1_KEY_RELEASE,
      NUMPAD2_KEY_RELEASE,
      NUMPAD3_KEY_RELEASE,
      NUMPAD4_KEY_RELEASE,
      NUMPAD5_KEY_RELEASE,
      NUMPAD6_KEY_RELEASE,
      NUMPAD7_KEY_RELEASE,
      NUMPAD8_KEY_RELEASE,
      NUMPAD9_KEY_RELEASE,
      F1_KEY_RELEASE,
      F2_KEY_RELEASE,
      F3_KEY_RELEASE,
      F4_KEY_RELEASE,
      F5_KEY_RELEASE,
      F6_KEY_RELEASE,
      F7_KEY_RELEASE,
      F8_KEY_RELEASE,
      F9_KEY_RELEASE,
      F10_KEY_RELEASE,
      F11_KEY_RELEASE,
      F12_KEY_RELEASE,
      F13_KEY_RELEASE,
      F14_KEY_RELEASE,
      F15_KEY_RELEASE,
      PAUSE_KEY_RELEASE,
    };
    struct KeyEvent
    {
      enum class State { Pressed, Released };
      State alt;
      State control;
      State shift;
      State system;
    };

    enum class Type
    {
      Key,
      JoystickButton,
      Entity
    };

    union
    {
      KeyEvent key;
      //JoystickButtonEvent joystickButton, 
      //EntityEvent entity
    };
    Type GetType() const { return m_Type; }
    Id GetId() const { return m_Id; }
  private:
    Type m_Type;
    Id m_Id;
  };
}