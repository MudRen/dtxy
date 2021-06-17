// by happ@YSZZ

#include <armor.h>
#include <ansi.h>
#include "chk_owner.c"

inherit ARMOR;

void create()
{
   set_name(HIY"»Æ½ðÊ¥ÒÂ"NOR, ({ "huangjin shengyi" }) );
   set_weight(3000);
   if( clonep() )
   set_default_object(__FILE__);
   else {
     set("unit", "¼þ");
      set("no_sell",1);
      set("no_give",1);
      set("no_drop",1);
      set("no_get",1);
       set("value",10);
     set("material", "steel");
   set("armor_prop/armor",150);
  }
  set("special_effects", "ÎÞ");  // emotion
   setup();
}
int query_autoload() { return 1; }
