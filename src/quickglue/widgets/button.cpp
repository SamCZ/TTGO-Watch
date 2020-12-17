#include "button.h"
#include <config.h>
#include "../internal/widgetmanager.h"

Button::Button(lv_obj_t * btn){
  assign(btn);
  // lv_cont_set_fit(native, true, true);
  
  auto subLabelhandle = lv_obj_get_child(btn, NULL);
  if (subLabelhandle != nullptr)
    label = Label(subLabelhandle);
}


Button::Button(const Widget* parent, const lv_img_dsc_t& image, WidgetAction onClick){
  assign(lv_imgbtn_create(parent->handle(), NULL));
  
  lv_imgbtn_set_src(native, LV_BTN_STATE_RELEASED, &image);
  lv_imgbtn_set_src(native, LV_BTN_STATE_PRESSED, &image);
  lv_imgbtn_set_src(native, LV_BTN_STATE_CHECKED_RELEASED, &image);
  lv_imgbtn_set_src(native, LV_BTN_STATE_CHECKED_PRESSED, &image);
  
  if (onClick != NULL)
    clicked(onClick);
}

// Button::Button(const Widget* parent, const char * txt){
//   native = lv_btn_create(lv_scr_act(), NULL);
//   lv_obj_t * lbl = lv_label_create(native, NULL);
//   lv_label_set_text(lbl, txt);
//   label = Label(lv_obj_get_child(native, NULL));
//   //label.alignText(LV_ALIGN_TEXT_CENTER);
// }

Button& Button::clicked(WidgetAction onClick){
    auto wh = DefaultWidgetManager.GetOrCreate(native);
    wh->Action = onClick;
    return *this;
}

void Button::createObject(lv_obj_t* parent){
  assign(lv_obj_create(parent, NULL));
}

void Button::assign(lv_obj_t* newHandle)
{
    Widget::assign(newHandle);
    if (lv_obj_get_event_cb(native) == NULL)
      lv_obj_set_event_cb(native, &Button::Action);
}

// void Button::size(uint16_t width, uint16_t height){
//   // lv_cont_set_fit(native, false, false);
//   lv_obj_set_size(native, width, height);
//   label.size(width, height);
// }

Button& Button::disable() {
  lv_btn_set_state(native, LV_BTN_STATE_DISABLED);
  lv_obj_set_click(native, false);
  return *this;
}
Button& Button::enable() {
  lv_obj_set_click(native, true);
  lv_btn_set_state(native, LV_BTN_STATE_RELEASED);
  return *this;
}

void Button::Action(lv_obj_t* obj, lv_event_t event)
{
    auto handle = DefaultWidgetManager.GetIfExists(obj);
    Widget target(obj);
    switch (event) {
        case LV_EVENT_CLICKED:
            if (handle->Action != NULL)
              handle->Action(target);
            break;
    }
}