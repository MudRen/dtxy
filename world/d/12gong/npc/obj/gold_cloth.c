// by happ@YSZZ

#include <armor.h>
#include <ansi.h>
#include "chk_owner.c"
inherit ARMOR;

void create()
{
set_name(HIY"�ƽ�ʥ��"NOR, ({ "huangjin shengyi","shengyi","armor" }) );
   set_weight(3000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "��");
      set("no_sell",1);
       set("value",0);
     set("material", "steel");
     set("armor_prop/armor",100);
  }
   setup();
}
int query_autoload() { return 1; }
