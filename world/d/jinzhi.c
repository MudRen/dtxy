#include <ansi.h>
inherit ITEM;

void create()
{
  set_name(""HIY"金旨"NOR"", ({"jin zhi","jinzhi"}));
  set_weight(28000);
  set("long", "这就是当年玉帝给泾河龙王的金旨。\n" );
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "张");
    set("material", "paper");
    set("value", 2000);
    set("no_sell", 1);
    set("no_give", 1);
    set("no_drop", 1);
  }
  setup();
}
