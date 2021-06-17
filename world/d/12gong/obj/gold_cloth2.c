// by happ@YSZZ

#include <armor.h>

inherit CLOTH;
#include "chk_owner.c"

void create()
{
   set_name("»Æ½ðÊ¥ÒÂ", ({ "huangjin shengyi" }) );
   set_weight(10000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "¼þ");
     set("no_give",1);
     set("value",2000000);
     set("material", "steel");
     set("armor_prop/armor",120);
  }
  set("special_effects", "ÎÞ");  // emotion
   setup();
}
int query_autoload() { return 1; }
