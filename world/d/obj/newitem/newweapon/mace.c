// copperjian.c
// created 5-30-97 pickle

#include <weapon.h>
#include <ansi.h>

inherit MACE;
inherit NEWITEM;

int is_weapon() {
    return 1;
}


void create()
{
  set_name("锏", ({"mace"}));
  set_weight(5000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "柄");
    set("value", 2000);
    set("material", "copper");
    set("long", "一柄灌注了魔力的锏，");
    set("wield_msg", "$N举起一柄$n，在地上撞出点点火星。\n");
    set("unwield_msg", "$N抹了抹$n上的锈，把它收了起来。\n");
  }
  
  init_mace(25);
  setup();
}

