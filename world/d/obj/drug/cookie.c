
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","������һ�ɣ��±���ָ�们�䣡\n");
    set("no_give","��ô�����±������������ˣ�\n");
    set("no_drop","��ô������±������˶��ϧѽ��\n");
    set("no_sell","��������֪��"+this_object()->query("name")+"�ļ�ֵ�������Լ����Űɡ�\n");
  }
    if(this_player()==environment())
  add_action("do_eat", "eat");
}

void create()
{
  switch (random(5)) {
    case 0:
      set_name( HIW "�����±�" NOR , ({"yue bing", "cookie"}));
      break;
    case 1:
      set_name( HIW "�����±�" NOR , ({"yue bing", "cookie"}));
      break;
    case 2:
      set_name( HIW "�����±�" NOR , ({"yue bing", "cookie"}));
      break;
    case 3:
      set_name( HIW "�����±�" NOR , ({"yue bing", "cookie"}));
      break;
    case 4:
      set_name( HIW "з���±�" NOR , ({"yue bing", "cookie"}));
  }
  set_weight(90);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "һ��С��������±������˴������Ρ�\n");
    set("value", 0);
    set("drug_type", "��Ʒ");
  }
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  if (arg!="cookie" && arg!="yue bing")	return 0;
  if (me->query("wizgift/cookie_2000_eaten") <=4)
 {
  me->add("wizgift/cookie_2000_eaten",1); 
  me->set("eff_sen", (int)me->query("max_sen"));
  me->set("sen", (int)me->query("max_sen"));
  me->set("eff_gin", (int)me->query("max_gin"));
  me->set("gin", (int)me->query("max_gin"));
  me->set("eff_kee", (int)me->query("max_kee"));
  me->set("kee", (int)me->query("max_kee"));
  me->set("mana", (int)me->query("max_mana"));
  me->set("force", (int)me->query("max_force"));
  me->set("food", (int)me->max_food_capacity());
  me->set("water", (int)me->max_water_capacity());
  me->add("potential",1000);
  me->add("combat_exp",1000);
  me->save();
  log_file("static/COOKIEGIFT","["+ctime(time())+"] "+
  sprintf("%s(%s)����һ��%O\n",
  this_player()->query("name"),this_player()->query("id"),
  this_object()));

 }
  message_vision(HIG "$N��������һ���±�ҧ��һ�ڣ����в��ⷺ��һ��˼��֮�⡣
\n" NOR, me);
  destruct(this_object());
  return 1;
}

