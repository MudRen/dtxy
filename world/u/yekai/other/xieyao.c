#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_give",1);
    set("no_drop",1);
    set("no_sell",1);
  }                                    
  add_action("do_eat", "eat");
}

void create()
{
  set_name(YEL "кҩ" NOR, ({"xie yao","xieyao","yao"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "ƿ");
    set("long", "һ�ң�����˴������Ρ�\n");
    set("value", 50000);
    set("drug_type", "��Ʒ");
    set("is_monitored",1);
    set("reward_value",1);
  }
  
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  int food_allowed=(int)me->query("food");
  int water_allowed=(int)me->query("water");
  if (!id(arg))
    return notify_fail("��Ҫ��ʲô��\n");
  
        if ((int)this_player()->is_busy() )
     return notify_fail("( ����һ��������û����ɡ�)\n");
   if (food_allowed<20
    ||water_allowed<20) {
     message_vision(HIM"$N����һƿкҩ�����ö����͵����ܡ�����ʲôҲû��������\n"NOR,me);
     destruct(this_object());
     return 1;
  }
  message_vision(HIM "$N����һƿкҩ��ֻ������ߴ�ﹾ�����������$N��û��Ӧ�����Ѿ����������ˡ� \n" NOR, me);
  me->set("food", 50);
  me->set("water", 50);
  me->start_busy(6);

  destruct(this_object());

  return 1;
}




