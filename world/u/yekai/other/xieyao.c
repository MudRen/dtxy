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
  set_name(YEL "泻药" NOR, ({"xie yao","xieyao","yao"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "瓶");
    set("long", "一桃，真叫人垂涎欲滴。\n");
    set("value", 50000);
    set("drug_type", "补品");
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
    return notify_fail("你要吃什么？\n");
  
        if ((int)this_player()->is_busy() )
     return notify_fail("( 你上一个动作还没有完成。)\n");
   if (food_allowed<20
    ||water_allowed<20) {
     message_vision(HIM"$N喝下一瓶泻药，觉得肚子胀的难受。但是什么也没拉出来。\n"NOR,me);
     destruct(this_object());
     return 1;
  }
  message_vision(HIM "$N喝下一瓶泻药，只觉肚子叽里咕噜叫了起来，$N还没反应过来已经拉在身上了。 \n" NOR, me);
  me->set("food", 50);
  me->set("water", 50);
  me->start_busy(6);

  destruct(this_object());

  return 1;
}




