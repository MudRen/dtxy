inherit ITEM;
#include <ansi.h>
void create()
{
  set_name(""HIY"��ּ"NOR"", ({"jin zhi","jinzhi"}));
  set_weight(28000);
  set("long", "����ǵ�����۸����������Ľ�ּ��\n" );
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("material", "paper");
    set("value", 2000);
    set("no_sell", 1);
    set("no_drop", 1);
  }
  setup();
}