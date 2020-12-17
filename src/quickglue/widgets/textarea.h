#ifndef TEXTAREA_H_
#define TEXTAREA_H_

#include "widget.h"

class TextArea : public Widget {
public:
  TextArea(){};
  /** Create a TextArea from lvgl object */
  TextArea(lv_obj_t* handle);

  /** Create a TextArea with text `txt` */
  TextArea(const Widget* parent, const char* txt = NULL);
  
  TextArea& text(const char * txt);
  const char* text();

  TextArea& autoKeyboard(bool enable);
  
  TextArea& alignText(lv_label_align_t mode);
  TextArea& digitsMode(bool onlyDigits, const char* filterDigitsList = "+-.,0123456789");

  static const uint16_t IsDigitsOnlyMode = 1;
  static const uint16_t IsAutoKeyboardDisabled = 2;

  constexpr static const char* TypeName = "lv_textarea";

protected:
  virtual void createObject(lv_obj_t* parent);
  virtual void assign(lv_obj_t* newHandle);

private:
    static void Action(lv_obj_t * obj, lv_event_t event);
};

#endif