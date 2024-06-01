#include <Arduino.h>
#include <ui/ui.h>
#include <map>

enum LabelTextState {
  TEXT_DEFAULT,
  TEXT_NORMAL,
  TEXT_WARNING,
  TEXT_HIGH,
  TEXT_CRITICAL
};

std::map<LabelTextState, uint32_t> TextStatusMap = {
  { TEXT_DEFAULT, 0x000000 },
  { TEXT_NORMAL, 0x8ac926 },
  { TEXT_WARNING, 0xffcf00 },
  { TEXT_HIGH, 0xff41e2 },
  { TEXT_CRITICAL, 0xfa003f }
};

void updateLvglText(lv_obj_t *ui_object, String labelText, LabelTextState textState) {
  if (ui_object != nullptr) {
    lv_label_set_text(ui_object, labelText.c_str());
    lv_obj_set_style_text_color(ui_object, lv_color_hex(TextStatusMap[textState]), LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}
