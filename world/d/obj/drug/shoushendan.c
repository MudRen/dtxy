
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
	if(this_player()==environment())
	  add_action("do_eat", "eat");
}

void create()
{
  set_name( GRN "嫦娥瘦身丹" NOR , ({"change shoushen", "dan"}));
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "颗");
    set("long", "一颗五彩的糖丸，略微能闻到些许香气。爱美之人经常不惜重金寻购, 用以减肥, \n保持苗条身材. 让体弱多病的夫君可以轻易背负\n");
    set("value", 2000000);
    set("drug_type", "良药");
    set("special_effects", "服一颗先天力量减一. 吃完后记得quit");
  }
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="dan" && arg!="change shoushen")	return 0;

  if (me->query("str") <= 10) {
	  tell_object(me, "你已经这么瘦了, 这个嫦娥瘦身丹还是不要再吃了吧.\n");
	  return 1;
  }
  me->add("str", -1);
  message_vision(HIG "$N轻轻掰开一颗嫦娥瘦身丹送入嘴中，一时间肚中雷鸣。只见$N脚下流出一片厚厚的油脂，看起来腰也细多了！\n" NOR, me);
  log_file("eat_dan", me->query("name") + "(" + me->query("id") + ")吃了一颗嫦娥瘦身丹, str减为" + me->query("str") +"\n" );
  destruct(this_object());
  return 1;
}

